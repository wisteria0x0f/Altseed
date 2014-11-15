﻿
#include "ace.RenderedDirectionalLightObject3D.h"

#include "../../ace.Graphics_Imp.h"

#include "../../Resource/ace.RenderTexture2D_Imp.h"
#include "../../Resource/ace.DepthBuffer_Imp.h"

namespace ace
{
	void RenderedDirectionalLightObject3DProxy::CalcAABB(std::vector<Vector3DF>& points, Vector3DF& max_, Vector3DF& min_)
	{
		min_ = Vector3DF(FLT_MAX, FLT_MAX, FLT_MAX);
		max_ = Vector3DF(-FLT_MAX, -FLT_MAX, -FLT_MAX);
		for (auto p : points)
		{
			if (min_.X > p.X) min_.X = p.X;
			if (min_.Y > p.Y) min_.Y = p.Y;
			if (min_.Z > p.Z) min_.Z = p.Z;

			if (max_.X < p.X) max_.X = p.X;
			if (max_.Y < p.Y) max_.Y = p.Y;
			if (max_.Z < p.Z) max_.Z = p.Z;
		}
	}

	RenderedDirectionalLightObject3DProxy::RenderedDirectionalLightObject3DProxy(Graphics* graphics)
	{
		auto g = (Graphics_Imp*) graphics;

		deviceType = g->GetGraphicsDeviceType();
		LightColor = Color(255, 255, 255, 255);
		m_shadowTexture = g->CreateRenderTexture2D_Imp(RenderedDirectionalLightObject3D::ShadowBufferSize, RenderedDirectionalLightObject3D::ShadowBufferSize, TextureFormat::R16G16_FLOAT);
		m_shadowDepthBuffer = g->CreateDepthBuffer_Imp(RenderedDirectionalLightObject3D::ShadowBufferSize, RenderedDirectionalLightObject3D::ShadowBufferSize);
	}

	RenderedDirectionalLightObject3DProxy::~RenderedDirectionalLightObject3DProxy()
	{
		SafeRelease(m_shadowTexture);
		SafeRelease(m_shadowDepthBuffer);
	}

	Vector3DF RenderedDirectionalLightObject3DProxy::GetDirection()
	{
		auto& mat = GetGlobalMatrix();
		return Vector3DF(mat.Values[0][2], mat.Values[1][2], mat.Values[2][2]);
	}

	void RenderedDirectionalLightObject3DProxy::CalcShadowMatrix(Vector3DF viewPosition, Vector3DF viewDirection, Vector3DF viewUp, Matrix44 matCameraProj, float zn, float zf, Matrix44& lightView, Matrix44& lightProjection)
	{
		auto calcCubeClipMatrix = [this](Vector3DF& max_, Vector3DF& min_)->Matrix44
		{
			Matrix44 matCubeClip;
			matCubeClip.SetIdentity();
			matCubeClip.Values[0][0] = 2.0f / (max_.X - min_.X);
			matCubeClip.Values[0][1] = 0.0f;
			matCubeClip.Values[0][2] = 0.0f;
			matCubeClip.Values[0][3] = -(max_.X + min_.X) / (max_.X - min_.X);

			matCubeClip.Values[1][0] = 0.0f;
			matCubeClip.Values[1][1] = 2.0f / (max_.Y - min_.Y);
			matCubeClip.Values[1][2] = 0.0f;
			matCubeClip.Values[1][3] = -(max_.Y + min_.Y) / (max_.Y - min_.Y);

			if (deviceType == GraphicsDeviceType::DirectX11)
			{
				matCubeClip.Values[2][0] = 0.0f;
				matCubeClip.Values[2][1] = 0.0f;
				matCubeClip.Values[2][2] = -1.0f / (max_.Z - min_.Z);
				matCubeClip.Values[2][3] = min_.Z / (max_.Z - min_.Z) + 1.0f;
			}
			else
			{
				matCubeClip.Values[2][0] = 0.0f;
				matCubeClip.Values[2][1] = 0.0f;
				matCubeClip.Values[2][2] = -2.0f / (max_.Z - min_.Z);
				matCubeClip.Values[2][3] = (max_.Z + min_.Z) / (max_.Z - min_.Z);
			}

			return matCubeClip;
		};

		// LiSPSMで行列を計算する。

		// 初期化
		auto lightDirection = GetDirection();
		viewDirection.Normalize();
		lightDirection.Normalize();

		m_shadowObjectPoints.clear();

		// ライトビューに含むオブジェクトの座標算出
		auto matCPInv = matCameraProj.GetInverted();
		/*
		if (deviceType == GraphicsDeviceType::DirectX11)
		{
			Vector3DF points[8] = {
				Vector3DF(1.0f, 1.0f, 0.0f),
				Vector3DF(-1.0f, 1.0f, 0.0f),
				Vector3DF(1.0f, -1.0f, 0.0f),
				Vector3DF(-1.0f, -1.0f, 0.0f),
				Vector3DF(1.0f, 1.0f, 1.0f),
				Vector3DF(-1.0f, 1.0f, 1.0f),
				Vector3DF(1.0f, -1.0f, 1.0f),
				Vector3DF(-1.0f, -1.0f, 1.0f),
			};

			for (int32_t i = 0; i < 8; i++)
			{
				points[i] = matCPInv.Transform3D(points[i]);
				m_shadowObjectPoints.push_back(points[i]);
			}
		}
		else
		*/
		{
			Vector3DF points[8] = {
				Vector3DF(1.0f, 1.0f, -1.0f),
				Vector3DF(-1.0f, 1.0f, -1.0f),
				Vector3DF(1.0f, -1.0f, -1.0f),
				Vector3DF(-1.0f, -1.0f, -1.0f),
				Vector3DF(1.0f, 1.0f, 1.0f),
				Vector3DF(-1.0f, 1.0f, 1.0f),
				Vector3DF(1.0f, -1.0f, 1.0f),
				Vector3DF(-1.0f, -1.0f, 1.0f),
			};

			for (int32_t i = 0; i < 8; i++)
			{
				points[i] = matCPInv.Transform3D(points[i]);
				m_shadowObjectPoints.push_back(points[i]);
			}
		}

		m_shadowObjectPointsBack = m_shadowObjectPoints;
		auto back2 = m_shadowObjectPoints;

		// LiSPSMかUSMか
		auto vlC = Vector3DF::Dot(viewDirection, lightDirection);
		auto vlAngle = acos(vlC);

		if (fabsf(vlAngle) < 0.01f || fabsf(vlAngle - PI) < 0.01f)
		{
			// 視線とライトの方向が近い場合はUSM

			// ライトビューの計算
			auto eye = viewPosition;
			lightView.SetLookAtRH(eye, eye + lightDirection, viewUp);

			// AABB計算
			for (auto i = 0; i < m_shadowObjectPoints.size(); i++)
			{
				m_shadowObjectPoints[i] = lightView.Transform3D(m_shadowObjectPoints[i]);
			}

			Vector3DF min_, max_;
			CalcAABB(m_shadowObjectPoints, max_, min_);

			lightProjection = calcCubeClipMatrix(max_, min_);

			// デバッグ用
			/*
			for (auto i = 0; i < m_shadowObjectPoints.size(); i++)
			{
			m_shadowObjectPoints[i] = lightProjection.Transform3D(m_shadowObjectPoints[i]);
			}


			{
			Vector3DF points[8] = {
			Vector3DF(0.5f, 0.5f, -0.5f),
			Vector3DF(-0.5f, 0.5f, -0.5f),
			Vector3DF(0.5f, -0.5f, -0.5f),
			Vector3DF(-0.5f, -0.5f, -0.5f),
			Vector3DF(0.5f, 0.5f, 0.5f),
			Vector3DF(-0.5f, 0.5f, 0.5f),
			Vector3DF(0.5f, -0.5f, 0.5f),
			Vector3DF(-0.5f, -0.5f, 0.5f),
			};

			for (int32_t i = 0; i < 8; i++)
			{
			back2.push_back(points[i]);
			}
			}

			auto back = back2;
			auto lvp = lightProjection * lightView;
			{
			for (auto i = 0; i < back2.size(); i++)
			{
			back2[i] = lvp.Transform3D(back2[i]);
			}
			}
			*/
			return;
		}

		auto sinGamma = sqrtf(1.0f - vlC * vlC);

		// Upの計算
		auto upLeft = Vector3DF::Cross(lightDirection, viewDirection);
		auto up = Vector3DF::Cross(upLeft, lightDirection);
		up.Normalize();

		// Eyeの計算
		auto eye = viewPosition;

		// ライトビューの計算
		lightView.SetLookAtRH(eye, eye + lightDirection, up);

		// AABB計算
		for (auto i = 0; i < m_shadowObjectPoints.size(); i++)
		{
			m_shadowObjectPoints[i] = lightView.Transform3D(m_shadowObjectPoints[i]);
		}

		Vector3DF min_, max_;
		CalcAABB(m_shadowObjectPoints, max_, min_);


		// 視錐台計算
		const float factor = 1.0f / sinGamma;
		const float z_n = factor * zn;
		const float d = abs(max_.Y - min_.Y);

#if 0
		// New Formula written in ShaderX4
		const float z0 = -z_n;
		const float z1 = -(z_n + d * sinGamma);
		const float n = d / (sqrtf(z1 / z0) - 1.0f);
#else
		// Old Formula written in papers
		const float z_f = z_n + d * sinGamma;
		const float n = (z_n + sqrtf(z_f * z_n)) * factor;
#endif
		const float f = n + d;

		// ライトビューの位置補正
		auto pos = eye - up * (n - zn);
		lightView.SetLookAtRH(pos, (pos + lightDirection), up);

		// Y方向への射影行列を取得
		Matrix44 matPerspective;
		{
			// [1,	0,	0,	0]
			// [0,	a,	0,	b]
			// [0,	0,	1,	0]
			// [0,	1,	0,	0]
			// a = (f + n) / (f - n)
			// b = -2.0f * n * f / (f - n)

			matPerspective.SetIdentity();
			matPerspective.Values[1][1] = (f + n) / (f - n);
			matPerspective.Values[3][1] = 1.0f;
			matPerspective.Values[1][3] = -2.0f * n * f / (f - n);
			matPerspective.Values[3][3] = 0.0f;
		}

		// 透視変換後の空間へ変換する
		Matrix44 lightProjection_ = matPerspective * lightView;

		// AABBを計算
		for (auto i = 0; i < m_shadowObjectPointsBack.size(); i++)
		{
			m_shadowObjectPointsBack[i] = lightProjection_.Transform3D(m_shadowObjectPointsBack[i]);
		}

		Vector3DF min__, max__;
		CalcAABB(m_shadowObjectPointsBack, max__, min__);

		Matrix44 matCubeClip = calcCubeClipMatrix(max__, min__);

		lightProjection = matCubeClip * matPerspective;

		// デバッグ用コード
		/*
		{
		Vector3DF points[8] = {
		Vector3DF(0.5f, 0.5f, -0.5f),
		Vector3DF(-0.5f, 0.5f, -0.5f),
		Vector3DF(0.5f, -0.5f, -0.5f),
		Vector3DF(-0.5f, -0.5f, -0.5f),
		Vector3DF(0.5f, 0.5f, 0.5f),
		Vector3DF(-0.5f, 0.5f, 0.5f),
		Vector3DF(0.5f, -0.5f, 0.5f),
		Vector3DF(-0.5f, -0.5f, 0.5f),
		};

		for (int32_t i = 0; i < 8; i++)
		{
		back2.push_back(points[i]);
		}
		}

		auto back = back2;
		auto lvp = lightProjection * lightView;
		{
		for (auto i = 0; i < back2.size(); i++)
		{
		back2[i] = lvp.Transform3D(back2[i]);
		}
		}
		*/
	}

	RenderedDirectionalLightObject3D::RenderedDirectionalLightObject3D(Graphics* graphics)
		: RenderedObject3D(graphics)
	{
		color = Color(255, 255, 255, 255);
		proxy = new RenderedDirectionalLightObject3DProxy(graphics);
	}

	RenderedDirectionalLightObject3D::~RenderedDirectionalLightObject3D()
	{
		SafeRelease(proxy);
	}

	void RenderedDirectionalLightObject3D::Flip(float deltaTime)
	{
		RenderedObject3D::Flip(deltaTime);
		proxy->LightColor = color;
		proxy->Intensity = intensity;
	}

	float RenderedDirectionalLightObject3D::GetIntensity()
	{
		return intensity;
	}

	void RenderedDirectionalLightObject3D::SetIntensity(float intensity)
	{
		this->intensity = intensity;
	}

	Color RenderedDirectionalLightObject3D::GetColor()
	{
		return color;
	}

	void RenderedDirectionalLightObject3D::SetColor(Color color)
	{
		this->color = color;
	}
}
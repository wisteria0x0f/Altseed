﻿
#pragma once

#include <Math/asd.Vector2DI.h>
#include <Math/asd.Vector3DF.h>

#include "asd.RenderedObject3D.h"

namespace asd
{
	class RenderedCameraObject3DProxy
		: public RenderedObject3DProxy
	{
		friend class RenderedCameraObject3D;

	private:
		GraphicsDeviceType	deviceType;

		RenderTexture2D_Imp*	m_renderTargetDiffuseColor_RT = nullptr;
		RenderTexture2D_Imp*	m_renderTargetSmoothness_Metalness_AO_RT = nullptr;
		RenderTexture2D_Imp*	m_renderTargetNormalDepth_RT = nullptr;
		RenderTexture2D_Imp*	m_renderTargetAO_MatID_RT = nullptr;

		RenderTexture2D_Imp*	m_renderTargetSSAO_RT = nullptr;
		RenderTexture2D_Imp*	m_renderTargetSSAO_temp_RT = nullptr;
		RenderTexture2D_Imp*	m_renderTargetShadow_RT = nullptr;
		DepthBuffer_Imp*		m_depthBuffer_RT = nullptr;

		RenderTexture2D_Imp*	m_renderTarget_FR[2];

		RenderTexture2D_Imp*	m_renderTargetEnvironment = nullptr;

		PostEffectRenderer*		m_postEffectRenderer = nullptr;
		std::vector<std::shared_ptr<Material2DCommand>>	m_postEffectCommands_RT;
		int32_t					postEffectCount = 0;

	public:
		float ZFar = 0.0f;
		float ZNear = 0.0f;
		float FOV = 0.0f;

		bool IsProjectionMatSet = false;
		
		Vector3DF Focus;
		Matrix44	CameraMatrix;
		Matrix44	ProjectionMatrix;
		Vector2DI	WindowSize;
		Vector3DF	Up;


		RenderTexture2D_Imp*	RenderTargetRefraction = nullptr;
		RenderTexture2D_Imp*	RenderTargetReflection = nullptr;
		DepthBuffer_Imp*		DepthBufferReflection = nullptr;


		bool	HDRMode;

		/**
		@brief	シェーダー内の画像からカメラ座標復元
		*/
		Vector3DF	ReconstructInfo1;

		/**
		@brief	シェーダー内の画像からカメラ座標復元
		*/
		Vector4DF	ReconstructInfo2;

		Vector3DF	FrontDir;
		Vector3DF	UpDir;
		Vector3DF	RightDir;

		RenderedCameraObject3DProxy(Graphics* graphics);
		virtual ~RenderedCameraObject3DProxy();

		void SetWindow(Graphics* graphics, Vector2DI windowSize, bool hdrMode);

		void OnUpdateAsync() override;

		RenderTexture2D_Imp*	GetRenderTargetDiffuseColor() { return m_renderTargetDiffuseColor_RT; }
		RenderTexture2D_Imp*	GetRenderTargetSmoothness_Metalness_AO() { return m_renderTargetSmoothness_Metalness_AO_RT; }
		RenderTexture2D_Imp*	GetRenderTargetDepth() { return m_renderTargetNormalDepth_RT; }
		RenderTexture2D_Imp*	GetRenderTargetAO_MatID() { return m_renderTargetAO_MatID_RT; }
		RenderTexture2D_Imp*	GetRenderTargetShadow() { return m_renderTargetShadow_RT; }
		RenderTexture2D_Imp*	GetRenderTargetSSAO() { return m_renderTargetSSAO_RT; }
		RenderTexture2D_Imp*	GetRenderTargetSSAO_Temp() { return m_renderTargetSSAO_temp_RT; }

		RenderTexture2D_Imp*	GetRenderTargetEnvironment() { return m_renderTargetEnvironment; }

		DepthBuffer_Imp*		GetDepthBuffer() { return m_depthBuffer_RT; }
		RenderTexture2D_Imp*	GetRenderTarget();
		RenderTexture2D_Imp*	GetAffectedRenderTarget();
		void ApplyPostEffects(RenderingCommandHelper* helper);

		RenderedObject3DType GetObjectType() const override { return RenderedObject3DType::Camera; }
	};


	class RenderedCameraObject3D
		: public RenderedObject3D
	{
	private:

		struct
		{
			float	zfar;
			float	znear;
			float	fov;

			Vector2DI	size;
			Vector3DF	focus;

			bool		isProjectionMatSet;
			Matrix44	projectionMat;

			bool	hdrMode;

			int32_t	postEffectCount;

		} m_values;

		std::vector<std::shared_ptr<Material2DCommand>>	m_postEffectCommands;

		RenderedCameraObject3DProxy* proxy = nullptr;

	public:
		RenderedCameraObject3D(Graphics* graphics);
		virtual ~RenderedCameraObject3D();

		void Flip(float deltaTime) override;

		RenderedObject3DProxy* GetProxy() const override { return proxy; }

		Vector2DI GetWindowSize() const { return m_values.size; }
		void SetWindowSize( const Vector2DI& size );

		Vector3DF GetFocus(){ return m_values.focus; }
		void SetFocus(const Vector3DF& focus);

		float GetFieldOfView(){ return m_values.fov; }
		void SetFieldOfView(float fov);

		float GetZFar() { return m_values.zfar; }
		void SetZFar(float zfar);

		float GetZNear(){ return m_values.znear; }
		void SetZNear(float znear);

		Matrix44 GetProjectionMatrixDirectly(){ return m_values.projectionMat; }
		void SetProjectionMatrixDirectly(Matrix44 projectionMatrix)
		{
			m_values.projectionMat = projectionMatrix;
			m_values.isProjectionMatSet = true;
		}

		bool GetHDRMode() const;
		void SetHDRMode(bool value);

		void StartAddingPostEffect(int32_t postEffectCount);
		void AddPostEffectCommand(std::shared_ptr<Material2DCommand> command);

		/**
			@brief	ポストエフェクト設定時の出力先を取得する。
			@param	count	現在の描画回数
			@note
			別スレッドで描画に使用されている可能性が高いので注意する。
		*/
		RenderTexture2D* GetDstForPostEffect(int32_t count);

		/**
		@brief	ポストエフェクト設定時の出力元を取得する。
		@param	count	現在の描画回数
		@note
		別スレッドで描画に使用されている可能性が高いので注意する。
		*/
		RenderTexture2D* GetSrcForPostEffect(int32_t count);

		RenderedObject3DType GetObjectType() const override { return RenderedObject3DType::Camera; }
	};
}
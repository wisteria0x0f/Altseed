﻿
#pragma once

#include <ace.common.Base.h>

#include <Math/ace.Vector2DI.h>
#include <Math/ace.Vector2DF.h>
#include <Math/ace.Vector3DF.h>
#include <Math/ace.Vector4DF.h>
#include <Math/ace.Matrix44.h>
#include <Graphics/ace.Color.h>

#include "../../ace.RenderingThread.h"

#include "../../../ace.Core.Base.h"
#include "../../../ace.Core.Base_Imp.h"

namespace ace
{
	/**
		@brief	レンダラー
		@note
		ライトウエイトレンダラー
		ディレクショナルライト1、半球ライト1のみ、影等なし
	*/
	class Renderer3D
	{
	private:

		class RenderingEvent
			: public RenderingThreadEvent
		{
			Renderer3D*	m_renderer;
		public:
			RenderingEvent(Renderer3D* renderer);
			virtual ~RenderingEvent();
			void Event() override;
		};

		Graphics_Imp*	m_graphics;
		RenderSettings	m_settings;

		std::set<RenderedObject3D*>	objects;
		std::set<RenderedObject3D*>	newObjects;
		std::set<RenderedObject3D*>	removingObjects;

		Color						m_skyAmbientColor;
		Color						m_groundAmbientColor;

		Vector2DI					m_windowSize;

		RenderTexture2D_Imp*		m_renderTarget;


		Effekseer::Manager*						m_effectManager = nullptr;
		EffekseerRenderer::Renderer*			m_effectRenderer = nullptr;

		RenderingEvent	m_event;
		float	deltaTime = 0.0f;

		RenderingCommandExecutor*				executor = nullptr;
		Renderer3DProxy*						proxy = nullptr;

	public:

		Renderer3D(Graphics* graphics, RenderSettings settings);
		~Renderer3D();

		RenderSettings GetRenderSettings() const;
		void SetRenderSettings(RenderSettings settings);

		void SetWindowSize(Vector2DI windowSize);

		void AddObject(RenderedObject3D* o);
		void RemoveObject(RenderedObject3D* o);

		void Flip();

		void BeginRendering(float deltaTime);
		void EndRendering();

		void SetSkyAmbientColor(Color color) { m_skyAmbientColor = color; }
		void SetGroundAmbientColor(Color color) { m_groundAmbientColor = color; }

		RenderTexture2D_Imp* GetRenderTarget();

		Effekseer::Manager*	GetEffectManager() { return m_effectManager; }
	};
}
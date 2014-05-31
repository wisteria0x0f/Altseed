﻿#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------

#include <Math/ace.Vector2DI.h>

#include <Graphics/Font/ace.AffLoader.h>
#include <Graphics/Font/ace.GlyphData.h>
#include "ace.Texture2D.h"
#include "ace.Font.h"
#include "../ace.DeviceObject.h"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace ace {
	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	class Font_Imp
		: public Font
		, public DeviceObject
	{
	protected:

		Graphics *m_graphics;

		std::vector<std::shared_ptr<Texture2D>> m_textures;
		std::map<achar, GlyphData> m_glyphs;

	public:
		const GlyphData GetGlyphData(achar c);
		// リロード
		void Reload(const achar* affFilePath);

		Font_Imp(Graphics* graphics, const achar* affFilePath);
		virtual ~Font_Imp();

		// IReferenceを継承したデバイスオブジェクト向け定義
#if !SWIG
	public:
		virtual int GetRef() { return ReferenceObject::GetRef(); }
		virtual int AddRef() { return ReferenceObject::AddRef(); }
		virtual int Release() { return ReferenceObject::Release(); }
#endif
	};

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
}
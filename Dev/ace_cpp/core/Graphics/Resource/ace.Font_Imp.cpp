﻿//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include "ace.Font_Imp.h"
#include "../ace.Graphics_Imp.h"
#include "../ace.GraphicsResourceContainer.h"


#define Z_SOLO
#include <png.h>
#include <pngstruct.h>
#include <pnginfo.h>

#if _WIN32
#if _DEBUG
#pragma comment(lib,"libpng16.Debug.lib")
#pragma comment(lib,"zlib.Debug.lib")
#else
#pragma comment(lib,"libpng16.Release.lib")
#pragma comment(lib,"zlib.Release.lib")
#endif
#endif

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace ace {

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	Font_Imp::Font_Imp(Graphics* graphics, const achar* affFilePath)
		: DeviceObject(graphics)
	{
		AffLoader affLoader = AffLoader(ace::astring(affFilePath));
		m_glyphs = affLoader.GetGlyphs();
	}

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
	Font_Imp::~Font_Imp()
	{

	}

	//----------------------------------------------------------------------------------
	//
	//----------------------------------------------------------------------------------
}
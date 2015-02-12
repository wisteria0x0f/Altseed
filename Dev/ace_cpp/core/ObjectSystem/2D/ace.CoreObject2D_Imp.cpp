﻿
#include "ace.CoreObject2D_Imp.h"
#include "../../Graphics/ace.Graphics_Imp.h"
#include "ace.CoreTextureObject2D_Imp.h"
#include "ace.CoreCameraObject2D_Imp.h"
#include "ace.CoreTextObject2D_Imp.h"
#include "ace.CoreMapObject2D_Imp.h"
#include "ace.CoreEffectObject2D_Imp.h"

namespace ace
{

	CoreObject2D_Imp::CoreObject2D_Imp(Graphics_Imp* graphics)
		: m_graphics(graphics)
		, m_objectInfo(ObjectInfo2D())
		, m_transform(TransformInfo2D())
		, cullingObject(nullptr)
	{
		SafeAddRef(m_graphics);
		alreadyCullingUpdated = false;
	}

	CoreObject2D_Imp::~CoreObject2D_Imp()
	{
		SafeRelease(m_graphics);
	}

	void CoreObject2D_Imp::SetCullingUpdate(CoreObject2D_Imp* obj)
	{
#if __CULLING_2D__

		if (children.find(nullptr) != children.end())
		{
			children.erase(nullptr);
		}

		if (m_objectInfo.GetLayer() == nullptr) return;

		auto layerImp = (CoreLayer2D_Imp*)m_objectInfo.GetLayer();

		if (!obj->GetAlreadyCullingUpdated())
		{
			layerImp->TransformedObjects.push_back(obj->GetCullingObject());
			obj->SetAlreadyCullingUpdated(true);
		}

		auto cldrn = obj->children;

		for (auto& cld : cldrn)
		{
			auto cld_Imp = CoreObject2DToImp(cld);
			SetCullingUpdate(cld_Imp);
		}
#endif
	}

	culling2d::Circle& CoreObject2D_Imp::GetBoundingCircle()
	{
		return m_boundingCircle;
	}

	CoreObject2D_Imp* CoreObject2D_Imp::CoreObject2DToImp(CoreObject2D* obj)
	{
		if (obj == nullptr) return nullptr;

		switch (obj->GetObjectType())
		{
		case Object2DType::Texture:
			return (CoreTextureObject2D_Imp*)obj;
		case Object2DType::Text:
			return (CoreTextObject2D_Imp*)obj;
		case Object2DType::Camera:
			return (CoreCameraObject2D_Imp*)obj;
		case Object2DType::Map:
			return (CoreMapObject2D_Imp*)obj;
		case Object2DType::Effect:
			return (CoreEffectObject2D_Imp*)obj;
		default:
			break;
		}

		return nullptr;
	}
}
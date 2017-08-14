﻿#pragma once

#include "asd.CoreCollider2D.h"
#include "../../asd.Core.Base.h"
#include "../../ObjectSystem/2D/asd.CoreObject2D_Imp.h"
#include <Culling2D_AABB.h>
#include "../../asd.ReferenceObject.h"
#include "asd.CoreCollision2DManager.h"

namespace asd {

	class CoreCollider2D_Imp
	{
	private:
		astring tag;
	public:
		void SetOwnerObject2D(CoreObject2D_Imp* ownerObject);
		CoreObject2D_Imp* GetOwnerObject2D();
	protected:
		CoreObject2D_Imp* ownerObject;
		culling2d::RectF aabb;
		culling2d_aabb::Object *cullingObject;
		CoreCollision2DManager *coreCollision2DManager;

	protected:
		bool isNeededUpdateShapes;

	public:
		virtual void Update() = 0;
		virtual Collider2DShapeType GetType() const = 0;

		CoreCollider2D_Imp();
		virtual ~CoreCollider2D_Imp();
#if !SWIG
		static CoreCollider2D_Imp* CoreCollider2DToImp(CoreCollider2D* obj);
		static CoreCollider2D* CoreCollider2DImpToAbstract(CoreCollider2D_Imp* obj);

		virtual void OnAddedToObject(CoreObject2D_Imp*);
		virtual void OnRemovedFromObject(CoreObject2D_Imp*);
		virtual void OnOwnerObjectTransformChanged(CoreObject2D_Imp*);

		void SetCullingObject(culling2d_aabb::Object*);
		culling2d_aabb::Object* GetCullingObject();

		culling2d_aabb::RectF GetAABB();
		void SetAABB(culling2d_aabb::RectF aabb);

		virtual b2Shape* GetB2Shape() = 0;

		void SetCollisionManager(CoreCollision2DManager *collision2DManager);
		CoreCollision2DManager* GetCollisionManager();

		virtual void DrawVisibleCollisionsAdditionally(CoreLayer2D*) = 0;
#endif
	};
};

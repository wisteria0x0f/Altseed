﻿#pragma once

#include <vector>
#include <unordered_set>
#include <set>
#include <memory>
#include "asd.CoreCollision2D.h"
#include "Culling2D_AABB.h"

namespace asd {

	using namespace std;
	class CoreCollider2D;
	class CoreCollider2D_Imp;

	class CoreCollision2DManager {

		class CoreCollider2DManagerListener;

		unordered_set<CoreCollider2D*> registeredColliders;
		unordered_set<CoreCollider2D_Imp*> registeredCollidersImp;
		unordered_set<CoreCollision2D*, CoreCollision2D::HashFunctor> registeredCollisions;
		unordered_set<CoreCollider2D_Imp*> lastTransformedColliders;
		culling2d_aabb::World *cullingWorld;
	public:

		CoreCollision2DManager();
		virtual ~CoreCollision2DManager();

		void RegisterCollider(CoreCollider2D* collider);
		void UnregisterCollider(CoreCollider2D* collider);

		void NotifyLastTransformed(CoreCollider2D_Imp* collider);

		void UpdateCollisionState();
	};
}
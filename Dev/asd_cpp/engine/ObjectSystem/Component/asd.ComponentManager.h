﻿#pragma once
#include <memory>
#include <map>
#include <list>
#include "../../asd.CoreToEngine.h"
#include "../../asd.Engine.h"
#include "../Registration/asd.IComponentRegisterable.h"
#include "../Registration/asd.IImmediateComponentManager.h"
#include "../Registration/asd.EventToManageComponent.h"

namespace asd
{
	template<typename TComponent>
	class ComponentManager
		: public std::enable_shared_from_this<ComponentManager<TComponent>>
		, public IImmediateComponentManager<TComponent>
	{
	private:
		typedef std::shared_ptr<TComponent> ComponentPtr;

		IComponentRegisterable<TComponent>* m_owner;
		std::map<astring, ComponentPtr> m_components;

	public:
		typedef std::shared_ptr<ComponentManager<TComponent>> Ptr;

		ComponentManager(IComponentRegisterable<TComponent>* owner)
			: m_owner(owner)
			, m_components(std::map<astring, ComponentPtr>())
		{
		}

		void Add(const ComponentPtr& component, astring key)
		{
			ACE_ASSERT(component != nullptr, "nullptrをコンポーネントとして追加することはできません。");

			auto e = EventToManageComponent<TComponent>::GetAddEvent(
				std::static_pointer_cast<IImmediateComponentManager<TComponent>>(this->shared_from_this()),
				component, key);
			Engine::m_changesToCommit.push(e);
		}

		bool Remove(astring key)
		{
			auto c = Get(key);
			if (c != nullptr)
			{
				auto e = EventToManageComponent<TComponent>::GetRemoveEvent(this->shared_from_this(), key);
				Engine::m_changesToCommit.push(e);
				return true;
			}
			return false;
		}

		void ImmediatelyAddComponent(const ComponentPtr& component, astring key)
		{
			m_components[key] = component;
			m_owner->Register(component);
			component->SetKey(key);
		}

		void ImmediatelyRemoveComponent(astring key)
		{
			auto component = m_components[key];
			m_components.erase(key);
			m_owner->Unregister(component);
			component->SetKey(ToAString(""));
		}

		ComponentPtr Get(astring key)
		{
			auto it = m_components.find(key);
			if (it != m_components.end())
			{
				return it->second;
			}

			return nullptr;
		}

		const std::map<astring, ComponentPtr>& GetComponents() const
		{
			return m_components;
		}
	};
}
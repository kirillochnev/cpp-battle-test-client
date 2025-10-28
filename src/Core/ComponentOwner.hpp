//
// Created by kirill on 10/28/2025.
//

#pragma once

#include <map>
#include <any>
#include <typeindex>

namespace sw
{
	class ComponentOwner
	{
	public:
		template <typename TComponent>
		TComponent& getOrCreateComponent() {
			static auto index = componentId<TComponent>();
			auto it = _components.find(index);
			if (it == _components.end())
			{
				it = _components.emplace(index, std::make_any<TComponent>()).first;
			}
			return std::any_cast<TComponent&>(it->second);
		}

		template <typename TComponent, typename... ARGS>
		TComponent& addComponent(ARGS&&... args) {
			static auto index = componentId<TComponent>();
			auto& component = _components[index];
			component = std::make_any<TComponent>(std::forward<ARGS>(args)...);
			return std::any_cast<TComponent&>(component);
		}

		template <typename TComponent>
		TComponent* getComponent()
		{
			static auto index = componentId<TComponent>();
			auto it = _components.find(index);
			if (it == _components.end())
			{
				return nullptr;
			}
			return &std::any_cast<TComponent&>(it->second);
		}

		template <typename TComponent>
		const TComponent* getComponent() const
		{
			static auto index = componentId<TComponent>();
			auto it = _components.find(index);
			if (it == _components.end())
			{
				return nullptr;
			}
			return &std::any_cast<const TComponent&>(it->second);
		}


		template <typename TComponent>
		void remove()
		{
			static auto index = componentId<TComponent>();
			_components.erase(index);
		}

		template <typename TComponent>
		bool hasComponent() const
		{
			return getComponent<TComponent>() != nullptr;
		}

	private:

		template <typename TComponent>
		static auto componentId() noexcept
		{
			static const auto index = std::type_index(typeid(TComponent));
			return index;
		}

		std::map<std::type_index, std::any> _components;
	};
}


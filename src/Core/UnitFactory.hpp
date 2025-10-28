//
// Created by kirill on 10/28/2025.
//

#pragma once

#include <Core/Types.hpp>
#include <Core/Unit.hpp>
#include <Utils/function_traits.hpp>

#include <any>
#include <map>
#include <string>
#include <functional>

namespace sw
{
	class UnitFactory : Uncopiable
	{
	public:
		using UnitAllocator = std::function<UnitPtr (Game&, const std::any&)>;

		explicit UnitFactory(Game& game);
		~UnitFactory();

		bool unRegisterUnitKind(const std::string& kind);
		bool registerUnitKind(const std::string& kind, const UnitAllocator& allocator);

		template <typename TAllocator>
		bool registerUnitKind(const std::string& kind, TAllocator&& allocator)
		{
			if (!allocator)
			{
				return false;
			}
			_allocators[kind] = [allocator](Game& game, const std::any& data) {
				using ArgType = typename utils::function_traits<TAllocator>::template arg<1>::type;
				return allocator(game, std::any_cast<ArgType>(data));
			};
			return true;
		}

		Unit* allocateUnit(const std::string& kind, const std::any& data);
	private:
		void onError(const std::string& unitKind, const std::any& data, const std::string_view& reason) const;

		Game& _game;
		std::map<std::string, UnitAllocator> _allocators;
	};
}

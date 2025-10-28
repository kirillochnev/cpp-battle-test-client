//
// Created by kirill on 10/24/2025.
//

#pragma once

#include <cstdint>
#include <compare>

namespace sw
{
	using Real = int32_t;
	using Id = uint32_t;


	class Game;
	class Unit;
	class RuleBook;
	class ICommand;
	class IAbility;
	class BattleField;
	struct Position;
	
	enum class InteractionType : uint32_t {
		kUnknown = 0,
		kSelect,
		kMeleeAttack,
		kRangeAttach,
		kAoeAttach,
		kMovement,
		kVisibility
	};
	enum class AttributeType : uint32_t {
		kHp,
		kStr,
		kAgl,
		kSpeed
	};

	class Uncopiable {
	public:
		Uncopiable() = default;
		Uncopiable(Uncopiable&&) = default;
		Uncopiable(const Uncopiable&) = delete;
		Uncopiable& operator=(const Uncopiable&) = delete;
		Uncopiable& operator=(Uncopiable&&) = default;
	};

}

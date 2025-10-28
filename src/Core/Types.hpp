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

	enum class AttributeType : uint32_t {
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

	struct Point
	{
		Real x;
		Real y;

		auto operator<=>(const Point&) const = default;

		// to handle unsigned Real data type
		Point absDiff(const Point& rhs) const noexcept
		{
			return {
				x > rhs.x ? x - rhs.x : rhs.x - x,
				y > rhs.y ? y - rhs.y : rhs.y - y
			};
		}

		// ChebyshevDistanceRule
		Real distanceTo(const Point& rhs) const noexcept
		{
			const auto delta = absDiff(rhs);
			return delta.x > delta.y ? delta.x : delta.y;
		}
	};
}

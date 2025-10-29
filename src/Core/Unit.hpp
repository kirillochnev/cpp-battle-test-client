//
// Created by kirill on 10/28/2025.
//

#pragma once

#include <Core/Types.hpp>
#include <Core/GameRule.hpp>

namespace sw
{
	class Unit
	{
		UnitId _id = 0;
		const Game* _game = nullptr;
		mutable UnitObject* _object = nullptr;
	public:
		Unit(UnitObject&);
		Unit(UnitObject*);
		Unit(std::nullptr_t){};
		Unit() = default;
		Unit(UnitId id, const Game* game = nullptr, UnitObject* object = nullptr);

		[[nodiscard]] operator bool() const noexcept;
		[[nodiscard]] bool isValid() const noexcept;

		UnitObject* get() noexcept;
		const UnitObject* get() const noexcept;
		UnitObject& operator*() noexcept {return *get();}
		const UnitObject& operator*() const noexcept {return *get();}

		const UnitObject* operator->() const noexcept {return get();}
		UnitObject* operator->() noexcept {return get();}

		bool operator==(const Unit& rhs) const noexcept {return _id == rhs._id;}
	};


	class DoesUnitBlockCeilRule : public GameRule
	{
	public:
		using ResultType = bool;
		virtual bool tryExecute(bool&, Unit unit);
	};

	class UnitPlaceRule : public GameRule
	{
	public:
		using ResultType = void;
		virtual bool tryExecute(BattleField&, Unit unit, Position position);
	};

	class UnitRemovedRule : public GameRule
	{
	public:
		using ResultType = void;
		virtual bool tryExecute(BattleField&, Unit unit);
	};

	class UnitMovedRule : public GameRule
	{
	public:
		using ResultType = void;
		virtual bool tryExecute(BattleField&, Unit unit, Position from, Position to);
	};

	class UnitsActInFrameOfCreation : public GameRule
	{
	public:
		using ResultType = bool;
		virtual bool tryExecute(ResultType& out);
	};
}

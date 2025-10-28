//
// Created by kirill on 10/28/2025.
//

#pragma once

#include <Core/Types.hpp>
#include <Core/GameRule.hpp>
#include <Core/ComponentOwner.hpp>
#include <Core/AttributeOwner.hpp>

#include <any>
#include <map>
#include <memory>
#include <vector>
#include <typeindex>

namespace sw
{
	class Unit : public ComponentOwner, public AttributeOwner
	{
	public:
		Unit(Unit&&) = default;
		explicit Unit(Id id, Point position);

		virtual ~Unit();

		Point position() const
		{
			return _position;
		}

		virtual void setPosition(Point value);

		virtual void update();

		template <typename TAbility, typename... ARGS>
		TAbility& addAbility(ARGS&&... args)
		{
			_abilities.emplace_back(std::make_unique<TAbility>(std::forward<ARGS>(args)...));
			sortAbilities();
		}

		template <typename TCommand, typename... ARGS>
		TCommand& addCommand(ARGS&&... args)
		{
			auto& ref = addCommand(std::make_unique<TCommand>(std::forward<ARGS>(args)...));
			return static_cast<TCommand&>(ref);
		}

		[[nodiscard]] Id id() const noexcept {return _id;}
		[[nodiscard]] bool wasInit() const noexcept {return _game && _battleField;}
		[[nodiscard]] Game* game() const noexcept {return _game;}
		[[nodiscard]] BattleField* battleField() const noexcept {return _battleField;}
	protected:
		virtual void processCommands();
		virtual void processAbilities();

		friend Game;
		void init(Game& game, BattleField& _battleField);

		virtual ICommand& addCommand(std::unique_ptr<ICommand>&& command);
		void sortAbilities();

		const Id _id;
		Point _position;
		std::vector<std::unique_ptr<IAbility> > _abilities;
		std::unique_ptr<ICommand> _commandToExecute;
		Game* _game = nullptr;
		BattleField*  _battleField = nullptr;
	};

	using UnitPtr = std::unique_ptr<Unit>;

	class DoesUnitBlockCeilRule : public GameRule
	{
	public:
		using ResultType = bool;
		virtual bool tryExecute(bool&, BattleField&, Unit& unit);
	};

	class UnitPlaceRule : public GameRule
	{
	public:
		using ResultType = void;
		virtual bool tryExecute(BattleField&, Unit& unit, Point position);
	};
	class UnitMovedRule : public GameRule
	{
	public:
		using ResultType = void;
		virtual bool tryExecute(BattleField&, Unit& unit, Point from, Point to);
	};

}

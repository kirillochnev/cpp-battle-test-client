//
// Created by kirill on 10/28/2025.
//

#pragma once

#include <Core/Types.hpp>
#include <Core/GameRule.hpp>
#include <Core/Position.hpp>
#include <Core/ComponentOwner.hpp>
#include <Core/AttributeOwner.hpp>

#include <any>
#include <map>
#include <memory>
#include <vector>
#include <typeindex>

namespace sw
{
	class UnitObject : public ComponentOwner, public AttributeOwner
	{
	public:
		UnitObject(UnitObject&&) = default;
		explicit UnitObject(UnitId id, std::string type, Position position);

		virtual ~UnitObject();

		Position position() const
		{
			return _position;
		}

		virtual void setPosition(Position value);

		template <typename TAbility, typename... ARGS>
		void addAbility(ARGS&&... args)
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
		[[nodiscard]] const std::string& type() const noexcept {return _type;}
		[[nodiscard]]
		UnitId id() const noexcept {return _id;}
		[[nodiscard]] bool wasInit() const noexcept {return _game && _battleField;}
		[[nodiscard]] Game* game() const noexcept {return _game;}
		[[nodiscard]] BattleField* battleField() const noexcept {return _battleField;}

		[[nodiscard]] bool alive() const noexcept {return _alive;}
		virtual void kill();
	protected:
		virtual void update();
		virtual void processCommands();
		virtual bool processAbilities();

		friend Game;
		virtual void init(Game& game, BattleField& _battleField);

		virtual ICommand& addCommand(std::unique_ptr<ICommand>&& command);
		void sortAbilities();

		const UnitId _id;
		std::string _type;
		Position _position;
		std::vector<std::unique_ptr<IAbility> > _abilities;
		std::unique_ptr<ICommand> _commandToExecute;
		Game* _game = nullptr;
		BattleField*  _battleField = nullptr;
		bool _alive = false;
	};


	struct UnitIdleEvent
	{
		UnitId unitId;
	};
}

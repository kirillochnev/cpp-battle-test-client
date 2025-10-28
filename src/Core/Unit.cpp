//
// Created by kirill on 10/28/2025.
//

#include "Unit.hpp"

#include "Ability.hpp"
#include "BattleField.hpp"
#include "Command.hpp"
#include "Game.hpp"
#include "GameRule.hpp"
#include "IO/Events/UnitDied.hpp"

#include <IO/Events/UnitMoved.hpp>
#include <algorithm>

using namespace sw;


Unit::Unit(Id id,std::string type, Position position) :
		_id(id),
		_type(type),
		_position(position)
{

}

Unit::~Unit()
{
	if (wasInit())
	{
		_battleField->releaseCeil(_position.x, _position.y);
		_game->ruleBook().apply<UnitRemovedRule>(*_battleField, *this);
	}
}

ICommand& Unit::addCommand(std::unique_ptr<ICommand>&& command)
{

	if (_commandToExecute && _commandToExecute->isInProgress())
	{
		_commandToExecute->terminate(*this);
	}
	_commandToExecute = std::move(command);
	_commandToExecute->start(*this);
	return *_commandToExecute;
}

void Unit::sortAbilities()
{
	std::stable_sort(_abilities.begin(), _abilities.end(), [](const auto& a, const auto& b) {
	   return a->priority() > b->priority();
	 });
}

bool Unit::update()
{
	processCommands();
	return processAbilities();
}

void Unit::init(Game& game, BattleField& battleField)
{
	_game = &game;
	_battleField = &battleField;
	_alive = true;
	game.ruleBook().apply<UnitPlaceRule>(battleField, *this, _position);
}

void Unit::processCommands()
{
	if (_commandToExecute)
	{
		_commandToExecute->update(*this);
		if (!_commandToExecute->isInProgress())
		{
			_commandToExecute.reset();
		}
	}
}

bool Unit::processAbilities()
{
	for (const auto& ability : _abilities)
	{
		if (!alive() || ability->execute(*this))
		{
			return true;
		}
	}
	return false;
}

void Unit::setPosition(Position value)
{
	if (_game && _battleField)
	{
		_game->ruleBook().apply<UnitMovedRule>(*_battleField, *this, _position, value);
		_game->eventSystem().post(io::UnitMoved{.unitId = _id, .x = (uint32_t)value.x, .y = (uint32_t)value.y});
	}
	_position = value;
}

void Unit::kill()
{
	if (wasInit())
	{
		if (alive())
		{
			_alive = false;
			_game->eventSystem().post(io::UnitDied{ .unitId = _id });
			_game->removeUnit(_id);
		}
	}
}

bool DoesUnitBlockCeilRule::tryExecute(bool& result, Unit& unit)
{
	result = true;
	return true;
}

bool UnitPlaceRule::tryExecute(BattleField& battleField, Unit& unit, Position position)
{
	if (owner().apply<DoesUnitBlockCeilRule>(unit))
	{
		battleField.blockCeil(position.x, position.y);
	}
	return true;
}

bool UnitMovedRule::tryExecute(BattleField& battleField, Unit& unit, Position from, Position to)
{
	if (owner().apply<DoesUnitBlockCeilRule>(unit))
	{
		battleField.releaseCeil(from.x, from.y);
		battleField.blockCeil(to.x, to.y);
	}
	return true;
}

bool UnitRemovedRule::tryExecute(BattleField& battleField, Unit& unit)
{
	if (owner().apply<DoesUnitBlockCeilRule>(unit))
	{
		battleField.releaseCeil(unit.position().x, unit.position().y);
	}
	return true;
}

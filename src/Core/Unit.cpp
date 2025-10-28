//
// Created by kirill on 10/28/2025.
//

#include "Unit.hpp"
#include "Ability.hpp"
#include "Game.hpp"
#include "GameRule.hpp"
#include "BattleField.hpp"
#include "Command.hpp"
#include <algorithm>

using namespace sw;


Unit::Unit(Id id, Point position) :
		_id(id),
		_position(position)
{

}

Unit::~Unit() = default;

ICommand& Unit::addCommand(std::unique_ptr<ICommand>&& command)
{

	if (_commandToExecute && _commandToExecute->isInProgress())
	{
		_commandToExecute->terminate();
	}
	_commandToExecute = std::move(command);
	return *_commandToExecute;
}

void Unit::sortAbilities()
{
	std::stable_sort(_abilities.begin(), _abilities.end(), [](const auto& a, const auto& b) {
	   return a->priority() > b->priority();
	 });
}

void Unit::update()
{
	processCommands();
	processAbilities();
}

void Unit::init(Game& game, BattleField& battleField)
{
	_game = &game;
	_battleField = &battleField;
	game.ruleBook().apply<UnitPlaceRule>(battleField, *this, _position);
}

void Unit::processCommands()
{
	if (_commandToExecute)
	{
		_commandToExecute->update();
		if (!_commandToExecute->isInProgress())
		{
			_commandToExecute.reset();
		}
	}
}

void Unit::processAbilities()
{
	for (const auto& ability : _abilities)
	{
		if (ability->execute(*this))
		{
			return;
		}
	}
}

void Unit::setPosition(Point value)
{
	if (_game && _battleField)
	{
		_game->ruleBook().apply<UnitMovedRule>(*_battleField, *this, _position, value);
	}
	_position = value;
}

bool DoesUnitBlockCeilRule::tryExecute(bool& result, BattleField&, Unit& unit)
{
	result = true;
	return true;
}

bool UnitPlaceRule::tryExecute(BattleField& battleField, Unit& unit, Point position)
{
	if (owner().apply<DoesUnitBlockCeilRule>(battleField, unit))
	{
		battleField.blockCeil(position.x, position.y);
	}
	return true;
}

bool UnitMovedRule::tryExecute(BattleField& battleField, Unit& unit, Point from, Point to)
{
	if (owner().apply<DoesUnitBlockCeilRule>(battleField, unit))
	{
		battleField.releaseCeil(from.x, from.y);
		battleField.blockCeil(to.x, to.y);
	}
	return true;
}

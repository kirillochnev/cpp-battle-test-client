//
// Created by kirill on 10/28/2025.
//

#include "UnitObject.hpp"
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

UnitObject::UnitObject(UnitId id,std::string type, Position position) :
		_id(id),
		_type(type),
		_position(position)
{
	addAbility<IdleAbility>();
}

UnitObject::~UnitObject()
{
	if (wasInit())
	{
		_battleField->releaseCeil(_position.x, _position.y);
		_game->ruleBook().apply<UnitRemovedRule>(*_battleField, *this);
	}
}

ICommand& UnitObject::addCommand(std::unique_ptr<ICommand>&& command)
{

	if (_commandToExecute && _commandToExecute->isInProgress())
	{
		_commandToExecute->terminate(*this);
	}
	_commandToExecute = std::move(command);
	_commandToExecute->start(*this);
	return *_commandToExecute;
}

void UnitObject::sortAbilities()
{
	std::stable_sort(_abilities.begin(), _abilities.end(), [](const auto& a, const auto& b) {
	   return a->priority() > b->priority();
	 });
}

void UnitObject::update()
{
	processCommands();
	processAbilities();
}

void UnitObject::init(Game& game, BattleField& battleField)
{
	_game = &game;
	_battleField = &battleField;
	_alive = true;
	game.ruleBook().apply<UnitPlaceRule>(battleField, *this, _position);
}

void UnitObject::processCommands()
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

bool UnitObject::processAbilities()
{
	for (const auto& ability : _abilities)
	{
		if (!alive() || ability->execute(*this))
		{
			_game->eventSystem().post(AbilityWasExecutedEvent{.ability = *ability, .unit = *this});
			return true;
		}
	}
	return false;
}

void UnitObject::setPosition(Position value)
{
	if (_game && _battleField)
	{
		_game->ruleBook().apply<UnitMovedRule>(*_battleField, *this, _position, value);
		_game->eventSystem().post(io::UnitMoved{.unitId = _id, .x = (uint32_t)value.x, .y = (uint32_t)value.y});
	}
	_position = value;
}

void UnitObject::kill()
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

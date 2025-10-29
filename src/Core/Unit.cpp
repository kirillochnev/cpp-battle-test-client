//
// Created by kirill on 10/28/2025.
//

#include "Unit.hpp"
#include "Game.hpp"

#include <list>

using namespace sw;


Unit::Unit(UnitId id, const Game* game, UnitObject* object):
		_id(id),
		_game(game),
		_object(object)
{
	if (_object == nullptr && _game != nullptr)
	{
		_object = _game->findUnitRaw(_id);
	}
}

bool Unit::isValid() const noexcept
{
	if (_game == nullptr)
	{
		return false;
	}
	_object = _game->findUnitRaw(_id);
	return _object != nullptr;
}

UnitObject* Unit::get() noexcept
{
	if (_object == nullptr && _game != nullptr)
	{
		_object = _game->findUnitRaw(_id);
	}
	return _object;
}

const UnitObject* Unit::get() const noexcept
{
	if (_object == nullptr && _game != nullptr)
	{
		_object = _game->findUnitRaw(_id);
	}
	return _object;
}

Unit::operator bool() const noexcept
{
	return isValid();
}

Unit::Unit(UnitObject& self):
		Unit(&self)
{

}

Unit::Unit(UnitObject* self):
	_id(self ? self->id() : 0),
	_game (self ? self->game() : 0),
	_object(self)
{

}

bool DoesUnitBlockCeilRule::tryExecute(bool& result, Unit unit)
{
	result = true;
	return true;
}

bool UnitPlaceRule::tryExecute(BattleField& battleField, Unit unit, Position position)
{
	if (owner().apply<DoesUnitBlockCeilRule>(unit))
	{
		battleField.blockCeil(position.x, position.y);
	}
	return true;
}

bool UnitMovedRule::tryExecute(BattleField& battleField, Unit unit, Position from, Position to)
{
	if (owner().apply<DoesUnitBlockCeilRule>(unit))
	{
		battleField.releaseCeil(from.x, from.y);
		battleField.blockCeil(to.x, to.y);
	}
	return true;
}

bool UnitRemovedRule::tryExecute(BattleField& battleField, Unit unit)
{
	if (owner().apply<DoesUnitBlockCeilRule>(unit))
	{
		battleField.releaseCeil(unit->position().x, unit->position().y);
	}
	return true;
}

bool UnitsActInFrameOfCreation::tryExecute(UnitsActInFrameOfCreation::ResultType& out)
{
	out = false;
	return true;
}

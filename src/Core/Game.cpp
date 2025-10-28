//
// Created by kirill on 10/28/2025.
//

#include "Game.hpp"

#include "IO/Events/UnitSpawned.hpp"
#include <IO/Events/MapCreated.hpp>

using namespace sw;

Game::Game():
		_ruleBook(*this),
		_unitFactory(*this)
{

}

Game::~Game() = default;

void Game::createBattleField(Real w, Real h)
{
	_units.clear();
	_toRemove.clear();
	_idToIndex.clear();
	_battleField = std::make_unique<BattleField>(w, h);

	_events.post(io::MapCreated{.width = (uint32_t) w, .height = (uint32_t) h});
}

Unit* Game::addUnit(UnitPtr&& unit)
{
	if (!_battleField)
	{
		throw std::runtime_error("Can not create units without battle field");
	}

	auto ptr = _units.emplace_back(std::move(unit)).get();
	ptr->init(*this, *_battleField);
	_events.post(io::UnitSpawned {
		.unitId = ptr->id(), .unitType = ptr->_type,
		.x = (uint32_t)ptr->position().x, .y = (uint32_t)ptr->position().y
	});

	// If tick is in progress, append to tick view so the new unit acts this frame
	if (_tickInProgress)
	{
		_tickUnits.push_back(ptr);
	}

	rebuildIndex();
	return ptr;
}

void Game::init()
{

}

bool Game::update()
{
	if (_units.size() < 2)
	{
		return false;
	}

	// Remove pending deletions before tick
	if (!_toRemove.empty())
	{
		erase_if(_units, [this](const auto& unit){
			return std::find(_toRemove.begin(), _toRemove.end(), unit->id()) != _toRemove.end();
		});
		_toRemove.clear();
		rebuildIndex();
	}

	_tickInProgress = true;
	_tickUnits.clear();
	_tickUnits.reserve(_units.size());
	for (const auto& u : _units)
	{
		_tickUnits.push_back(u.get());
	}

	// Update over stable view; addUnit may append to _tickUnits for same-frame activation
	bool wasAnyActions = false;
	for (size_t i = 0; i < _tickUnits.size(); ++i)
	{
		if (_tickUnits[i]->update())
		{
			wasAnyActions = true;
		}
	}

	// Apply removals from this tick
	if (!_toRemove.empty())
	{
		erase_if(_units, [this](const auto& unit){
			return std::find(_toRemove.begin(), _toRemove.end(), unit->id()) != _toRemove.end();
		});
		_toRemove.clear();
	}

	_tickInProgress = false;
	_tickUnits.clear();
	rebuildIndex();
	++_frameIndex;

	return wasAnyActions;
}

void Game::removeUnit(Id id)
{
	_toRemove.push_back(id);
}

Unit* Game::findUnit(Id id) const noexcept
{
	auto it = _idToIndex.find(id);
	if (it == _idToIndex.end())
	{
		return nullptr;
	}
	return _units[it->second].get();
}

void Game::rebuildIndex()
{
	_idToIndex.clear();
	for (size_t i = 0; i < _units.size(); ++i)
	{
		_idToIndex[_units[i]->id()] = i;
	}
}



//
// Created by kirill on 10/28/2025.
//

#include "MarchCommand.hpp"
#include <Core/Game.hpp>
#include <IO/Events/MarchEnded.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <Game/Components/MoveTarget.hpp>


using namespace sw;



MarchCommand::MarchCommand(Real x, Real y):
	_targetX(x),
	_targetY(y)
{

}


void MarchCommand::onStart(Unit& owner)
{
	owner.getOrCreateComponent<MoveTarget>() = MoveTarget{.x = _targetX, .y = _targetY};
	io::MarchStarted event;
	event.unitId = owner.id();
	event.x = owner.position().x;
	event.y = owner.position().y;
	event.targetX = _targetX;
	event.targetY = _targetY;
	owner.game()->eventSystem().post(event);
}

void MarchCommand::onFinished(Unit& owner)
{
	owner.remove<MoveTarget>();
	auto pos = owner.position();
	owner.game()->eventSystem().post(io::MarchEnded{.unitId = owner.id(), .x = (uint32_t)pos.x, .y = (uint32_t)pos.y});
}

void MarchCommand::onUpdate(Unit& owner)
{
	const auto pos = owner.position();
	if (pos.x == _targetX && pos.y == _targetY || !owner.hasComponent<MoveTarget>())
	{
		_inProgress = false;
	}
}

void MarchCommand::onTerminate(Unit& owner)
{
	onFinished(owner);
}
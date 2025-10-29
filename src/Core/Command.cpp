//
// Created by kirill on 10/28/2025.
//

#include "Command.hpp"


using namespace sw;

void sw::ICommand::update(UnitObject& owner)
{
	start(owner);

	onUpdate(owner);

	if (!isInProgress())
	{
		onFinished(owner);
	}
}

void sw::ICommand::terminate(UnitObject& owner)
{
	if (isInProgress())
	{
		onTerminate(owner);
		_inProgress = false;
	}
}

void ICommand::start(UnitObject& owner)
{
	if (!isInProgress())
	{
		onStart(owner);
		_inProgress = true;
	}
}

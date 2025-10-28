//
// Created by kirill on 10/28/2025.
//

#include "Command.hpp"


using namespace sw;

void sw::ICommand::update(Unit& owner)
{
	start(owner);

	onUpdate(owner);

	if (!isInProgress())
	{
		onFinished(owner);
	}
}

void sw::ICommand::terminate(Unit& owner)
{
	if (isInProgress())
	{
		onTerminate(owner);
		_inProgress = false;
	}
}

void ICommand::start(Unit& owner)
{
	if (!isInProgress())
	{
		onStart(owner);
		_inProgress = true;
	}
}

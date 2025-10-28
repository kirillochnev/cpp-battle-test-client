//
// Created by kirill on 10/28/2025.
//

#include "Command.hpp"


using namespace sw;

void sw::ICommand::update()
{
	if (!isInProgress())
	{
		onStart();
		_inProgress = true;
	}

	onUpdate();

	if (!isInProgress())
	{
		onFinished();
	}
}

void sw::ICommand::terminate()
{
	if (isInProgress())
	{
		onTerminate();
		_inProgress = false;
	}
}

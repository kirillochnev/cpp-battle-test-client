//
// Created by kirill on 10/28/2025.
//

#include "PathFindingRule.hpp"
#include <Core/Position.hpp>
#include <Core/Game.hpp>

bool sw::PathFindingRule::tryExecute(sw::PathFindingRule::ResultType& path, Game& game, sw::Position from, sw::Position to,
									 bool ignoreCollision, const sw::Unit* optionalUnit)
{
	path.clear();

	const Real dX = (to.x > from.x) ? 1 :
					(to.x < from.x) ? -1 : 0;
	const Real dY = (to.y > from.y) ? 1 :
					(to.y < from.y) ? -1 : 0;

	if (!game.battleField())
	{
		return true;
	}

	Real dist = optionalUnit ? owner().apply<GetDistance>(*optionalUnit, to) : owner().apply<GetDistance>(from, to);
	for (int32_t i = 0; i <= dist; ++i)
	{
		Position nextStep{from.x + i * dX, from.y + i * dY};
		if (i > 0 && !ignoreCollision && !game.battleField()->isCeilAvailable(nextStep.x, nextStep.y))
		{
			return true;
		}
		path.push_back(nextStep);
	}
	return true;
}

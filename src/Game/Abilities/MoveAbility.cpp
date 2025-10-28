//
// Created by kirill on 10/28/2025.
//

#include "MoveAbility.hpp"
#include <Core/Game.hpp>
#include <Game/Components/MoveTarget.hpp>
#include <Game/Rules/PathFindingRule.hpp>

using namespace sw;


bool MoveAbility::execute(Unit& unit)
{
	auto targetPos = unit.getComponent<MoveTarget>();
	if (targetPos == nullptr)
	{
		return false;
	}
    const auto& ruleBook = unit.game()->ruleBook();
    const bool ignoreCollision = !ruleBook.apply<DoesUnitBlockCeilRule>(unit);
	auto path = ruleBook.apply<PathFindingRule>(*unit.game(), unit.position(), Position{targetPos->x, targetPos->y}, ignoreCollision, &unit);
	if (path.size() < 2)
	{
		return false;
	}
	unit.setPosition(path[1]);
	return true;
}

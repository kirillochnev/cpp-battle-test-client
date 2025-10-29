//
// Created by kirill on 10/28/2025.
//

#include "ModifyHpRule.hpp"

#include <Core/Game.hpp>

using namespace sw;

bool ModifyHpRule::tryExecute(Unit unit, Real deltaHp)
{
	if (unit)
	{
		const Real oldHp = unit->getAttribute(AttributeType::kHp);
		Real newHp = oldHp + deltaHp;
		if (newHp < 0)
		{
			newHp = 0;
		}

		unit->setAttribute(AttributeType::kHp, newHp);
		if (newHp == 0 && unit->alive())
		{
			// schedule death next tick and log
			unit->kill();
		}
	}
    return true;
}

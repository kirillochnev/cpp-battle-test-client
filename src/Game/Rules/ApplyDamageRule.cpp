//
// Created by kirill on 10/28/2025.
//

#include "ApplyDamageRule.hpp"
#include "ModifyHpRule.hpp"
#include <Core/Game.hpp>
#include <IO/Events/UnitAttacked.hpp>
#include <IO/Events/UnitDied.hpp>

using namespace sw;

bool ApplyDamageRule::tryExecute(Unit, Unit target, Real damage)
{
    if (damage <= 0)
	{
		damage = 0;
	}

    // apply HP change
    owner().apply<ModifyHpRule>(target, -damage);

    return true;
}

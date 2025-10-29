//
// Created by kirill on 10/28/2025.
//

#include "Ability.hpp"
#include <limits>

using namespace sw;

int32_t sw::IdleAbility::priority() const noexcept
{
	return std::numeric_limits<int32_t >::min();
}

bool sw::IdleAbility::execute(sw::UnitObject& self)
{
	return true;
}

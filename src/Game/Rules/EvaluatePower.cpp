//
// Created by kirill on 10/28/2025.
//

#include "EvaluatePower.hpp"

#include <Core/UnitObject.hpp>

using namespace sw;

bool EvaluatePower::tryExecute(EvaluatePower::ResultType& out, Unit caster, const IAbility&,
							   Real basePower, const std::map<AttributeType, Real>& scales, InteractionType)
{
	out = basePower;
	for (auto [attribute, scale] : scales)
	{
		out += caster->getAttribute(attribute) * scale;
	}
	return true;
}

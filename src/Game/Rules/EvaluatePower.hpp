//
// Created by kirill on 10/28/2025.
//

#pragma once

#include <Core/GameRule.hpp>

#include <map>

namespace sw
{
	class EvaluatePower : public GameRule
	{
	public:
		using ResultType = Real;
		bool tryExecute(ResultType& out, const Unit& caster, const IAbility& ability, Real basePower,
						const std::map<AttributeType, Real>& scales, InteractionType type = InteractionType::kUnknown);
	};
}

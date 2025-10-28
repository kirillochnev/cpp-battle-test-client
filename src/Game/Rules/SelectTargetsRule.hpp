//
// Created by kirill on 10/28/2025.
//

#pragma once

#include <Core/GameRule.hpp>

namespace sw
{

	class SelectTargetsRule : public GameRule
	{
	public:
		using ResultType = std::vector<Unit*>;
		virtual bool tryExecute(ResultType& out, Unit& unit, const ResultType& candidates, InteractionType type);
	};
}

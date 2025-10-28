//
// Created by kirill on 10/28/2025.
//

#include "SelectTargetsRule.hpp"
#include <Core/RundomNumber.hpp>

using namespace sw;

bool SelectTargetsRule::tryExecute(SelectTargetsRule::ResultType& out, Unit&,
								   const SelectTargetsRule::ResultType& candidates, InteractionType)
{
	if (!candidates.empty())
	{
		out.push_back(candidates[owner().apply<GetRandomNumber>(0, candidates.size() - 1)]);
	}
	return true;
}

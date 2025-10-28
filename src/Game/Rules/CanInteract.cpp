//
// Created by kirill on 10/28/2025.
//

#include "CanInteract.hpp"
#include <Core/Unit.hpp>

using namespace sw;

bool CanInteract::tryExecute(CanInteract::ResultType& out, const Unit& a, const Unit& b, InteractionType type)
{
	if ((type == InteractionType::kMeleeAttack || type == InteractionType::kRangeAttach) && a.id() == b.id())
	{
		// no self attack
		out = false;
	}
	else
	{
		out = true;
	}
	return true;
}

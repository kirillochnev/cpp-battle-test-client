//
// Created by kirill on 10/28/2025.
//

#include "CanInteract.hpp"

#include <Core/UnitObject.hpp>

using namespace sw;

bool CanInteract::tryExecute(CanInteract::ResultType& out, Unit a, Unit b, InteractionType type)
{
	if (a && b)
	{
		const auto targetAttack = type == InteractionType::kMeleeAttack || type == InteractionType::kRangeAttack;
		out = true;
		if (targetAttack && a == b)
		{
			// no self attack
			out = false;
		}

		if ((targetAttack || type == InteractionType::kAoeAttack) && !b->alive())
		{
			// rest in piece, not in pieces
			out = false;
		}
	}
	else
	{
		out = false;
	}
	return true;
}

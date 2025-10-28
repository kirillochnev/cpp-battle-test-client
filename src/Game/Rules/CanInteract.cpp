//
// Created by kirill on 10/28/2025.
//

#include "CanInteract.hpp"
#include <Core/Unit.hpp>

using namespace sw;

bool CanInteract::tryExecute(CanInteract::ResultType& out, const Unit& a, const Unit& b, InteractionType type)
{
	const auto targetAttack = type == InteractionType::kMeleeAttack || type == InteractionType::kRangeAttack;
	out = true;
	if (targetAttack && a.id() == b.id())
	{
		// no self attack
		out = false;
	}

	if ((targetAttack || type == InteractionType::kAoeAttack) && !b.alive())
	{
		// rest in piece, not in pieces
		out = false;
	}

	return true;
}

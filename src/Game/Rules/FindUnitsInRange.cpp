//
// Created by kirill on 10/28/2025.
//

#include "FindUnitsInRange.hpp"
#include "CanInteract.hpp"
#include "Core/Game.hpp"

using namespace sw;

bool FindUnitsInRange::tryExecute(FindUnitsInRange::ResultType& out, const Unit& interactor,
								  Real minRange, Real maxRange, InteractionType interactionType)
{
	const auto& ruleBook = owner();
	auto& game = ruleBook.owner();
	out.clear();
	for (const auto& unit : game.units())
	{
		const auto distance = ruleBook.apply<GetDistance>(interactor, *unit, interactionType);
		if (distance >= minRange && distance <= maxRange)
		{
			if (ruleBook.apply<CanInteract>(interactor, *unit, interactionType))
			{
				out.push_back(unit.get());
			}
		}
	}
	return true;
}

bool FindUnitsInRange::tryExecute(FindUnitsInRange::ResultType& out, Position from,
								  Real minRange, Real maxRange, InteractionType interactionType)
{
	const auto& ruleBook = owner();
	auto& game = ruleBook.owner();
	out.clear();
	for (const auto& unit : game.units())
	{
		const auto distance = ruleBook.apply<GetDistance>(*unit, from, interactionType);
		if (distance >= minRange && distance <= maxRange)
		{
			out.push_back(unit.get());
		}
	}
	return true;
}

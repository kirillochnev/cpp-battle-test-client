//
// Created by kirill on 10/28/2025.
//

#pragma once

#include <Core/GameRule.hpp>
#include <Core/Position.hpp>

namespace sw
{
	class FindUnitsInRange : public GameRule
	{

	public:
		using ResultType = std::vector<Unit*>;
		virtual bool tryExecute(ResultType& out, const Unit& interactor, Real minRange, Real maxRange,
								InteractionType interactionType = InteractionType::kUnknown);

		virtual bool tryExecute(ResultType& out, Position from, Real minRange, Real maxRange,
								InteractionType interactionType = InteractionType::kUnknown);
	};

}
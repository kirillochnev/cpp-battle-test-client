//
// Created by kirill on 10/28/2025.
//

#pragma once

#include <Core/GameRule.hpp>

namespace sw
{
	class CanInteract : public GameRule
	{
	public:
		using ResultType = bool;
		bool tryExecute(ResultType& out, const Unit& a, const Unit& b, InteractionType type);
	};

}
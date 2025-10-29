//
// Created by kirill on 10/28/2025.
//

#pragma once

#include <Core/Ability.hpp>

namespace sw
{
	class MoveAbility : public IAbility
	{
	public:
		bool execute(UnitObject& self) override;
	};
}
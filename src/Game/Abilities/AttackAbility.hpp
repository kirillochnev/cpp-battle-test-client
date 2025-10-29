//
// Created by kirill on 10/28/2025.
//

#pragma once

#include <Game/Abilities/InteractAbility.hpp>

#include <map>
#include <vector>

namespace sw
{
	class AttackAbility : public InteractAbility
	{
	protected:

		bool applyAbility(Unit self, std::vector<Unit>&& targets, Real power) override;
	public:
		using InteractAbility::InteractAbility;
	};

	class MeleeAttack : public AttackAbility
	{
	public:
		explicit MeleeAttack(Real basePower, AttributeType attributeType);
		explicit MeleeAttack(AttributeType attributeType);
		explicit MeleeAttack(Real basePower);
		explicit MeleeAttack(Real basePower, std::map<AttributeType, Real> scales);
	};

	class RangeAttack : public AttackAbility
	{
	public:
		RangeAttack(Real basePower, std::map<AttributeType, Real> scales, Real min, Real max);
		RangeAttack(Real basePower, AttributeType attribute, Real min, Real max);
		RangeAttack(AttributeType attribute, Real min, Real max);
		RangeAttack(Real basePower, Real min, Real max);
	};

}
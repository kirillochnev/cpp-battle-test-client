//
// Created by kirill on 10/28/2025.
//

#include "AttackAbility.hpp"
#include <Core/Game.hpp>
#include <Game/Rules/CanInteract.hpp>
#include <Game/Rules/EvaluatePower.hpp>
#include <Game/Rules/ApplyDamageRule.hpp>
#include <Game/Rules/FindUnitsInRange.hpp>
#include <Game/Rules/SelectTargetsRule.hpp>
#include <IO/Events/UnitAttacked.hpp>


using namespace sw;


bool AttackAbility::applyAbility(Unit self, std::vector<Unit>&& targets, Real power)
{
	if (!self || targets.empty())
	{
		return false;
	}
	auto& game = *self->game();
	for (auto target : targets)
	{
		game.eventSystem().post(io::UnitAttacked {
			.attackerUnitId = self->id(), .targetUnitId = target->id(), .damage = (uint32_t)power,
			.targetHp = (uint32_t)target->getAttribute(AttributeType::kHp) - power
		});
		game.ruleBook().apply<ApplyDamageRule>(self, target, power);
	}
	return true;
}


MeleeAttack::MeleeAttack(Real basePower, std::map<AttributeType, Real> scales):
		AttackAbility(InteractionType::kMeleeAttack, 0, 1, basePower, std::move(scales))
{

}

MeleeAttack::MeleeAttack(Real basePower, AttributeType attributeType):
		MeleeAttack(basePower, std::map<AttributeType, Real> {{attributeType, 1}})
{

}

MeleeAttack::MeleeAttack(AttributeType attributeType):
		MeleeAttack(0, attributeType)
{

}

MeleeAttack::MeleeAttack(Real basePower):
		MeleeAttack(basePower, {})
{

}

RangeAttack::RangeAttack(Real basePower, std::map<AttributeType, Real> scales, Real min, Real max):
	AttackAbility(InteractionType::kRangeAttack, min, max, basePower, std::move(scales))
{

}

RangeAttack::RangeAttack(Real basePower, AttributeType attribute, Real min, Real max):
		RangeAttack(basePower, std::map<AttributeType, Real>{{attribute, 1}}, min, max)
{

}

RangeAttack::RangeAttack(AttributeType attribute, Real min, Real max):
		RangeAttack(0, std::map<AttributeType, Real>{{attribute, 1}}, min, max) {

}

RangeAttack::RangeAttack(Real basePower, Real min, Real max):
		RangeAttack(basePower, {}, min, max)
{

}

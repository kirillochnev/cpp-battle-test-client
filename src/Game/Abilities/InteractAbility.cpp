//
// Created by kirill on 10/28/2025.
//

#include "InteractAbility.hpp"
#include <Core/Game.hpp>
#include <Game/Rules/CanInteract.hpp>
#include <Game/Rules/EvaluatePower.hpp>
#include <Game/Rules/FindUnitsInRange.hpp>
#include <Game/Rules/SelectTargetsRule.hpp>

using namespace sw;


InteractAbility::InteractAbility(InteractionType type, Real minRange, Real maxRange,
								 Real power, std::map<AttributeType, Real>&& scales):
		_type(type),
		_minRange(minRange),
		_maxRange(maxRange),
		_basePower(power),
		_scales(std::move(scales))
{

}

bool InteractAbility::execute(Unit& self)
{
	std::vector<Unit*> candidates;
	std::vector<Unit*> targets;
	Real power = 0;
	return
		findCandidates(self, candidates) &&
		filterCandidates(self, candidates) &&
		selectTargets(self, std::move(candidates), targets) &&
		evaluatePower(self, targets, power) &&
		applyAbility(self, std::move(targets), power);
}

bool InteractAbility::findCandidates(Unit& self, std::vector<Unit*>& out)
{
	out = self.game()->ruleBook().apply<FindUnitsInRange>(self, _minRange, _maxRange, _type);
	return !out.empty();
}

bool InteractAbility::filterCandidates(Unit& self, std::vector<Unit*>& candidates)
{
	erase_if(candidates, [&](auto unit){
				 // FindUnitsInRange override may not check this
				 return !self.game()->ruleBook().apply<CanInteract>(self, *unit, _type);
			 });
	return !candidates.empty();
}

bool InteractAbility::selectTargets(Unit& self, std::vector<Unit*>&& candidates, std::vector<Unit*>& targets)
{
	targets = self.game()->ruleBook().apply<SelectTargetsRule>(self, candidates, _type);
	return !targets.empty();
}

bool InteractAbility::evaluatePower(Unit& self, const std::vector<Unit*>& targets, Real& power)
{
	power = self.game()->ruleBook().apply<EvaluatePower>(self, *this, _basePower, _scales, _type);
	return true;
}

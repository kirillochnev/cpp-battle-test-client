//
// Created by kirill on 10/28/2025.
//

#pragma once

#include <Core/Ability.hpp>

#include <map>
#include <vector>

namespace sw
{
	class InteractAbility : public IAbility
	{
		InteractionType _type;
		Real _basePower;
		Real _minRange;
		Real _maxRange;
		std::map<AttributeType, Real> _scales;
	public:
		InteractAbility(InteractionType type, Real minRange, Real maxRange,
						Real power, std::map<AttributeType, Real>&& scales);
		bool execute(UnitObject& self) override;

	protected:
		virtual bool findCandidates(Unit self, std::vector<Unit>& out);
		virtual bool filterCandidates(Unit self, std::vector<Unit>& candidates);
		virtual bool selectTargets(Unit self, std::vector<Unit>&& candidates, std::vector<Unit>& targets);
		virtual bool evaluatePower(Unit self, const std::vector<Unit>& targets, Real & power);
		virtual bool applyAbility(Unit self, std::vector<Unit>&& targets, Real power) = 0;
	};

}
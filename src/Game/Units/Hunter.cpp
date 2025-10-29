//
// Created by kirill on 10/28/2025.
//

#include "IO/Commands/SpawnHunter.hpp"

#include <Core/Game.hpp>
#include <Game/Abilities/AttackAbility.hpp>
#include <Game/Abilities/MoveAbility.hpp>

using namespace sw;

struct RegisterHunter : public AutoRegistrator {
	std::string name() const noexcept override
	{
		return "RegisterHunter";
	}

	void registerIn(Game& game) override
	{
		game.parser().add<io::SpawnHunter>([&game](const io::SpawnHunter& event){
			// we could directly call game.unitFactory().allocateUnit("Hunter", event);
			// but if we want to send this event out of parser post \ receive is better
		   	game.eventSystem().post(event);
	    });

		game.unitFactory().registerUnitKind("Hunter", [](Game&, io::SpawnHunter event){
			auto unit = std::make_unique<UnitObject>(event.unitId, "Hunter", Position{(Real)event.x, (Real)event.y});
			unit->setAttribute(AttributeType::kStr, event.strength);
			unit->setAttribute(AttributeType::kAgl, event.agility);
			unit->setAttribute(AttributeType::kHp, event.hp);
			unit->addAbility<MeleeAttack>(AttributeType::kStr);
			unit->addAbility<RangeAttack>(AttributeType::kAgl, 2, event.range);
			unit->addAbility<MoveAbility>();
			return std::move(unit);
		});

		game.eventSystem().subscribe<io::SpawnHunter>([&game](const io::SpawnHunter& event){
			  game.unitFactory().allocateUnit("Hunter", event);
		});
	}
};

RegisterHunter _autoregisterHunter;
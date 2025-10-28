//
// Created by kirill on 10/28/2025.
//

#include "IO/Commands/SpawnSwordsman.hpp"

#include <Core/Game.hpp>
#include <Game/Abilities/AttackAbility.hpp>
#include <Game/Abilities/MoveAbility.hpp>

using namespace sw;

struct RegisterSwordsman : public AutoRegistrator {
	std::string name() const noexcept override
	{
		return "RegisterSwordsman";
	}

	void registerIn(Game& game) override
	{
		game.parser().add<io::SpawnSwordsman>([&game](auto event){
			// we could directly call game.unitFactory().allocateUnit("Hunter", event);
			// but if we want to send this event out of parser post \ receive is better
		   	game.eventSystem().post(event);
	    });

		game.unitFactory().registerUnitKind("Swordsman", [](Game&, io::SpawnSwordsman event){
			auto unit = std::make_unique<Unit>(event.unitId,"Swordsman", Position{(Real)event.x, (Real)event.y});
			unit->setAttribute(AttributeType::kStr, event.strength);
			unit->setAttribute(AttributeType::kHp, event.hp);
			unit->addAbility<MeleeAttack>(AttributeType::kStr);
			unit->addAbility<MoveAbility>();
			return std::move(unit);
		});

		game.eventSystem().subscribe<io::SpawnSwordsman>([&game](auto event) {
			game.unitFactory().allocateUnit("Swordsman", event);
		});

	}
};

RegisterSwordsman _autoregisterSwordsman;
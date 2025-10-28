#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/Events/MapCreated.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/Events/MarchEnded.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/Events/UnitAttacked.hpp>
#include <IO/Events/UnitDied.hpp>
#include <IO/Events/UnitMoved.hpp>
#include <IO/Events/UnitSpawned.hpp>
#include <IO/System/CommandParser.hpp>
#include <IO/System/EventLog.hpp>
#include <IO/System/PrintDebug.hpp>

#include <Game/Abilities/MoveAbility.hpp>
#include <Game/Commands/MarchCommand.hpp>
#include <Game/Abilities/AttackAbility.hpp>
#include <Core/Game.hpp>
#include <fstream>
#include <iostream>


int main(int argc, char** argv)
{
	using namespace sw;

	if (argc != 2)
	{
		throw std::runtime_error("Error: No file specified in command line argument");
	}

	std::ifstream file(argv[1]);
	if (!file)
	{
		throw std::runtime_error("Error: File not found - " + std::string(argv[1]));
	}

	Game game;

	game.init();

	game.unitFactory().registerUnitKind("swordsman", [](Game&, io::SpawnSwordsman event){
		auto unit = std::make_unique<Unit>(event.unitId,"swordsman", Position{(Real)event.x, (Real)event.y});
		unit->setAttribute(AttributeType::kStr, event.strength);
		unit->setAttribute(AttributeType::kHp, event.hp);
		unit->addAbility<MeleeAttack>(AttributeType::kStr);
	  	unit->addAbility<MoveAbility>();
	  return std::move(unit);
	});

	game.unitFactory().registerUnitKind("hunter", [](Game&, io::SpawnHunter event){
		auto unit = std::make_unique<Unit>(event.unitId, "hunter", Position{(Real)event.x, (Real)event.y});
		unit->setAttribute(AttributeType::kStr, event.strength);
		unit->setAttribute(AttributeType::kAgl, event.agility);
		unit->setAttribute(AttributeType::kHp, event.hp);
		unit->addAbility<MeleeAttack>(AttributeType::kStr);
		unit->addAbility<RangeAttack>(AttributeType::kAgl, 2, event.range);
		unit->addAbility<MoveAbility>();
		return std::move(unit);
	});


	std::vector<Subscription > subs;
	subs.push_back(game.eventSystem().subscribe<io::CreateMap>([&game](const io::CreateMap& event){
		game.createBattleField(event.width, event.height);
	}));
	subs.push_back(game.eventSystem().subscribe<io::SpawnSwordsman>([&game](const io::SpawnSwordsman& event){
		game.unitFactory().allocateUnit("swordsman", event);
	}));
	subs.push_back(game.eventSystem().subscribe<io::SpawnHunter>([&game](const io::SpawnHunter& event){
		game.unitFactory().allocateUnit("hunter", event);
	}));

	subs.push_back(game.eventSystem().subscribe<io::March>([&game](const io::March& event){
		game.findUnit(event.unitId)->addCommand<MarchCommand>(event.targetX, event.targetY);
	}));


	EventLog eventLog;
	auto printEvent = [&eventLog, &game](auto event){
		eventLog.log(game.frameIndex() + 1, std::move(event));
	};

	subs.push_back(game.eventSystem().subscribe<io::UnitSpawned>(printEvent));
	subs.push_back(game.eventSystem().subscribe<io::MapCreated>(printEvent));
	subs.push_back(game.eventSystem().subscribe<io::UnitMoved>(printEvent));
	subs.push_back(game.eventSystem().subscribe<io::MarchStarted>(printEvent));
	subs.push_back(game.eventSystem().subscribe<io::MarchEnded>(printEvent));
	subs.push_back(game.eventSystem().subscribe<io::UnitAttacked>(printEvent));
	subs.push_back(game.eventSystem().subscribe<io::UnitDied>(printEvent));

	io::CommandParser parser;
	auto handle = [&game](auto command){game.eventSystem().post(command);};
	parser.add<io::CreateMap>(handle)
		.add<io::SpawnSwordsman>(handle)
		.add<io::SpawnHunter>(handle)
		.add<io::March>(handle);

	parser.parse(file);


	do
	{
		std::cout << "\n";
	} while (game.update());

	return 0;
}

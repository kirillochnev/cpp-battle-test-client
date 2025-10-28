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
#include <Core/Game.hpp>
#include <fstream>
#include <iostream>



void addEventPrinter(sw::Game& game)
{
	using namespace sw;

	auto printEvent = [&game](auto event){
		EventLog eventLog;
		eventLog.log(game.frameIndex() + 1, std::move(event));
	};

	game.eventSystem().subscribe<io::UnitSpawned>(printEvent);
	game.eventSystem().subscribe<io::MapCreated>(printEvent);
	game.eventSystem().subscribe<io::UnitMoved>(printEvent);
	game.eventSystem().subscribe<io::MarchStarted>(printEvent);
	game.eventSystem().subscribe<io::MarchEnded>(printEvent);
	game.eventSystem().subscribe<io::UnitAttacked>(printEvent);
	game.eventSystem().subscribe<io::UnitDied>(printEvent);
}

void registerCommonCommands(sw::Game& game)
{
	using namespace sw;

	game.eventSystem().subscribe<io::CreateMap>([&game](const io::CreateMap& event) {
		game.createBattleField(event.width, event.height);
	});

	game.eventSystem().subscribe<io::March>([&game](const io::March& event){
		game.findUnit(event.unitId)->addCommand<MarchCommand>(event.targetX, event.targetY);
	});
}

void configureGame(sw::Game& game)
{
	// We may register units/rules directly here< or use AutoRegistrator
	using namespace sw;
	registerCommonCommands(game);
	addEventPrinter(game);
}

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
	configureGame(game);
	game.init();



	auto handle = [&game](auto command){game.eventSystem().post(command);};
	game.parser()
		.add<io::CreateMap>(handle)
		.add<io::March>(handle);

	game.parser().parse(file);


	do
	{
		std::cout << "\n";
	} while (game.update());

	return 0;
}

#include "UnitTests.h"
#include "../Logic/Strategy/PathLinear.h"
#include "Logic/Map.h"
#include "Logic/Game.h"
#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/System/CommandParser.hpp>
#include <iostream>
#include <fstream>


void UnitTests::fullTest() {
	std::cout << "StartTest" << std::endl;

	mapCreatorTest();
	linearPathTest();
	scenarioTest();

	std::cout << "Finish test" << std::endl;
}

void UnitTests::mapCreatorTest()
{
	using namespace sw::logic;

	std::cout << "Map creator test" << std::endl;
	Map map;
	equal(map.height(), static_cast<uint32_t>(0));
	equal(map.width(), static_cast<uint32_t>(0));

	map.create(15,12);
	equal(map.height(), static_cast<uint32_t>(12));
	equal(map.width(), static_cast<uint32_t>(15));
}

void UnitTests::linearPathTest()
{
	std::cout << "Linear path test" << std::endl;

	{
		sw::logic::PathLinear path;
		path.setStartPoint({2,2});
		path.setEndPoint({4,4});

		equal(path.nextPosition(), {3,3});
		equal(path.nextPosition(), {4,4});
	}

	{
		sw::logic::PathLinear path;
		path.setStartPoint({2, 1});
		path.setEndPoint({4,5});

		equal(path.nextPosition(), {3,2});
		equal(path.nextPosition(), {3,3});
		equal(path.nextPosition(), {4,4});
		equal(path.nextPosition(), {4,5});
	}

	{
		sw::logic::PathLinear path;
		path.setStartPoint({1, 2});
		path.setEndPoint({5, 4});
		path.generate();

		equal(path.nextPosition(), {2,3});
		equal(path.nextPosition(), {3,3});
		equal(path.nextPosition(), {4,4});
		equal(path.nextPosition(), {5,4});
	}
}

void UnitTests::scenarioTest()
{
	std::cout << "Scenario test" << std::endl;

	using namespace sw;
	io::CommandParser parser;
	parser.add<io::CreateMap>([](auto command) {})
	 	.add<io::SpawnSwordsman>([](auto command) {})
	 	.add<io::SpawnHunter>([](auto command) {})
	 	.add<io::March>([](auto command) {});

	oneTest(R"(./../test/two_swordsman_move_command.txt)",R"(./../test/two_swordsman_move_origin.txt)", parser);
	oneTest(R"(./../test/two_swordsman_attack_command.txt)",R"(./../test/two_swordsman_attack_origin.txt)", parser);
	oneTest(R"(./../test/two_sword_move_attack_command.txt)",R"(./../test\two_sword_move_attack_origin.txt)", parser);
	oneTest(R"(./../test/hunter_sword_command.txt)",R"(./../test/hunter_sword_origin.txt)", parser);
	oneTest(R"(./../test/main_battle_command.txt)",R"(./../test/main_battle_origin.txt)", parser);
}

void UnitTests::oneTest(const std::string& commandFileName, const std::string& originFileName, sw::io::CommandParser& parser)
{
	const std::string outFileName = R"(./../test/out.txt)";

	std::ifstream commandFile(commandFileName);
	if (!commandFile)
	{
		throw std::runtime_error("Error: File not found - " + commandFileName);
	}

	std::ofstream outFile(outFileName);
	if (!outFile || !outFile.is_open())
	{
		throw std::runtime_error("Error: File not found - " + commandFileName);
	}

	std::streambuf* originalCoutBuffer = std::cout.rdbuf(); // Сохраняем оригинальный буфер
	std::cout.rdbuf(outFile.rdbuf()); // Перенаправляем std::cout в файл

	sw::logic::Game::instance().clear();
	parser.parse(commandFile);
	while (!sw::logic::Game::instance().isGameOver())
		sw::logic::Game::instance().makeTurn();

	std::cout.rdbuf(originalCoutBuffer); // Восстанавливаем оригинальный буфер std::cout
	commandFile.close();
	outFile.close();

	std::cout << commandFileName << "   ";
	equal(compare(outFileName,  originFileName), true);
}

bool UnitTests::compare(const std::string& resultFileName, const std::string& originFileName)
{
	std::ifstream resultFile(resultFileName);
	std::ifstream originFile(originFileName);

	if (!resultFile.is_open())
	{
		std::cerr << "Could not open file " << resultFileName << std::endl;
		return false;
	}
	if (!originFile.is_open())
	{
		std::cerr << "Could not open file " << originFileName << std::endl;
		return false;
	}

	std::string resultLine;
	std::string originLine;

	while (std::getline(resultFile, resultLine) && std::getline(originFile, originLine))
	{
		if (resultLine != originLine)
		{
			std::cout << "Result  " << resultLine << std::endl;
			std::cout << "Origin  " << originLine << std::endl;
			return false;
		}
	}

	resultFile.close();
	originFile.close();

	return true;
}
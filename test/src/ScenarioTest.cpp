#include "gtest/gtest.h"
#include <string>
#include <fstream>
#include <filesystem>
#include "../../src/IO/System/CommandParser.hpp"
#include "../../src/IO/Commands/CreateMap.hpp"
#include "../../src/IO/Commands/SpawnSwordsman.hpp"
#include "../../src/IO/Commands/SpawnHunter.hpp"
#include "../../src/IO/Commands/March.hpp"


bool compare(const std::string& resultFileName, const std::string& originFileName)
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

sw::io::CommandParser createParser()
{
	sw::io::CommandParser parser;
	parser.add<sw::io::CreateMap>([](auto command) {})
		.add<sw::io::SpawnSwordsman>([](auto command) {})
		.add<sw::io::SpawnHunter>([](auto command) {})
		.add<sw::io::March>([](auto command) {});

	return parser;
}

void oneScenario(const std::string& scenarioFileName, const std::string& tempFileName, sw::io::CommandParser& parser)
{
	std::ifstream scenarioFile(scenarioFileName);
 	if (!scenarioFile)
 	{
 		throw std::runtime_error("Error: File not found - " + scenarioFileName);
	}

	std::ofstream tempFile(tempFileName);
 	if (!tempFile || !tempFile.is_open())
 	{
 		throw std::runtime_error("Error: File not found - " + tempFileName);
	}

 	std::streambuf* originalCoutBuffer = std::cout.rdbuf(); // Сохраняем оригинальный буфер
 	std::cout.rdbuf(tempFile.rdbuf()); // Перенаправляем std::cout в файл

 	sw::logic::Game::instance().clear();
 	parser.parse(scenarioFile);
 	while (!sw::logic::Game::instance().isGameOver())
 		sw::logic::Game::instance().makeTurn();

 	std::cout.rdbuf(originalCoutBuffer); // Восстанавливаем оригинальный буфер std::cout
 	scenarioFile.close();
	tempFile.close();
}


TEST(ScenarioTest, SwBattle) {

	std::filesystem::path scenarioPath = std::filesystem::current_path().parent_path() / "scenario";
	std::filesystem::path resultPath = std::filesystem::current_path().parent_path() / "result";
	std::filesystem::path tempPath = std::filesystem::current_path().parent_path() / "temp";

	sw::io::CommandParser parser = createParser();

	for (const auto& scenarioName : std::filesystem::directory_iterator(scenarioPath))
	{
		if (std::filesystem::is_regular_file(scenarioName))
		{
			const auto filename = scenarioName.path().filename();
			const auto resultFileName = resultPath / filename;
			const auto tempFileName = tempPath / filename;

			oneScenario(scenarioName.path().string(), tempFileName.string(), parser);
			EXPECT_EQ(compare(resultFileName.string(), tempFileName.string()), true);
		}
	}
}

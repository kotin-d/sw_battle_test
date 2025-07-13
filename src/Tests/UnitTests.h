#pragma once

#include <string>
#include <iostream>
#include <IO/System/CommandParser.hpp>


class UnitTests {
public:
	static void fullTest();

	static void mapCreatorTest();
	static void linearPathTest();

	static void scenarioTest();

private:
	template<typename T>
	static void equal(const T& value1, const T& value2)
	{
		std::cout << ((value1 == value2) ? "Ok" : "Fail") << std::endl;
	}

	static void oneTest(const std::string& commandFileName, const std::string& originFileName, sw::io::CommandParser& parser);
	[[nodiscard]] static bool compare(const std::string& resultFileName, const std::string& originFileName);

};


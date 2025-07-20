cmake_minimum_required(VERSION 3.27)
project(sw_battle_test)

# GoogleTest requires at least C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../src ../src/Logic ../src/Logic/Strategy ../src/IO/System)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.hpp ../src/Logic/*.cpp ../src/Logic/Strategy/*.cpp ../src/IO/System/*.cpp)
#file(GLOB_RECURSE LOGIC_SOURCES ../src/Logic/*.cpp)
#file(GLOB_RECURSE STRATEGY_SOURCES ../src/Logic/Strategy/*.cpp)

add_executable(Google_Tests_run ${SOURCES}
        src/MathTest.cpp
        src/ScenarioTest.cpp
)
target_link_libraries(Google_Tests_run gtest gtest_main)
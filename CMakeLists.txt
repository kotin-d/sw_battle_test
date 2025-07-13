cmake_minimum_required(VERSION 3.27)
project(sw_battle_test)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.hpp)
add_executable(sw_battle_test ${SOURCES}
        src/Tests/UnitTests.cpp
        src/Tests/UnitTests.h
        src/Logic/Map.cpp
        src/Logic/Map.h
        src/Logic/Cell.cpp
        src/Logic/Cell.h
        src/Logic/Unit.cpp
        src/Logic/Unit.h
        src/Logic/SwordsMan.cpp
        src/Logic/SwordsMan.h
        src/Logic/Hunter.cpp
        src/Logic/Hunter.h
        src/Logic/Delegate/LogMapDelegate.cpp
        src/Logic/Delegate/LogMapDelegate.h
        src/Helpers/Position.h
        src/Logic/Strategy/IPath.h
        src/Logic/Strategy/PathLinear.cpp
        src/Logic/Strategy/PathLinear.h
        src/Logic/Game.cpp
        src/Logic/Game.h
        src/Logic/Delegate/LogMapDelegate.cpp
        src/Logic/Delegate/LogMapDelegate.h
        src/Logic/Strategy/Healther.h
        src/Logic/Strategy/Damager.h
        src/Logic/Strategy/Reacher.h
        src/Logic/Strategy/Finder.cpp
        src/Logic/Strategy/Finder.h
        src/Logic/Strategy/Reacher.cpp
        src/Logic/Strategy/PathStand.h
)

target_include_directories(sw_battle_test PUBLIC src/)

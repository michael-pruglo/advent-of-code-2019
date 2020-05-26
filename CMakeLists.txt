cmake_minimum_required(VERSION 3.16)
project(untitled3)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled3 main.cpp tests/Test.hpp helpers/IntcodeComputer.cpp helpers/IntcodeComputer.hpp Solution.hpp tests/IntCodeComputer/TestIntcodeComputer.cpp tests/IntCodeComputer/TestIntcodeComputer.hpp Solution.cpp helpers/EmergencyHullPaintingRobot.cpp helpers/EmergencyHullPaintingRobot.hpp helpers/ArcadeCabinet.cpp helpers/ArcadeCabinet.hpp)
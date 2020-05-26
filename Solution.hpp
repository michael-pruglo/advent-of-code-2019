//
// Created by Michael on 05/22/20.
//

#ifndef UNTITLED3_SOLUTION_HPP
#define UNTITLED3_SOLUTION_HPP

#include <fstream>
#include <numeric>
#include <algorithm>
#include <map>
#include <set>
#include "helpers/IntcodeComputer.hpp"
#include "helpers/EmergencyHullPaintingRobot.hpp"

class Solution
{
public:

    auto run(const std::string& inFileName)
    {
        std::ifstream inFile(inFileName);
        EmergencyHullPaintingRobot ehpr;
        ehpr.init(inFile);
        return ehpr.run();
    }

public:
    long long runComputer(const std::string& inFileName);
    long long runAmplifier(const std::string& inFileName);
    long long runAmplifierFeedbackloop(const std::string& inFileName);
};

#endif //UNTITLED3_SOLUTION_HPP

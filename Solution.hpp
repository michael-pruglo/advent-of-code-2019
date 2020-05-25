//
// Created by Michael on 05/22/20.
//

#ifndef UNTITLED3_SOLUTION_HPP
#define UNTITLED3_SOLUTION_HPP

#include <fstream>
#include <numeric>
#include <algorithm>
#include "helpers/IntcodeComputer.hpp"

class Solution
{
public:
    auto run(const std::string& inFileName)
    {
        return runAmplifierFeedbackloop(inFileName);
    }

public:
    int runComputer(const std::string& inFileName);
    int runAmplifier(const std::string& inFileName);
    int runAmplifierFeedbackloop(const std::string& inFileName);
};

#endif //UNTITLED3_SOLUTION_HPP

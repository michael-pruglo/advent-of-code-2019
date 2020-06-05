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
#include <thread>
#include <mutex>
#include "helpers/IntcodeComputer.hpp"
#include "helpers/IntcodeComputerASCII.hpp"

class Solution
{

public:

    auto run(const std::string& inFileName)
    {
        IntcodeComputerASCII ic = readIntcodeFile(inFileName);


        return 0;
    }

public:
    long long runComputer(const std::string& inFileName);
    long long runAmplifier(const std::string& inFileName);
    long long runAmplifierFeedbackloop(const std::string& inFileName);
};

#endif //UNTITLED3_SOLUTION_HPP

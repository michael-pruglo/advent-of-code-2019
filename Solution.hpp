//
// Created by Michael on 05/22/20.
//

#ifndef UNTITLED3_SOLUTION_HPP
#define UNTITLED3_SOLUTION_HPP

#include <fstream>
#include <cassert>
#include "helpers/IntcodeComputer.hpp"

class Solution
{
public:
    auto run(const std::string& inFileName)
    {
        std::ifstream inFile(inFileName);

        IntcodeComputer ic(inFile);
        return ic.run();
    }
};


#endif //UNTITLED3_SOLUTION_HPP

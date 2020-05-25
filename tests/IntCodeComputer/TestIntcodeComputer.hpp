//
// Created by Michael on 05/25/20.
//

#ifndef UNTITLED3_TESTINTCODECOMPUTER_HPP
#define UNTITLED3_TESTINTCODECOMPUTER_HPP

#include <vector>
#include <string>
#include <functional>
#include "../../Solution.hpp"
#include "../Test.hpp"

class TestIntcodeComputer
{
    int badNo=0, allNo=0;
    template<typename T>
    void runMachine(std::vector<std::pair<std::string, T>> testcases);
    template<typename T>
    void runAmplifier(std::vector<std::pair<std::string, T>> testcases);
    template<typename T>
    void runAmplifierFeedbackloop(std::vector<std::pair<std::string, T>> testcases);


public:
    void run();
};


#endif //UNTITLED3_TESTINTCODECOMPUTER_HPP

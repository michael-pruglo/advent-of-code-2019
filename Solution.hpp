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
#include "helpers/IntcodeComputerASCII.hpp"

class Solution
{
    IntcodeComputerASCII ic;

    long long addCommandAndTry(const std::string& scriptSoFar, int n)
    {
        if (n > 3) return -3;
        if (n==1) {std::cout<<"Trying "; for (auto& c: scriptSoFar) std::cout<<(c=='\n'?';':c); std::cout<<"\n";}
        if (auto res = test(scriptSoFar+"WALK\n") != 10) return res;

        for (const std::string& opcode : {"AND ", "OR ", "NOT "})
            for (const std::string& arg1 : {"A ", "B ", "C ", "D ", "T ", "J "})
                for (const std::string& arg2 : {"T\n", "J\n"})
                {
                    std::string newS;
                    newS.reserve(scriptSoFar.size() + 10);
                    newS =  scriptSoFar;
                    newS += opcode;
                    newS += arg1;
                    newS += arg2;
                    addCommandAndTry(newS,n+1);
                }
        return -4;
    }

    long long test(const std::string& springScript)
    {
        ic.run();
        ic.grabOutput();

        auto res = ic.run(springScript);
        std::cout<<ic.grabOutput();
        ic.reset();
        return res;
    }

public:

    auto run(const std::string& inFileName)
    {
        std::ifstream inFile(inFileName);
        ic = IntcodeComputerASCII(inFile);

        auto res = test(""
//                    "OR E J\n"
//                    "AND I J\n"
//
//                    "OR H J\n"
//
//                    "AND D J\n"
                    "OR B T\n"
                    "AND C T\n"
                    "NOT T T\n"

                    "OR E J\n"
                    "AND I J\n"
                    "OR H J\n"

                    "AND D J\n"

                    "AND T J\n"

                    "NOT A T\n"
                    "OR T J\n"


                    "RUN\n");

        return res;
    }

public:
    long long runComputer(const std::string& inFileName);
    long long runAmplifier(const std::string& inFileName);
    long long runAmplifierFeedbackloop(const std::string& inFileName);
};

#endif //UNTITLED3_SOLUTION_HPP

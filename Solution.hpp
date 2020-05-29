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

class Solution
{
    const int W = 100, H = W;
    std::vector<std::vector<int>> map = std::vector<std::vector<int>>(H, std::vector<int>(W));
    IntcodeComputer ic;


    bool get(int i, int j)
    {
        bool res = ic.run({j, i});
        ic.reset();
        return res;
    }
public:

    auto run(const std::string& inFileName)
    {
        std::ifstream inFile(inFileName);
        ic = IntcodeComputer(inFile);


//        for (int i = 85; i < 110; ++i, std::cout<<"\n")
//            for (int j = 70; j < 120; ++j)
//                std::cout<<(get(i, j)?10'000*(j-W+1) + i==860096?'-':'#':'.');

        const int LIM = 99999;
        int j;
        for (j = W; !get(H*2-5, j); ++j);
        for (int i = H*2-5; i < LIM; ++i%1000?std::cout:std::cout<<i<<"\n")
            for (; get(i, j); ++j)
                if (get(i+(H-1), j-(W-1)))
                    return 10'000*(j-W+1) + i;
        return -1;
    }

public:
    long long runComputer(const std::string& inFileName);
    long long runAmplifier(const std::string& inFileName);
    long long runAmplifierFeedbackloop(const std::string& inFileName);
};

#endif //UNTITLED3_SOLUTION_HPP

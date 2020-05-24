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
        std::ifstream inFile(inFileName);

        const int N = 5;
        std::vector<IntcodeComputer> ic(N, IntcodeComputer(inFile));

        std::vector<int> phaseSettingSequence(N);
        std::iota(phaseSettingSequence.begin(), phaseSettingSequence.end(), 0);
        int maxRes = -1;
        std::vector<int> maxSeq;
        do {
            int currRes = ic[0].run(std::queue<int>({phaseSettingSequence[0], 0}));
            for (int i = 1; i < N; ++i)
                currRes = ic[i].run(std::queue<int>({phaseSettingSequence[i], currRes}));
            if (maxRes < currRes)
            {
                maxRes = currRes;
                maxSeq = phaseSettingSequence;
            }
        } while ( std::next_permutation(phaseSettingSequence.begin(), phaseSettingSequence.end()) );


        //std::cout<<"from the seq "; for (auto& x: maxSeq) std::cout<<x<<" "; std::cout<<"\n";
        return maxRes;
    }
};


#endif //UNTITLED3_SOLUTION_HPP

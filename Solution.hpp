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

int Solution::runAmplifier(const std::string& inFileName)
{
    std::ifstream inFile(inFileName);

    const int N = 5;
    std::vector<IntcodeComputer> ic(N, IntcodeComputer(inFile));

    std::vector<int> phaseSettingSequence(N);
    std::iota(phaseSettingSequence.begin(), phaseSettingSequence.end(), 0);
    int maxRes = -1;
    std::vector<int> maxSeq;

    do {
        int currRes = 0;
        for (int i = 0; i < N; ++i)
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

int Solution::runComputer(const std::string& inFileName)
{
    std::ifstream inFile(inFileName);

    IntcodeComputer ic(inFile);
    return ic.run();
}

int Solution::runAmplifierFeedbackloop(const std::string& inFileName)
{
    std::ifstream inFile(inFileName);

    const int N = 5;
    std::vector<IntcodeComputer> ic(N, IntcodeComputer(inFile));

    std::vector<int> phaseSettingSequence(N);
    std::iota(phaseSettingSequence.begin(), phaseSettingSequence.end(), 5);
    int maxRes = -1;
    std::vector<int> maxSeq;

    //phaseSettingSequence = {9,7,8,6,5};
    do {
        for (auto& x: ic) x.reset();
        int currRes = 0, terminateSum = 0;
        std::vector<int> currout = {currRes};
        bool firstRunFlag = true;
        for (int i = 0; terminateSum<N; )
        {
            if (!ic[i].wasTerminated())
            {
                //std::cout<<"=========machine "<<i<<"\n";
                std::queue<int> nextInput;
                if (firstRunFlag) nextInput.push(phaseSettingSequence[i]);
                for (auto x: currout) nextInput.push(x);
                //ic[i].reset();
                currRes = ic[i].run(nextInput);
                currout = ic[i].getOutput();
            } else
                ++terminateSum;

            if (++i >= N)
            {
                i = 0;
                firstRunFlag = false;
            }
        }
        if (maxRes < currRes)
        {
            maxRes = currRes;
            maxSeq = phaseSettingSequence;
        }

        //std::cout<<"for the seq "; for (auto& x: phaseSettingSequence) std::cout<<x<<" "; std::cout<<"="<<currRes<<"\n";
    } while ( std::next_permutation(phaseSettingSequence.begin(), phaseSettingSequence.end()) );


    std::cout<<"from the seq "; for (auto& x: maxSeq) std::cout<<x<<" "; std::cout<<"\n";
    return maxRes;
}


#endif //UNTITLED3_SOLUTION_HPP

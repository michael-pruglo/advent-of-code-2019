//
// Created by Michael on 05/25/20.
//
#include "Solution.hpp"

long long Solution::runComputer(const std::string& inFileName)
{
    std::ifstream inFile(inFileName);

    IntcodeComputer ic(inFile);
    auto res = ic.run();
    auto residualOutput = ic.grabOutput();
    if (residualOutput.size()>1) { std::cout << "\tvvv [bottom] has residual output ["; for (auto& x: residualOutput) std::cout << x << " "; std::cout << "] \n";}
    return res;
}

long long Solution::runAmplifier(const std::string& inFileName)
{
    std::ifstream inFile(inFileName);

    const int N = 5;
    std::vector<IntcodeComputer> ic(N, IntcodeComputer(inFile));

    std::vector<int> phaseSettingSequence(N);
    std::iota(phaseSettingSequence.begin(), phaseSettingSequence.end(), 0);
    long long maxRes = -1;
    std::vector<int> maxSeq;

    do {
        long long currRes = 0;
        for (int i = 0; i < N; ++i)
            currRes = ic[i].run({phaseSettingSequence[i], currRes});

        if (maxRes < currRes)
        {
            maxRes = currRes;
            maxSeq = phaseSettingSequence;
        }

        for (auto& computer: ic)
            computer.reset();
    } while ( std::next_permutation(phaseSettingSequence.begin(), phaseSettingSequence.end()) );


    //std::cout<<"from the seq "; for (auto& x: maxSeq) std::cout<<x<<" "; std::cout<<"\n";
    return maxRes;
}

long long Solution::runAmplifierFeedbackloop(const std::string& inFileName)
{
    std::ifstream inFile(inFileName);

    const int N = 5;
    std::vector<IntcodeComputer> ic(N, IntcodeComputer(inFile));

    std::vector<int> phaseSettingSequence(N);
    std::iota(phaseSettingSequence.begin(), phaseSettingSequence.end(), 5);
    long long maxRes = -1;
    std::vector<int> maxSeq;

    //phaseSettingSequence = {9,7,8,6,5};
    do {
        for (auto& x: ic) x.reset();
        long long currRes = 0, terminateSum = 0;
        std::vector<long long> currout = {currRes};
        bool firstRunFlag = true;
        for (int i = 0; terminateSum<N; )
        {
            if (!ic[i].wasTerminated())
            {
                //std::cout<<"=========machine "<<i<<"\n";
                std::vector<long long> nextInput = currout;
                if (firstRunFlag) nextInput.insert(nextInput.begin(), phaseSettingSequence[i]);
                //ic[i].reset();
                currRes = ic[i].run(nextInput);
                currout = ic[i].grabOutput();
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

//
// Created by Michael on 05/25/20.
//

#include "TestIntcodeComputer.hpp"

void TestIntcodeComputer::run()
{
    runMachine(std::vector({
         std::make_pair(std::string("tests/IntCodeComputer/in1.txt"), 2),
         std::make_pair(std::string("tests/IntCodeComputer/in2.txt"), 30),
         std::make_pair(std::string("tests/IntCodeComputer/in3.txt"), 6568671),
         std::make_pair(std::string("tests/IntCodeComputer/in4.txt"), 19690720),
         std::make_pair(std::string("tests/IntCodeComputer/in5.txt"), 3500),
         std::make_pair(std::string("tests/IntCodeComputer/in6.txt"), 6745903),
         std::make_pair(std::string("tests/IntCodeComputer/in7.txt"), 9168267),
         std::make_pair(std::string("tests/IntCodeComputer/in8.txt"), 1),
         std::make_pair(std::string("tests/IntCodeComputer/in9.txt"), 0),
         std::make_pair(std::string("tests/IntCodeComputer/in10.txt"), 1),
         std::make_pair(std::string("tests/IntCodeComputer/in11.txt"), 0),
         std::make_pair(std::string("tests/IntCodeComputer/in12.txt"), 1),
         std::make_pair(std::string("tests/IntCodeComputer/in13.txt"), 0),
         std::make_pair(std::string("tests/IntCodeComputer/in14.txt"), 1),
         std::make_pair(std::string("tests/IntCodeComputer/in15.txt"), 0),
         std::make_pair(std::string("tests/IntCodeComputer/in16.txt"), 1),
         std::make_pair(std::string("tests/IntCodeComputer/in17.txt"), 0),
         std::make_pair(std::string("tests/IntCodeComputer/in18.txt"), 1),
         std::make_pair(std::string("tests/IntCodeComputer/in19.txt"), 0),
         std::make_pair(std::string("tests/IntCodeComputer/in20.txt"), 999),
         std::make_pair(std::string("tests/IntCodeComputer/in21.txt"), 1000),
         std::make_pair(std::string("tests/IntCodeComputer/in22.txt"), 1001),
         std::make_pair(std::string("tests/IntCodeComputer/in23.txt"), 2369720),
         std::make_pair(std::string("tests/IntCodeComputer/in24.txt"), 13933662)
    }));

    runAmplifier(std::vector({
           std::make_pair(std::string("tests/IntCodeComputer/in25.txt"), 43210),
           std::make_pair(std::string("tests/IntCodeComputer/in26.txt"), 54321),
           std::make_pair(std::string("tests/IntCodeComputer/in27.txt"), 65210),
           std::make_pair(std::string("tests/IntCodeComputer/in28.txt"), 14902)
    }));

    runAmplifierFeedbackloop(std::vector({
           std::make_pair(std::string("tests/IntCodeComputer/in29.txt"), 139629729),
           std::make_pair(std::string("tests/IntCodeComputer/in30.txt"), 18216),
           std::make_pair(std::string("tests/IntCodeComputer/in31.txt"), 6489132)
    }));

    std::cout<<"\n\n";
    std::cout<<"TESTING OF INTCODE COMPUTER IS DONE: \n";
    std::cout<<"\t# "<<allNo<<"\n";
    std::cout<<"\t+ "<<allNo-badNo<<"\n";
    std::cout<<"\t- "<<badNo<<"\n\n";
}


template<typename T>
void TestIntcodeComputer::runMachine(std::vector<std::pair<std::string, T>> testcases)
{
    int bad = 0;
    for (const auto& [fileName, expected] : testcases)
    {
        Solution sol;
        auto result = sol.runComputer(fileName);
        std::cout<<"test \""<<fileName<<"\" ";
        if (Test::test(expected, result))
            std::cout<<" passed\n";
        else
        {
            std::cout<<" WA: expected ["<<expected<<"] got ["<<result<<"]\n";
            ++bad;
        }
    }
    int good = testcases.size()-bad;
    allNo += good;
    badNo += bad;

    std::cout<<"==\n";
    std::cout<<testcases.size()<<" tests done. "<<good<<" ok, "<<bad<<" bad\n";
}


template<typename T>
void TestIntcodeComputer::runAmplifier(std::vector<std::pair<std::string, T>> testcases)
{
    int bad = 0;
    for (const auto& [fileName, expected] : testcases)
    {
        Solution sol;
        auto result = sol.runAmplifier(fileName);
        std::cout<<"test \""<<fileName<<"\" ";
        if (Test::test(expected, result))
            std::cout<<" passed\n";
        else
        {
            std::cout<<" WA: expected ["<<expected<<"] got ["<<result<<"]\n";
            ++bad;
        }
    }
    int good = testcases.size()-bad;
    allNo += good;
    badNo += bad;

    std::cout<<"==\n";
    std::cout<<testcases.size()<<" tests done. "<<good<<" ok, "<<bad<<" bad\n";
}

template<typename T>
void TestIntcodeComputer::runAmplifierFeedbackloop(std::vector<std::pair<std::string, T>> testcases)
{
    int bad = 0;
    for (const auto& [fileName, expected] : testcases)
    {
        Solution sol;
        auto result = sol.runAmplifierFeedbackloop(fileName);
        std::cout<<"test \""<<fileName<<"\" ";
        if (Test::test(expected, result))
            std::cout<<" passed\n";
        else
        {
            std::cout<<" WA: expected ["<<expected<<"] got ["<<result<<"]\n";
            ++bad;
        }
    }
    int good = testcases.size()-bad;
    allNo += good;
    badNo += bad;

    std::cout<<"==\n";
    std::cout<<testcases.size()<<" tests done. "<<good<<" ok, "<<bad<<" bad\n";
}
//
// Created by Michael on 05/25/20.
//

#include "TestIntcodeComputer.hpp"

void TestIntcodeComputer::run()
{
    runMachine(std::vector({
        std::make_pair(std::string("tests/IntCodeComputer/in/in1.txt"), 2ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in2.txt"), 30ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in3.txt"), 6568671ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in4.txt"), 19690720ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in5.txt"), 3500ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in6.txt"), 6745903ll), //residual output does checks 0=OK. Last = result
        std::make_pair(std::string("tests/IntCodeComputer/in/in7.txt"), 9168267ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in8.txt"), 1ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in9.txt"), 0ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in10.txt"), 1ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in11.txt"), 0ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in12.txt"), 1ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in13.txt"), 0ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in14.txt"), 1ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in15.txt"), 0ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in16.txt"), 1ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in17.txt"), 0ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in18.txt"), 1ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in19.txt"), 0ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in20.txt"), 999ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in21.txt"), 1000ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in22.txt"), 1001ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in23.txt"), 2369720ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in24.txt"), 13933662ll) //residual output does checks 0=OK. Last = result
    }));

    runAmplifier(std::vector({
        std::make_pair(std::string("tests/IntCodeComputer/in/in25.txt"), 43210ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in26.txt"), 54321ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in27.txt"), 65210ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in28.txt"), 14902ll)
    }));

    runAmplifierFeedbackloop(std::vector({
        std::make_pair(std::string("tests/IntCodeComputer/in/in29.txt"), 139629729ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in30.txt"), 18216ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in31.txt"), 6489132ll)
    }));

    runMachine(std::vector({
        std::make_pair(std::string("tests/IntCodeComputer/in/in32.txt"), 99ll), //reflexive output of the program itself
        std::make_pair(std::string("tests/IntCodeComputer/in/in33.txt"), 1219070632396864ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in34.txt"), 1125899906842624ll),
        std::make_pair(std::string("tests/IntCodeComputer/in/in35.txt"), 2890527621ll)
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
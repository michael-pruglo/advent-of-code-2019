#include "tests/Test.hpp"

int main()
{
    Test::run(std::vector({
        std::make_pair(std::string("tests/in1.txt"), 2),
        std::make_pair(std::string("tests/in2.txt"), 30),
        std::make_pair(std::string("tests/in3.txt"), 6568671),
        std::make_pair(std::string("tests/in4.txt"), 19690720),
        std::make_pair(std::string("tests/in5.txt"), 3500),
        std::make_pair(std::string("tests/in6.txt"), 6745903),
        std::make_pair(std::string("tests/in7.txt"), 9168267),
        std::make_pair(std::string("tests/in8.txt"), 1),
        std::make_pair(std::string("tests/in9.txt"), 0),
        std::make_pair(std::string("tests/in10.txt"), 1),
        std::make_pair(std::string("tests/in11.txt"), 0),
        std::make_pair(std::string("tests/in12.txt"), 1),
        std::make_pair(std::string("tests/in13.txt"), 0),
        std::make_pair(std::string("tests/in14.txt"), 1),
        std::make_pair(std::string("tests/in15.txt"), 0),
        std::make_pair(std::string("tests/in16.txt"), 1),
        std::make_pair(std::string("tests/in17.txt"), 0),
        std::make_pair(std::string("tests/in18.txt"), 1),
        std::make_pair(std::string("tests/in19.txt"), 0),
        std::make_pair(std::string("tests/in20.txt"), 999),
        std::make_pair(std::string("tests/in21.txt"), 1000),
        std::make_pair(std::string("tests/in22.txt"), 1001),
        std::make_pair(std::string("tests/in23.txt"), 2369720),
        std::make_pair(std::string("tests/in24.txt"), 13933662)
    }));


    std::cout<<"\nMain run:\n";
    std::cout<<Solution().run("in.txt")<<"\n";

    return 0;
}

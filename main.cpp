#include "tests/Test.hpp"

int main()
{
    //TODO: exhaustive tests
    Test::run(std::vector({
        std::make_pair(std::string("tests/in1.txt"), 2),
        std::make_pair(std::string("tests/in2.txt"), 30),
        std::make_pair(std::string("tests/in3.txt"), 6568671),
        std::make_pair(std::string("tests/in4.txt"), 19690720),
        std::make_pair(std::string("tests/in5.txt"), 3500),
    }));


    std::cout<<"\nMain run:\n";
    //std::cout<<Solution().run("in.txt")<<"\n";

    return 0;
}

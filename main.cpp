#include "tests/Test.hpp"

int main()
{
    Test::run(std::vector({
        std::make_pair(std::string("tests/in1.txt"), 0),
        std::make_pair(std::string("tests/in2.txt"), 1),
        std::make_pair(std::string("tests/in3.txt"), 0),
        std::make_pair(std::string("tests/in4.txt"), 1),
        std::make_pair(std::string("tests/in5.txt"), 1),
        std::make_pair(std::string("tests/in6.txt"), 1),
        std::make_pair(std::string("tests/in7.txt"), 999)
    }));


    std::cout<<"\nMain run:\n";
    std::cout<<Solution().run("in.txt")<<"\n";

    return 0;
}

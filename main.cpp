#include "tests/IntCodeComputer/TestIntcodeComputer.hpp"

int main()
{
    //TestIntcodeComputer().run();

    std::ifstream in("in.txt"); std::cout<<IntcodeComputer(in).disassemble();

    //std::cout<<"\nMain run:\n"; std::cout<<Solution().run("in.txt")<<"\n";

    return 0;
}

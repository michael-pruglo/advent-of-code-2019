#include "tests/IntCodeComputer/TestIntcodeComputer.hpp"

int main()
{
    //TestIntcodeComputer().run();

    //std::cout<<readIntcodeFile("in.txt").disassemble();

    std::cout<<"\nMain run:\n"; std::cout<<Solution().run("in.txt")<<"\n";

    return 0;
}

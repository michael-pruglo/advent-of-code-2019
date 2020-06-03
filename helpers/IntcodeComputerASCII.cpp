//
// Created by Michael on 06/02/20.
//

#include "IntcodeComputerASCII.hpp"

std::string IntcodeComputerASCII::grabOutput()
{
    auto outp = IntcodeComputer::grabOutput();
    std::string res;
    res.reserve(outp.size());
    for (char c: outp)
        res.push_back(c);
    return res;
}

IntcodeComputer::Mem_t IntcodeComputerASCII::run(const std::string& input)
{
    std::vector<Mem_t> inp;
    inp.reserve(input.size());
    for (Mem_t x: input)
        inp.push_back(x);
    return IntcodeComputer::run(inp);
}

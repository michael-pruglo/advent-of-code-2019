//
// Created by Michael on 06/02/20.
//

#ifndef UNTITLED3_INTCODECOMPUTERASCII_HPP
#define UNTITLED3_INTCODECOMPUTERASCII_HPP

#include "IntcodeComputer.hpp"

class IntcodeComputerASCII : public IntcodeComputer
{
public:
    IntcodeComputerASCII() = default;
    IntcodeComputerASCII(const std::vector<long long>& program, const std::vector<long long>& inputs) : IntcodeComputer(program, inputs) {}
    IntcodeComputerASCII(const IntcodeComputer& ic) : IntcodeComputer(ic) {}

    std::string grabOutput();
    Mem_t       run()
    {
        return run("");
    };
    Mem_t       run(const std::string& input);
};


#endif //UNTITLED3_INTCODECOMPUTERASCII_HPP

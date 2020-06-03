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
    explicit    IntcodeComputerASCII(std::istream& is) : IntcodeComputer(is) {}

    std::string grabOutput();
    Mem_t       run()
    {
        return run("");
    };
    Mem_t       run(const std::string& input);
};


#endif //UNTITLED3_INTCODECOMPUTERASCII_HPP

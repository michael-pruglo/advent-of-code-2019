//
// Created by Michael on 05/22/20.
//

#ifndef UNTITLED3_INTCODECOMPUTER_HPP
#define UNTITLED3_INTCODECOMPUTER_HPP


#include <vector>
#include <iostream>
#include <unordered_map>

class IntcodeComputer
{
    typedef int Address;
    std::vector<int>    memo,
                        startingState;
    const int           TERMINATE = -1;
    const int           INPUT = 5;

    struct Instruction
    {
        typedef int Opcode;
        typedef int Modes;

        Opcode opcode;
        Modes paramModes;
        std::vector<int> parameters;

        Instruction(IntcodeComputer& ic, Address ip) : ic(ic)
        {
            auto [op, pm] = parseValue(ic.memo[ip]);
            opcode = op;
            paramModes = pm;
            parameters = getParameters(ip+1, Instruction::paramNo.at(opcode), paramModes);
        }
        std::vector<int> getParameters(Address ip, int n, Modes paramModes);

        static const std::unordered_map<Opcode, int> paramNo;
        static bool isInstruction(int value);
        static std::pair<Opcode, Modes> parseValue(int value);

        IntcodeComputer& ic;
    };

public:
                        IntcodeComputer() = default;
    explicit            IntcodeComputer(std::istream& is);

private:
    void                readf(std::istream& is);

public:
    void                show(Address highlight = -1, std::ostream& os = std::cout) const;
    void                show(Address startAdress, Address endAdress, Address highlight = -1, std::ostream& os = std::cout) const;
    void                output(Address ip, int val, std::ostream& os = std::cout) const;
    inline int          get(Address address) const
    {
        return memo[address];
    }
    inline int          result() const
    {
        return get(0);
    }
    inline int          size() const
    {
        return memo.size();
    }

    void                reset();
    void                init(int noun, int verb);
    int                 executeInstruction(Instruction instruction, Address ip);
    int                 run(Address instructionPointer = 0)
    {
        for (int ip = 0; ip < memo.size() && ip != TERMINATE; )
        {
            if (Instruction::isInstruction(memo[ip]))
                ip = executeInstruction(Instruction(*this, ip), ip);
            else
                ++ip;
        }

        return result();
    }
};


#endif //UNTITLED3_INTCODECOMPUTER_HPP

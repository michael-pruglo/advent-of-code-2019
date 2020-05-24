//
// Created by Michael on 05/22/20.
//

#ifndef UNTITLED3_INTCODECOMPUTER_HPP
#define UNTITLED3_INTCODECOMPUTER_HPP


#include <vector>
#include <iostream>
#include <unordered_map>
#include <cmath>
#include <queue>

class IntcodeComputer
{
    typedef int Address;
    std::vector<int>    memo,
                        startingState;
    const int           TERMINATE = -1;
    std::queue<int>     input; //TODO:output as well
    int                 lastOutput = -1;

    struct Instruction
    {
        typedef int Opcode;
        typedef int Modes;

        Opcode opcode;
        Modes paramModes;
        std::vector<int> parameters;

        Instruction(IntcodeComputer& ic, Address ip) : ic(ic)
        {
            auto [op, pm] = parseValue(ic.get(ip));
            opcode = op;
            paramModes = pm;
            parameters.resize(paramNo.at(opcode));
            std::copy(ic.memo.begin()+ip+1, ic.memo.begin()+ip+1+paramNo.at(opcode), parameters.begin());
            //parameters = getParameters(ip+1, Instruction::paramNo.at(opcode), paramModes);
        }
        inline int param(int i) { return paramModes/int(std::pow(10, i))%10 ?
                                            parameters[i] :
                                            ic.get(parameters[i]);}
        inline int paramWithoutMode(int i) { return parameters[i]; }

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
    void                output(Address ip, int val, std::ostream& os = std::cout);
    inline int          get(Address address) const
    {
        return memo[address];
    }
    inline int          set(Address address, int val) { memo[address] = val; }
    inline int          result() const
    {
        return lastOutput==-1 ? get(0) : lastOutput;
    }
    inline int          size() const
    {
        return memo.size();
    }

    void                reset();
    void                init(int noun, int verb);
    int                 executeInstruction(Instruction instruction, Address ip);
    int                 run(const std::queue<int>& inputSequence, Address instructionPointer = 0)
    {
        input = inputSequence;
        for (int ip = instructionPointer; ip < memo.size() && ip != TERMINATE; )
        {
            if (Instruction::isInstruction(get(ip)))
                ip = executeInstruction(Instruction(*this, ip), ip);
            else
                ++ip;
        }

        return result();
    }
};


#endif //UNTITLED3_INTCODECOMPUTER_HPP

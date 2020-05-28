//
// Created by Michael on 05/22/20.
//

#ifndef UNTITLED3_INTCODECOMPUTER_HPP
#define UNTITLED3_INTCODECOMPUTER_HPP
//#define VERBOSE

#include <vector>
#include <iostream>
#include <cmath>
#include <queue>
#include <unordered_map>

class IntcodeComputer
{
public:
    typedef int Addr_t;
    typedef long long Mem_t;

                        IntcodeComputer() = default;
    explicit            IntcodeComputer(std::istream& is);

    inline Mem_t        get(Addr_t address)
    {
        if(address>=memo.size()) memo.resize(address+1, 0); return memo[address];
    }
    inline void         set(Addr_t address, Mem_t val)
    {
        if(address>=memo.size())
            memo.resize(address+1, 0);
        memo[address] = val;
    }
    inline Mem_t        result() const
    {
        return outputSeqeunce.empty() ? _get_const(0) : outputSeqeunce.back();
    }
    inline int          size() const
    {
        return memo.size();
    }
    inline bool         wasTerminated() const
    {
        return terminated;
    }
    inline auto         grabOutput()
    {
        auto res = outputSeqeunce; outputSeqeunce.clear(); return res;
    }

    void                reset();
    Mem_t               run(const std::vector<Mem_t>& inputSeq = std::vector<Mem_t>())
    {
        return run(std::move(inputSeq), ip);
    }
    Mem_t               run(const std::vector<Mem_t>& inputSeq, Addr_t instructionPointer);





private:
    std::vector<Mem_t>  memo,
                        startingState;
    bool                terminated = false;
    Addr_t              ip = 0;
    Addr_t              relativeBase = 0;

    std::queue<Mem_t>   inputSequence;
    std::vector<Mem_t>  outputSeqeunce;

    struct Instruction
    {
        typedef int Opcode_t;
        typedef int ModeCollection_t;
        enum Mode { POSITION=0, IMMEDIATE=1, RELATIV=2 };

        Opcode_t opcode;
        ModeCollection_t paramModes;
        std::vector<Mem_t> parameters;

        Instruction(IntcodeComputer& ic, Addr_t ip) : ic(ic)
        {
            auto [op, pm] = parseValue(ic.get(ip));
            opcode = op;
            paramModes = pm;
            parameters.resize(paramNo.at(opcode));
            std::copy(ic.memo.begin()+ip+1, ic.memo.begin()+ip+1+paramNo.at(opcode), parameters.begin());
        }
        Mode getParamMode(int i)
        {
            return Mode(paramModes/int(std::pow(10, i))%10);
        }
        Mem_t param(int i);
        Mem_t paramAsAddress(int i);

        static const std::unordered_map<Opcode_t, int> paramNo;
        static bool isInstruction(Mem_t value);
        static std::pair<Opcode_t, ModeCollection_t> parseValue(Mem_t value);

        IntcodeComputer& ic;
    };

    void                readf(std::istream& is);
    inline Mem_t        _get_const(Addr_t address) const
    {
        return memo[address];
    }
    void                show(Addr_t highlight = -1, std::ostream& os = std::cout) const;
    void                show(Addr_t startAdress, Addr_t endAdress, Addr_t highlight = -1, std::ostream& os = std::cout) const;
};


#endif //UNTITLED3_INTCODECOMPUTER_HPP

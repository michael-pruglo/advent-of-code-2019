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
    typedef int Addr_t;
    typedef long long Mem_t;
    enum Status { READY, AWAITING_INPUT, TERMINATED };
    std::vector<Mem_t>  memo,
                        startingState;
    Status              status;
    Addr_t             currIp;
    Addr_t             relativeBase;

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
            //parameters = getParameters(ip+1, Instruction::paramNo.at(opcode), paramModes);
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

public:
                        IntcodeComputer() = default;
    explicit            IntcodeComputer(std::istream& is);

private:
    void                readf(std::istream& is);
    void                setStatus(Status st);
    inline Mem_t        _get_const(Addr_t address) const
    {
        return memo[address];
    }

public:
    void                show(Addr_t highlight = -1, std::ostream& os = std::cout) const;
    void                show(Addr_t startAdress, Addr_t endAdress, Addr_t highlight = -1, std::ostream& os = std::cout) const;
    void                output(Addr_t ip, Mem_t val, std::ostream& os = std::cout);
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
        return status==TERMINATED;
    }
    inline std::string  currentStatusString() const
    {
        return status == READY ? "READY"
             : status == TERMINATED ? "TERMINATED" :
             status == AWAITING_INPUT ? "AWAITING_INPUT" :
             "UNKNOWN";
    }
    inline auto         grabOutput()
    {
        auto res = outputSeqeunce; outputSeqeunce.clear(); return res;
    }

    void                reset();
    void                init(Mem_t noun, Mem_t verb);
    Addr_t             executeInstruction(Instruction instruction, Addr_t ip);
    Mem_t               run(std::queue<Mem_t> inputSeq = std::queue<Mem_t>())
    {
        return run(std::move(inputSeq), currIp);
    }
    Mem_t               run(std::queue<Mem_t> inputSeq, Addr_t instructionPointer);
};


#endif //UNTITLED3_INTCODECOMPUTER_HPP

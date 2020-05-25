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
    typedef int Address;
    typedef long long Mem_t;
    enum Status { READY, AWAITING_INPUT, TERMINATED };
    std::vector<Mem_t>  memo,
                        startingState;
    Status              status;
    Address             currIp;
    Address             relativeBase;

    std::queue<Mem_t>   inputSequence;
    std::vector<Mem_t>  outputSeqeunce;

    struct Instruction
    {
        typedef int Opcode;
        typedef int ModeCollection;
        enum Mode { POSITION=0, IMMEDIATE=1, RELATIV=2 };

        Opcode opcode;
        ModeCollection paramModes;
        std::vector<Mem_t> parameters;

        Instruction(IntcodeComputer& ic, Address ip) : ic(ic)
        {
            auto [op, pm] = parseValue(ic.get(ip));
            opcode = op;
            paramModes = pm;
            parameters.resize(paramNo.at(opcode));
            std::copy(ic.memo.begin()+ip+1, ic.memo.begin()+ip+1+paramNo.at(opcode), parameters.begin());
            //parameters = getParameters(ip+1, Instruction::paramNo.at(opcode), paramModes);
        }
        inline Mode getParamMode(int i) { return Mode(paramModes/int(std::pow(10, i))%10); }
        inline Mem_t param(int i);
        inline Mem_t paramWithoutMode(int i) { return parameters[i]; }

        static const std::unordered_map<Opcode, int> paramNo;
        static bool isInstruction(Mem_t value);
        static std::pair<Opcode, ModeCollection> parseValue(Mem_t value);

        IntcodeComputer& ic;
    };

public:
                        IntcodeComputer() = default;
    explicit            IntcodeComputer(std::istream& is);

private:
    void                readf(std::istream& is);
    void                setStatus(Status st);

public:
    void                show(Address highlight = -1, std::ostream& os = std::cout) const;
    void                show(Address startAdress, Address endAdress, Address highlight = -1, std::ostream& os = std::cout) const;
    void                output(Address ip, Mem_t val, std::ostream& os = std::cout);
    inline Mem_t        get(Address address) const { return memo[address]; }
    inline void         set(Address address, Mem_t val) { memo[address] = val; }
    inline Mem_t        result() const { return outputSeqeunce.empty() ? get(0) : outputSeqeunce.back(); }
    inline int          size() const { return memo.size(); }
    inline bool         wasTerminated() const { return status==TERMINATED; }
    inline std::string  currentStatusString() const { return status == READY ? "READY" : status == TERMINATED ? "TERMINATED" : status == AWAITING_INPUT ? "AWAITING_INPUT" : "UNKNOWN"; }
    inline auto         getOutput() { auto res = outputSeqeunce; outputSeqeunce.clear(); return res; }

    void                reset();
    void                init(Mem_t noun, Mem_t verb);
    Address             executeInstruction(Instruction instruction, Address ip);
    Mem_t               run(std::queue<Mem_t> inputSeq = std::queue<Mem_t>()) { return run(std::move(inputSeq), currIp); }
    Mem_t               run(std::queue<Mem_t> inputSeq, Address instructionPointer);
};


#endif //UNTITLED3_INTCODECOMPUTER_HPP

//
// Created by Michael on 05/22/20.
//

#ifndef UNTITLED3_INTCODECOMPUTER_HPP
#define UNTITLED3_INTCODECOMPUTER_HPP
//#define VERBOSE

#include <vector>
#include <iostream>
#include <unordered_map>
#include <cmath>
#include <queue>

class IntcodeComputer
{
    typedef int Address;
    enum Status { READY, AWAITING_INPUT, TERMINATED };
    std::vector<int>    memo,
                        startingState;
    Status              status;
    Address             currIp;

    std::queue<int>     inputSequence;
    std::vector<int>    outputSeqeunce;

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
        inline bool isImmediateMode(int i) { return paramModes/int(std::pow(10, i))%10; }
        inline int param(int i) { return  isImmediateMode(i) ?
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
    void                setStatus(Status st);

public:
    void                show(Address highlight = -1, std::ostream& os = std::cout) const;
    void                show(Address startAdress, Address endAdress, Address highlight = -1, std::ostream& os = std::cout) const;
    void                output(Address ip, int val, std::ostream& os = std::cout);
    inline int          get(Address address) const { return memo[address]; }
    inline int          set(Address address, int val) { memo[address] = val; }
    inline int          result() const { return outputSeqeunce.empty() ? get(0) : outputSeqeunce.back(); }
    inline int          size() const { return memo.size(); }
    inline bool         wasTerminated() const { return status==TERMINATED; }
    inline std::string  currentStatusString() const { return status == READY ? "READY" : status == TERMINATED ? "TERMINATED" : status == AWAITING_INPUT ? "AWAITING_INPUT" : "UNKNOWN"; }
    inline auto         getOutput() { auto res = outputSeqeunce; outputSeqeunce.clear(); return res; }

    void                reset();
    void                init(int noun, int verb);
    int                 executeInstruction(Instruction instruction, Address ip);
    int                 run(std::queue<int> inputSeq = std::queue<int>()) { return run(std::move(inputSeq), currIp); }
    int                 run(std::queue<int> inputSeq, Address instructionPointer)
    {
        if (status == AWAITING_INPUT && !inputSeq.empty())
            setStatus(READY);
        if (status != READY)
        {
            std::cout<<"[MACHINE ERROR] Calling Run() on a non-READY machine. Current status: "<<currentStatusString()<<"\n";
            return -1;
        }

        for ( ; !inputSeq.empty() ; inputSeq.pop()) inputSequence.push(inputSeq.front());
#ifdef VERBOSE
        std::cout<<"Run({"; for (auto temp = inputSeq; !temp.empty(); temp.pop()) std::cout<<temp.front()<<" "; std::cout<<"},"<<instructionPointer<<")\n";
        std::cout<<"current input queue: ["; for (auto temp = inputSequence; !temp.empty(); temp.pop()) std::cout<<temp.front()<<" "; std::cout<<"]\n";
#endif

        for (currIp = instructionPointer; currIp < memo.size() && status == READY; )
        {
            if (Instruction::isInstruction(get(currIp)))
                currIp = executeInstruction(Instruction(*this, currIp), currIp);
            else
                ++currIp;
        }

#ifdef VERBOSE
        std::cout << "returning with status: " << currentStatusString() << "\n";
#endif
        return result();
    }
};


#endif //UNTITLED3_INTCODECOMPUTER_HPP

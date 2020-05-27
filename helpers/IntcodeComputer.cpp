//
// Created by Michael on 05/22/20.
//

#include <iomanip>
#include <windows.h>
#include <cassert>
#include "IntcodeComputer.hpp"

const std::unordered_map<IntcodeComputer::Instruction::Opcode_t, int> IntcodeComputer::Instruction::paramNo =
        {
                {99, 0},
                {1, 3},
                {2, 3},
                {3, 1},
                {4, 1},
                {5, 2},
                {6, 2},
                {7, 3},
                {8, 3},
                {9, 1}
        };

bool IntcodeComputer::Instruction::isInstruction(IntcodeComputer::Mem_t value)
{
    auto [tryOpcode, tryParamModes] = parseValue(value);
    return paramNo.count(tryOpcode);
}

std::pair<IntcodeComputer::Instruction::Opcode_t,
          IntcodeComputer::Instruction::ModeCollection_t>
          IntcodeComputer::Instruction::parseValue(IntcodeComputer::Mem_t value)
{
    Mem_t opcode = value % 100;
    Mem_t paramModes = value / 100;
    return std::make_pair(opcode, paramModes);
}

IntcodeComputer::Mem_t IntcodeComputer::Instruction::param(int i)
{
    switch (getParamMode(i))
    {
        case Mode::POSITION: return ic.get(parameters[i]);
        case Mode::IMMEDIATE: return parameters[i];
        case Mode::RELATIV: return ic.get(ic.relativeBase + parameters[i]);
    }
    std::cout<<"[FATAL ERROR] wrong parameter mode: "<<getParamMode(i)<<"\n";
    exit(4);
}

IntcodeComputer::Mem_t IntcodeComputer::Instruction::paramAsAddress(int i)
{
    switch (getParamMode(i))
    {
        case Mode::POSITION: return parameters[i];
        case Mode::RELATIV: return ic.relativeBase + parameters[i];
    }
    std::cout<<"[FATAL ERROR] wrong parameter as address mode: "<<getParamMode(i)<<"\n";
    exit(4);
}

IntcodeComputer::IntcodeComputer(std::istream& is)
{
    readf(is);
    startingState = memo;
    setStatus(READY);
    currIp = 0;
    relativeBase = 0;
}

void IntcodeComputer::readf(std::istream& is)
{
    char comma;
    for (Mem_t i; is>>i; is>>comma)
        memo.push_back(i);
    if (comma=='>')
    {
        inputSequence.push(memo.back());
        memo.pop_back();
    }
#ifdef VERBOSE
    std::cout<<"INPUT = ";
    if (inputSequence.empty())
        std::cout<<"NONE\n";
    else
        std::cout<<inputSequence.back()<<" "<<comma<<"\n";
    show();
#endif
}

enum Color
{
    BRIGHTWHITE=0, BLUE, GREEN, AQUA, RED, PURPLE, YELLOW, WHITE, GRAY,
    LIGHTBLUE, LIGHTGREEN, LIGHTAQUA, LIGHTRED, LIGHTPURPLE, LIGHTYELLOW, BLACK
};
void changeColor(unsigned foreground = WHITE, unsigned background = 0)
{
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ),
                             (background<<4) | foreground );
}

void drawLine(int len, std::ostream& os = std::cout)
{
    for (int i = 0; i < len; ++i) std::cout<<"=";
    std::cout<<"\n";
}

void IntcodeComputer::show(Addr_t highlight, std::ostream& os) const
{
    show(0, memo.size(), highlight, os);
}

void IntcodeComputer::show(Addr_t startAdress, Addr_t endAdress,
                           Addr_t highlight,
                           std::ostream& os) const
{
    const int COLUMNS = 10, ADDRESS_W = 4, ITEM_W = 10, LINE_LEN = 1+ADDRESS_W+2+COLUMNS*ITEM_W,
            FORE_COLOR = BRIGHTWHITE, BACK_COLOR = 0,
            HIGHLIGHT_FORE_COLOR = BLACK, HIGHLIGHT_BACK_COLOR = LIGHTRED;

    changeColor(FORE_COLOR, BACK_COLOR);
    drawLine(LINE_LEN);
    for (int i = startAdress; i < endAdress; i+=COLUMNS)
    {
        os << "[" << std::setw(ADDRESS_W) << i << "] ";
        for (int j = i; j < i+COLUMNS && j < endAdress; ++j)
        {
            os << std::flush;
            if (highlight == j) changeColor(HIGHLIGHT_FORE_COLOR, HIGHLIGHT_BACK_COLOR);
            os << std::setw(ITEM_W) << _get_const(j);
            os << std::flush;
            if (highlight == j) changeColor(FORE_COLOR, BACK_COLOR);
        }
        os << "\n";
    }
    drawLine(LINE_LEN);
    changeColor();
}

void IntcodeComputer::output(Addr_t ip, IntcodeComputer::Mem_t val, std::ostream& os)
{
#ifdef VERBOSE
    changeColor(BLACK, GREEN);
    std::cout << "@" << ip << " output: " << val << "\n";
    changeColor();
#endif
    outputSeqeunce.push_back(val);
}

void IntcodeComputer::reset()
{
    memo = startingState;
    setStatus(READY);
    currIp = 0;
    relativeBase = 0;
}

void IntcodeComputer::init(IntcodeComputer::Mem_t noun, IntcodeComputer::Mem_t verb)
{
    set(1, noun);
    set(2, verb);
}

IntcodeComputer::Addr_t IntcodeComputer::executeInstruction(IntcodeComputer::Instruction instruction, IntcodeComputer::Addr_t ip)
{
#ifdef VERBOSE
    std::cout<< "execute __@"<<ip<<"__"<<instruction.opcode<<"(";
    for (int i = 0; i < instruction.parameters.size(); ++i)
    {
        auto pmode = instruction.getParamMode(i);
        std::cout<<(pmode==Instruction::IMMEDIATE?"":pmode==Instruction::POSITION?"@":"&")<<
                 instruction.parameters[i]<<",";
    }
    std::cout<<")\n";
    std::cout<<"relative base = "<<relativeBase<<"\n";
#endif
    switch (instruction.opcode) {
        case 99:
            setStatus(TERMINATED);
            return -1;

        case 1: //add two parameters and write to address
        case 2: //mul two parameters and write to address
            set(instruction.paramAsAddress(2), instruction.opcode == 1 ?
                                            instruction.param(0) + instruction.param(1) :
                                            instruction.param(0) * instruction.param(1));
            break;

        case 3: //write INPUT to address
            //assert(!inputSequence.empty());
            if (inputSequence.empty())
                setStatus(AWAITING_INPUT);
            else
            {
                //not without mode
                set(instruction.paramAsAddress(0), inputSequence.front());
                inputSequence.pop();
            }
            break;

        case 4: //output the value at the address
            output(ip, instruction.param(0));
            break;

        case 5: //jump-if-true
        case 6: //jump-if-false
            if (instruction.param(0) && instruction.opcode==5
                ||!instruction.param(0) && instruction.opcode==6)
                return instruction.param(1);
            else
                break;

        case 7: //less than - evaluate and write to address
        case 8: //equals - evaluate and write to address
            set(instruction.paramAsAddress(2), instruction.opcode == 7 ?
                                              instruction.param(0) < instruction.param(1) :
                                              instruction.param(0) == instruction.param(1));
            break;

        case 9: //adjust the relative base
            relativeBase += instruction.param(0);
            break;

        default:
            std::cout<<"[FATAL ERROR] Unsupported instruction: "<<instruction.opcode<<"\n";
            exit(5);
    }
#ifdef VERBOSE
    show(ip);
#endif

    Addr_t newIp = status == READY ?
            ip + Instruction::paramNo.at(instruction.opcode)+1 :
                   ip;
    return newIp;
}

void IntcodeComputer::setStatus(IntcodeComputer::Status st)
{
    switch (st)
    {
        case READY:
            status = READY;
#ifdef VERBOSE
            std::cout<<"[status] Machine set ready.\n";
#endif
            break;
        case AWAITING_INPUT:
            status = AWAITING_INPUT;
#ifdef VERBOSE
            std::cout<<"[status] Machine paused. Awaiting input.\n";
#endif
            break;
        case TERMINATED:
            status = TERMINATED;
#ifdef VERBOSE
        std::cout<<"[status] Machine terminated.\n";
#endif
            break;
        default:
            std::cout<<"[FATAL ERROR]: setStatus("<<st<<") - unknown status\n";
            exit(3);
    }
}

IntcodeComputer::Mem_t IntcodeComputer::run(std::queue<IntcodeComputer::Mem_t> inputSeq, IntcodeComputer::Addr_t instructionPointer)
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


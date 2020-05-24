//
// Created by Michael on 05/22/20.
//
//#define VERBOSE

#include <iomanip>
#include <windows.h>
#include "IntcodeComputer.hpp"

const std::unordered_map<IntcodeComputer::Instruction::Opcode, int> IntcodeComputer::Instruction::paramNo =
        {
                {99, 0},
                {1, 3},
                {2, 3},
                {3, 1},
                {4, 1},
                {5, 2},
                {6, 2},
                {7, 3},
                {8, 3}
        };

bool IntcodeComputer::Instruction::isInstruction(int value)
{
    auto [tryOpcode, tryParamModes] = parseValue(value);
    return paramNo.count(tryOpcode);
}

std::pair<IntcodeComputer::Instruction::Opcode,
          IntcodeComputer::Instruction::Modes>
          IntcodeComputer::Instruction::parseValue(int value)
{
    int opcode = value % 100;
    int paramModes = value / 100;
    return std::make_pair(opcode, paramModes);
}

IntcodeComputer::IntcodeComputer(std::istream& is)
{
    readf(is);
    startingState = memo;
}

void IntcodeComputer::readf(std::istream& is)
{
    char comma;
    for (int i; is>>i; is>>comma)
        memo.push_back(i);
    if (comma=='>')
    {
        inputSequence.push(memo.back());
        memo.pop_back();
    }
#ifdef VERBOSE
    std::cout<<"INPUT = "<<INPUT<<" "<<comma<<"\n";
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

void IntcodeComputer::show(Address highlight, std::ostream& os) const
{
    show(0, memo.size(), highlight, os);
}

void IntcodeComputer::show(Address startAdress, Address endAdress,
                           Address highlight,
                           std::ostream& os) const
{
    const int COLUMNS = 10, ADDRESS_W = 4, ITEM_W = 6, LINE_LEN = 1+ADDRESS_W+2+COLUMNS*ITEM_W,
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
            os << std::setw(ITEM_W) << get(j);
            os << std::flush;
            if (highlight == j) changeColor(FORE_COLOR, BACK_COLOR);
        }
        os << "\n";
    }
    drawLine(LINE_LEN);
    changeColor();
}

void IntcodeComputer::output(Address ip, int val, std::ostream& os)
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
}

void IntcodeComputer::init(int noun, int verb)
{
    set(1, noun);
    set(2, verb);
}

IntcodeComputer::Address IntcodeComputer::executeInstruction(IntcodeComputer::Instruction instruction, IntcodeComputer::Address ip)
{
#ifdef VERBOSE
    std::cout<< "execute "<<instruction.opcode<<"(";
    for (auto x: instruction.parameters) std::cout<<x<<",";
    std::cout<<")\n";
#endif
    switch (instruction.opcode) {
        case 99:
            return TERMINATE;

        case 1: //add two parameters and write to address
        case 2: //mul two parameters and write to address
            set(instruction.paramWithoutMode(2), instruction.opcode==1?
                                            instruction.param(0) + instruction.param(1) :
                                            instruction.param(0) * instruction.param(1));
            break;

        case 3: //write INPUT to address
            set(instruction.paramWithoutMode(0), inputSequence.front());
            inputSequence.pop();
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
            set(instruction.paramWithoutMode(2), instruction.opcode==7 ?
                                              instruction.param(0) < instruction.param(1) :
                                              instruction.param(0) == instruction.param(1));
            break;
    }
#ifdef VERBOSE
    show(ip);
#endif

    Address newIp = ip + Instruction::paramNo.at(instruction.opcode)+1;
    return newIp;
}


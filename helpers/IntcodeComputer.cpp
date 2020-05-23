//
// Created by Michael on 05/22/20.
//

#include "IntcodeComputer.hpp"

IntcodeComputer::IntcodeComputer(std::istream& is)
{
    readf(is);
    startingState = memo;
}

void IntcodeComputer::readf(std::istream& is)
{
    int i;
    for (char comma; is>>i; is>>comma)
        memo.push_back(i);
}

void IntcodeComputer::show(int highlight, std::ostream& os) const
{
    show(0, memo.size(), highlight, os);
}

void IntcodeComputer::show(int startAdress, int endAdress,
        int highlight,
        std::ostream& os) const
{
    for (int i = startAdress; i < endAdress; ++i)
    {
        if (highlight == i)
            os << "{" << memo[i] << "} ";
        else
            os << memo[i] << " ";
    }
    os << "\n";
}

void IntcodeComputer::reset()
{
    memo = startingState;
}

void IntcodeComputer::init(int noun, int verb)
{
    memo[1] = noun;
    memo[2] = verb;
}


//
// Created by Michael on 05/22/20.
//

#include <iomanip>
#include <windows.h>
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

enum Color
{
    BLACK=0, BLUE, GREEN, AQUA, RED, PURPLE, YELLOW, WHITE, GRAY,
    LIGHTBLUE, LIGHTGREEN, LIGHTAQUA, LIGHTRED, LIGHTPURPLE, LIGHTYELLOW, BRIGHTWHITE
};
void changeColor(unsigned foreground = WHITE, unsigned background = BLACK)
{
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ),
                             (background<<4) | foreground );
}

void drawLine(int len, std::ostream& os = std::cout)
{
    for (int i = 0; i < len; ++i) std::cout<<"=";
    std::cout<<"\n";
}

void IntcodeComputer::show(int highlight, std::ostream& os) const
{
    show(0, memo.size(), highlight, os);
}

void IntcodeComputer::show(int startAdress, int endAdress,
        int highlight,
        std::ostream& os) const
{
    const int COLUMNS = 10, ADDRESS_W = 4, ITEM_W = 6, LINE_LEN = 1+ADDRESS_W+2+COLUMNS*ITEM_W,
            FORE_COLOR = WHITE, BACK_COLOR = BLACK,
            HIGHLIGHT_FORE_COLOR = RED, HIGHLIGHT_BACK_COLOR = GRAY;

    changeColor(FORE_COLOR, BACK_COLOR);
    drawLine(LINE_LEN);
    for (int i = startAdress; i < endAdress; i+=COLUMNS)
    {
        os << "[" << std::setw(ADDRESS_W) << i << "] ";
        for (int j = i; j < i+COLUMNS && j < endAdress; ++j)
        {
            os << std::flush;
            if (highlight == j) changeColor(HIGHLIGHT_FORE_COLOR, HIGHLIGHT_BACK_COLOR);
            os << std::setw(ITEM_W) << memo[j];
            os << std::flush;
            if (highlight == j) changeColor(FORE_COLOR, BACK_COLOR);
        }
        os << "\n";
    }
    drawLine(LINE_LEN);
    changeColor();
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


//
// Created by Michael on 05/26/20.
//

#ifndef UNTITLED3_EMERGENCYHULLPAINTINGROBOT_HPP
#define UNTITLED3_EMERGENCYHULLPAINTINGROBOT_HPP


#include <vector>
#include "IntcodeComputer.hpp"

class EmergencyHullPaintingRobot
{
    const int SIZE = 100;
    std::vector<std::vector<bool>> map = std::vector<std::vector<bool>>(SIZE, std::vector<bool>(SIZE, 0));
    enum Direction { UP, RIGHT, DOWN, LEFT };
    inline Direction turnRight(Direction curr) { return Direction((curr+1)%4); }
    inline Direction turnLeft(Direction curr) { return Direction((4+curr-1)%4); }
    std::pair<int, int> move(int i, int j, Direction dir);

    IntcodeComputer ic;
public:
    void init(std::istream& in) { ic = IntcodeComputer(in); }
    void show();
    // returns the number of painted panels
    int run();
};


#endif //UNTITLED3_EMERGENCYHULLPAINTINGROBOT_HPP

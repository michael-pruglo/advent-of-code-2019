//
// Created by Michael on 05/26/20.
//

#ifndef UNTITLED3_ARCADECABINET_HPP
#define UNTITLED3_ARCADECABINET_HPP


#include <vector>
#include "IntcodeComputer.hpp"

class ArcadeCabinet
{
    static constexpr int W = 42, H = 24, UNDEF = -1;
    std::vector<std::vector<int>> screen = std::vector<std::vector<int>>(H, std::vector<int>(W, UNDEF));

    IntcodeComputer ic;

    int joystick = 0;
    int score = 0;

public:
    void init(std::istream& in) { ic = IntcodeComputer(in); }

    int run();
    void show();
};


#endif //UNTITLED3_ARCADECABINET_HPP

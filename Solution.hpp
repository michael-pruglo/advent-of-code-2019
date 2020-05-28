//
// Created by Michael on 05/22/20.
//

#ifndef UNTITLED3_SOLUTION_HPP
#define UNTITLED3_SOLUTION_HPP

#include <fstream>
#include <numeric>
#include <algorithm>
#include <map>
#include <set>
#include "helpers/IntcodeComputer.hpp"

class Solution
{
    enum Movement { NORTH=1, SOUTH=2, WEST=3, EAST=4};
    typedef char Cell;
    const int W = 50, H = 50;
    std::vector<std::vector<Cell>> map = std::vector<std::vector<Cell>>(H,
                                                                  std::vector<Cell>(W, ' '));
    std::vector<std::vector<bool>> visited = std::vector<std::vector<bool>>(H,
                                                                        std::vector<bool>(W, false));
    int finishI=-1, finishJ=-1;

    IntcodeComputer ic;

private:
    Movement opposite(Movement mov) {
        switch (mov) {
            case NORTH : return SOUTH;
            case SOUTH : return NORTH;
            case WEST : return EAST;
            case EAST : return WEST;
        }
    }
    Cell move(Movement mov) { return Cell(ic.run({mov})); }
    void showMap();

public:

    auto run(const std::string& inFileName)
    {
        std::ifstream inFile(inFileName);
        ic = IntcodeComputer(inFile);

        /*ic.run();
        auto output = ic.grabOutput();
        int n=0, m=0;
        for (char ch: output)
            ch==10 ? ++n,m=0 : map[n][m++] = ch;

        showMap();

        std::cout<<"newline = "<<int('\n')<<"\n";
        ic.reset();*/
        ic.set(0, 2);


        std::string mmr =  "A,B,A,C,A,B,C,B,C,A";
        std::string funA = "L,12,R,4,R,4,L,6";
        std::string funB = "L,12,R,4,R,4,R,12";
        std::string funC = "L,10,L,6,R,4";
        std::string input = mmr + '\n'
                            + funA + '\n'
                            + funB + '\n'
                            + funC + '\n'
                            + 'n' + '\n';

        std::vector<long long> inqueue;
        for (auto& ch: input) inqueue.push_back(ch);
        auto res = ic.run(inqueue);

        auto out = ic.grabOutput();
        for (auto& x: out) std::cout<<char(x);

        std::cout<<"\n\n\n==end\n";

        return res;
    }

public:
    long long runComputer(const std::string& inFileName);
    long long runAmplifier(const std::string& inFileName);
    long long runAmplifierFeedbackloop(const std::string& inFileName);
};

#endif //UNTITLED3_SOLUTION_HPP

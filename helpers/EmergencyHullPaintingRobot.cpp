//
// Created by Michael on 05/26/20.
//

#include <cassert>
#include <set>
#include "EmergencyHullPaintingRobot.hpp"

int EmergencyHullPaintingRobot::run()
{
    int i = SIZE/2, j = SIZE/2;
    Direction dir = UP;
    std::set<int> painted;

    map[i][j] = 1;

    while (!ic.wasTerminated())
    {
        //std::cout<<"ij: "<<i<<", "<<j<<" -> ";
        ic.run(std::queue<long long>({map[i][j]}));
        auto output = ic.getOutput();
        assert(output.size()==2);

        if (map[i][j] != output[0])
        {
            map[i][j] =  output[0]; //paint
            painted.insert(i*SIZE+j);
        }

        dir = output[1] ? turnLeft(dir) : turnRight(dir);
        auto [newI, newJ] = move(i, j, dir);
        i = newI, j = newJ;
        //std::cout<<" "<<i<<", "<<j<<"\n";
    }

    show();
    return painted.size();
}

std::pair<int, int> EmergencyHullPaintingRobot::move(int i, int j, EmergencyHullPaintingRobot::Direction dir)
{
    switch (dir) {
        case UP:    --i; break;
        case RIGHT: ++j; break;
        case DOWN:  ++i; break;
        case LEFT:  --j; break;
    }
    return {i, j};
}

void EmergencyHullPaintingRobot::show()
{
    for (const auto& row : map)
    {
        for (const auto& pix : row)
            std::cout<<(pix?'#':'.');
        std::cout<<"\n";
    }
}

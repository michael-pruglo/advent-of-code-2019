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
#include <thread>
#include <mutex>
#include "helpers/IntcodeComputer.hpp"
#include "helpers/IntcodeComputerASCII.hpp"

class Solution
{

    struct Moon
    {
        int x, y, z;
        int xVel=0, yVel=0, zVel=0;

        int potentialEnergy() { return std::abs(x)+std::abs(y)+std::abs(z); }
        int kineticEnergy() { return std::abs(xVel)+std::abs(yVel)+std::abs(zVel); }
        bool operator==(const Moon& m2) const
        {
            return
                x==m2.x &&
                y==m2.y &&
                z==m2.z &&
                xVel==m2.xVel &&
                yVel==m2.yVel &&
                zVel==m2.zVel;
            ;
        }
    };
    void bringCloser(int a, int& aVel, int b, int& bVel)
    {
             if (a<b) {++aVel; --bVel;}
        else if (a>b) {--aVel; ++bVel;}
    }
    void gravity(Moon& m1, Moon& m2)
    {
        //bringCloser(m1.x, m1.xVel, m2.x, m2.xVel);
        //bringCloser(m1.y, m1.yVel, m2.y, m2.yVel);
        bringCloser(m1.z, m1.zVel, m2.z, m2.zVel);
    }
    void velocity(Moon& m)
    {
        //m.x += m.xVel;
        //m.y += m.yVel;
        m.z += m.zVel;
    }

public:

    auto run(const std::string& inFileName)
    {
        std::ifstream inFile(inFileName);
        std::vector<Moon> moons;
        for ( int x, y, z; inFile>>x>>y>>z; moons.push_back({x,y,z}));
        auto stMoons = moons;

        for (auto& x: moons) std::cout<<"\t"<<x.x<<" "<<x.y<<" "<<x.z<<"       "<<x.xVel<<" "<<x.yVel<<" "<<x.zVel<<"\n";

        for (long long t = 1; ; ++t)
        {
            for (int i = 0; i < moons.size(); ++i)
                for (int j = i+1; j < moons.size(); ++j)
                    gravity(moons[i], moons[j]);

            for (auto& x: moons)
                velocity(x);

            if (t%10'000'000==0) {
                std::cout << "time " << t << "\n";
                for (auto& x: moons)
                    std::cout << "\t" << x.x << " " << x.y << " " << x.z << "       " << x.xVel << " " << x.yVel << " "
                              << x.zVel << "\n";
            }
            if (moons == stMoons) { std::cout<<"after "<<t<<" steps\n"; break;}
        }

        return 0;
    }

public:
    long long runComputer(const std::string& inFileName);
    long long runAmplifier(const std::string& inFileName);
    long long runAmplifierFeedbackloop(const std::string& inFileName);
};

#endif //UNTITLED3_SOLUTION_HPP

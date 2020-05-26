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
#include "helpers/EmergencyHullPaintingRobot.hpp"
#include "helpers/ArcadeCabinet.hpp"

class Solution
{
    enum Movement { NORTH=1, SOUTH=2, WEST=3, EAST=4};
    enum Cell { UNKNOWN=-1, WALL=0, EMPTY=1, FINISH=2 };
    const int W = 50, H = 50;
    std::vector<std::vector<Cell>> map = std::vector<std::vector<Cell>>(H,
                                                                  std::vector<Cell>(W, UNKNOWN));
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
    Cell move(Movement mov) { return Cell(ic.run(std::queue<long long>({mov}))); }
    void exploreWay(Movement mov, int newI, int newJ) {
        if (map[newI][newJ] != UNKNOWN)
        {
#ifdef VERBOSE
            std::cout<<" already explored. \n";
#endif
            return;
        }

        Cell status = move(mov);
#ifdef VERBOSE
        std::cout<<"status: "<<int(status)<<"\n";
#endif
        map[newI][newJ] = status;
        if (status == FINISH) {finishI=newI; finishJ=newJ;}
        if (status != WALL)
        {
            explore(newI, newJ);
            move(opposite(mov));
        }
    }
    void explore(int i, int j)
    {
#ifdef VERBOSE
        showMap(i, j);
        std::cout<<"explore("<<i<<", "<<j<<")\n";
        std::cout<<"\t trying to move north: ";
#endif
        exploreWay(NORTH, i-1, j);
#ifdef VERBOSE
        std::cout<<"\t trying to move south: ";
#endif
        exploreWay(SOUTH, i+1, j);
#ifdef VERBOSE
        std::cout<<"\t trying to move west: ";
#endif
        exploreWay(WEST, i, j-1);
#ifdef VERBOSE
        std::cout<<"\t trying to move east: ";
#endif
        exploreWay(EAST, i, j+1);
    }
    void showMap(int droidI, int droidJ);


    void dfs(int i, int j, int dist)
    {
        if (visited[i][j]) return;
        visited[i][j] = true;

        if (map[i][j]==FINISH)
        {
            std::cout<<"Dist = "<<dist<<"\n";
            exit(0);
        }

        if (map[i-1][j] >= EMPTY) dfs(i-1, j, dist+1);
        if (map[i+1][j] >= EMPTY) dfs(i+1, j, dist+1);
        if (map[i][j-1] >= EMPTY) dfs(i, j-1, dist+1);
        if (map[i][j+1] >= EMPTY) dfs(i, j+1, dist+1);
    }

    int bfs(int i, int j) {
        visited = std::vector<std::vector<bool>>(H,std::vector<bool>(W, false));
        std::queue<std::tuple<int, int, int>> q;
        q.push({i, j, 0});

        int time = 0;
        while (!q.empty())
        {
            auto [currI, currJ, currTime] = q.front();
            visited[currI][currJ] = true;
            if (map[currI-1][currJ] >= EMPTY && !visited[currI-1][currJ]) q.push({currI-1, currJ, currTime+1});
            if (map[currI+1][currJ] >= EMPTY && !visited[currI+1][currJ]) q.push({currI+1, currJ, currTime+1});
            if (map[currI][currJ-1] >= EMPTY && !visited[currI][currJ-1]) q.push({currI, currJ-1, currTime+1});
            if (map[currI][currJ+1] >= EMPTY && !visited[currI][currJ+1]) q.push({currI, currJ+1, currTime+1});
            q.pop();
            time = currTime;
        }
        return time;
    }
public:

    auto run(const std::string& inFileName)
    {
        std::ifstream inFile(inFileName);
        ic = IntcodeComputer(inFile);

        int i = H/2, j = W/2;
        map[i][j] = EMPTY;
        explore(i, j);
        showMap(i, j);


        return bfs(finishI, finishJ);
    }

public:
    long long runComputer(const std::string& inFileName);
    long long runAmplifier(const std::string& inFileName);
    long long runAmplifierFeedbackloop(const std::string& inFileName);
};

#endif //UNTITLED3_SOLUTION_HPP

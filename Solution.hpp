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
#include <list>
#include <thread>
#include <mutex>
#include "helpers/IntcodeComputer.hpp"
#include "helpers/IntcodeComputerASCII.hpp"

class Solution
{
    typedef __int64 Quan;

    struct Elem
    {
        std::string name;
        Quan quantity;
        bool operator<(const Elem& b) const { return name<b.name; }
    };
    std::unordered_map<std::string, std::pair<std::vector<Elem>, Quan>> reactions;

    std::unordered_map<std::string, Quan> inDegree, starting;

    std::map<std::string, Quan> needed;

    Quan oreneeded(Elem elem)
    {
        needed.clear();
        inDegree = starting;
        Quan res = 0;
        needed[elem.name] = elem.quantity;
        while (!needed.empty()) {
            for (auto neededElem = needed.begin(); neededElem!=needed.end(); ++neededElem)
            {
//                for (auto& [k, v]: needed) std::cout<<"["<<v<<","<<k<<"] "; std::cout<<" ="<<res<<"\n";
                Elem curr = {neededElem->first, neededElem->second};

                if (curr.name == "ORE") {
                    res += curr.quantity;
                    needed.erase(neededElem);
                    if (needed.empty())
                        return res;
                    neededElem = needed.begin();
                }
                else if (inDegree[curr.name] == 0) {
                    //decompose
                    needed.erase(neededElem);
//                    std::cout << "decomposing " << curr.quantity << " of " << curr.name << ": ";
                    auto[ingredients, qty] = reactions[curr.name];
                    for (auto& ingredient: ingredients) {
                        inDegree[ingredient.name]--;

                        Quan times = std::ceil((long double)(curr.quantity) / qty);
//                        std::cout << times <<"*"<< ingredient.quantity << "*" << ingredient.name << " ";
                        if (needed.count(ingredient.name))
                            needed[ingredient.name] += times * ingredient.quantity;
                        else
                            needed.insert({ingredient.name, times * ingredient.quantity});
                    }
                    neededElem = needed.begin();
//                    std::cout << "\n";
                }
            }
        }
        return res;
    }

public:

    auto run(const std::string& inFileName)
    {
        std::ifstream inFile(inFileName);
        for (std::vector<Elem> left; inFile.good(); )
        {
            Elem curr;
            inFile>>curr.quantity>>curr.name;
            if (curr.name.back() == ',')
            {
                curr.name.pop_back();
                left.push_back(curr);
            }
            else
            {
                left.push_back(curr);
                std::string arrow;
                inFile>>arrow>>curr.quantity>>curr.name;
                reactions[curr.name] = std::make_pair(left, curr.quantity);

                for (auto& x: left)
                    inDegree[x.name]++;
                left.clear();
            }
        }
        starting = inDegree;

        int qu;
        for (qu = 2267480; ; ++qu) {
            Quan rerere = oreneeded({"FUEL", qu});
            std::cout<<qu<<" ";
            std::cout<<rerere;
            std::cout<<"\n";
            if (rerere > 1'000'000'000'000) {
                std::cout << "YEAH: qu=" << qu << "\n";
                break;
            }
        }
        return qu;
    }

public:
    long long runComputer(const std::string& inFileName);
    long long runAmplifier(const std::string& inFileName);
    long long runAmplifierFeedbackloop(const std::string& inFileName);
};

#endif //UNTITLED3_SOLUTION_HPP

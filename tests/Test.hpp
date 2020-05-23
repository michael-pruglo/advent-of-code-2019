//
// Created by Michael on 05/22/20.
//

#ifndef UNTITLED3_TEST_HPP
#define UNTITLED3_TEST_HPP

#include <iostream>
#include <vector>
#include "../Solution.hpp"

class Test
{
public:
    template<typename T>
    static inline bool test(T expected, T real)
    {
        return expected==real;
    }

    template<typename T>
    static void run(std::vector<std::pair<std::string, T>> testcases)
    {
        int i = 0, bad = 0;
        for (const auto& [fileName, expected] : testcases)
        {
            Solution sol;
            auto result = sol.run(fileName);
            std::cout<<"test #"<<i++<<" ";
            if (test(expected, result))
                std::cout<<" passed\n";
            else
            {
                std::cout<<" WA: expected ["<<expected<<"] got ["<<result<<"]\n";
                ++bad;
            }
        }
        std::cout<<"==\n";
        std::cout<<testcases.size()<<" tests done. "<<testcases.size()-bad<<" ok, "<<bad<<" bad\n";

    }
};


#endif //UNTITLED3_TEST_HPP

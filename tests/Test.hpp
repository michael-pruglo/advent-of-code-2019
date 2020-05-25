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
};


#endif //UNTITLED3_TEST_HPP

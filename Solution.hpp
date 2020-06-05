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

public:

    auto run(const std::string& inFileName)
    {
        IntcodeComputerASCII ic = readIntcodeFile(inFileName);

        std::string command =
                "north\n"
                "west\n"
                //"take mug\n"
                "west\n"
                "take easter egg\n"
                "east\n"
                "east\n"
                "south\n"
                "south\n"
                "take asterisk\n"
                "south\n"
                "west\n"
                "north\n"
                "take jam\n"
                "south\n"
                "east\n"
                "north\n"
                "east\n"
                "take klein bottle\n"
                "south\n"
                "west\n"
                "take tambourine\n"
                "west\n"
                "take cake\n"
                "east\n"
                "south\n"
                "east\n"
                "take polygon\n"
                "north\n"
                "inv\n"
                ;

        const std::vector<std::string> objects = {
                "polygon",
                "easter egg",
                "tambourine",
                "asterisk",
                "jam",
                "klein bottle",
                "cake"
        };
        for (unsigned i = 1; i < 1u<<objects.size(); ++i)
        {
            for (unsigned j = 0; 1u<<j <= i; ++j)
                if (!((1u<<j)&i))
                    command += "drop " + objects[j] + "\n";
            command += "inv\neast\n";
            ic.run(command);
            std::cerr<<i<<"\n";
            std::cout<<ic.grabOutput();
            //std::cin.get();
            command.clear();
            for (unsigned j = 0; 1u<<j <= i; ++j)
                if (!((1u<<j)&i))
                    command += "take " + objects[j] + "\n";

        }

        while (1)
        {
            ic.run(command);
            std::cout<<ic.grabOutput()<<">";
            getline(std::cin, command);
            command += '\n';
        }

        return 0;
    }

public:
    long long runComputer(const std::string& inFileName);
    long long runAmplifier(const std::string& inFileName);
    long long runAmplifierFeedbackloop(const std::string& inFileName);
};

#endif //UNTITLED3_SOLUTION_HPP

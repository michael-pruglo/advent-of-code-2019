//
// Created by Michael on 05/22/20.
//

#ifndef UNTITLED3_INTCODECOMPUTER_HPP
#define UNTITLED3_INTCODECOMPUTER_HPP


#include <vector>
#include <iostream>

class IntcodeComputer
{
    std::vector<int>    memo,
                        startingState;
    const int           INPUT = 5;

public:
                        IntcodeComputer() = default;
    explicit            IntcodeComputer(std::istream& is);

private:
    void                readf(std::istream& is);

public:
    void                show(int highlight = -1, std::ostream& os = std::cout) const;
    void                show(int startAdress, int endAdress, int highlight = -1, std::ostream& os = std::cout) const;
    inline int          get(int address) const
    {
        return memo[address];
    }
    inline int          result() const
    {
        return get(0);
    }
    inline int          size() const
    {
        return memo.size();
    }

    void                reset();
    void                init(int noun, int verb);
    int                 run(int instructionPointer = 0)
    {
        for (int ip = 0; ip < memo.size(); )
        {
            int opcode = memo[ip] % 100;
            int paramModes = memo[ip] / 100;
            std::vector<int> parameters;

            switch (opcode) {
                case 99:
                    return result();

                case 1: //add two parameters and write to address
                case 2: //mul two parameters and write to address
                    parameters.push_back(paramModes%10 ? memo[ip+1] : memo[memo[ip+1]]);
                    paramModes /= 10;
                    parameters.push_back(paramModes%10 ? memo[ip+2] : memo[memo[ip+2]]);
                    paramModes /= 10;
                    parameters.push_back(memo[ip+3]);

                    memo[parameters[2]] = opcode==1?
                            parameters[0] + parameters[1] :
                            parameters[0] * parameters[1];
                    ip += parameters.size()+1;
                    break;

                case 3: //write INPUT to address
                    parameters.push_back(memo[ip+1]);

                    memo[parameters[0]] = INPUT;
                    ip += parameters.size()+1;
                    break;

                case 4: //output the value at the address
                    parameters.push_back(memo[ip+1]);

                    std::cout << "@" << ip << " output: " << memo[parameters[0]] << "\n";
                    ip += parameters.size()+1;
                    break;

                case 5: //jump-if-true
                case 6: //jump-if-false
                    parameters.push_back(paramModes%10 ? memo[ip+1] : memo[memo[ip+1]]);
                    paramModes /= 10;
                    parameters.push_back(paramModes%10 ? memo[ip+2] : memo[memo[ip+2]]);
                    paramModes /= 10;

                    if (parameters[0] && opcode==5
                     ||!parameters[0] && opcode==6)
                        ip = parameters[1];
                    else
                        ip += parameters.size()+1;
                    break;

                case 7: //less than - evaluate and write to address
                case 8: //equals - evaluate and write to address
                    parameters.push_back(paramModes%10 ? memo[ip+1] : memo[memo[ip+1]]);
                    paramModes /= 10;
                    parameters.push_back(paramModes%10 ? memo[ip+2] : memo[memo[ip+2]]);
                    paramModes /= 10;
                    parameters.push_back(memo[ip+3]);

                    memo[parameters[2]] = opcode==7 ?
                            parameters[0] < parameters[1] :
                            parameters[0] == parameters[1];
                    ip += parameters.size()+1;
                    break;
            }
            show(29, 36, ip);

        }

        return result();
    }
};


#endif //UNTITLED3_INTCODECOMPUTER_HPP

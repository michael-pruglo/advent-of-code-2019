//
// Created by Michael on 05/26/20.
//

#include "ArcadeCabinet.hpp"

int ArcadeCabinet::run()
{
    int ballX = -1, paddleX = -1;
    std::queue<long long> input;
    while (!ic.wasTerminated())
    {
        if (ic.currentStatusString()=="AWAITING_INPUT")
        {
            if (paddleX < ballX) joystick = 1;
            if (paddleX > ballX) joystick = -1;
            if (paddleX == ballX) joystick = 0;
            input = std::queue<long long> ({joystick});
            //std::cout<<"chose action: "<<joystick<<"\n";
            //std::cin.get();

        }
        //std::cout<<"ij: "<<i<<", "<<j<<" -> ";
        ic.run(input);
        auto output = ic.grabOutput();
        for (int i = 0; i < output.size(); i+=3)
        {
            auto x = output[i], y = output[i+1], id = output[i+2];
            if (x==-1 && y==0)
                score = id;
            else
                screen[y][x] = id;
            if (id==3) paddleX = x;
            if (id==4) ballX = x;
            //std::cout<<"] "<<x<<" "<<y<<" "<<id<<" \n";
        }
        //std::cout<<" "<<i<<", "<<j<<"\n";

        std::cout<<"score = "<<score<<"\n";
        //show();
    }
    int tilesNo = 0;
    for (auto& row : screen)
        for (auto& pix : row)
            if (pix == 2)
                ++tilesNo;

    return tilesNo;
}

void ArcadeCabinet::show()
{
    for (const auto& row : screen)
    {
        for (const auto& pix : row) {
            switch (pix) {
                case UNDEF: std::cout<<'@'; break;
                case 0: std::cout<<' '; break;
                case 1: std::cout<<'#'; break;
                case 2: std::cout<<'+'; break;
                case 3: std::cout<<'-'; break;
                case 4: std::cout<<'*'; break;
            }
        }
        std::cout<<"\n";
    }
    std::cout<<"SCORE: "<<score<<"\n";
}

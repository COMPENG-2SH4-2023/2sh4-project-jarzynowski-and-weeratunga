#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


class GameMechs
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    private:
    
        char input;
        bool exitFlag;
        bool loseFlag;
        int boardSizeX;
        int boardSizeY;
        
        // 3:2 
        int score;
        objPos foodPos; // This is the position of the food

        


    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        
        bool getExitFlagStatus();
        void setExitTrue();
        bool getLoseFlagStatus();
        void setLoseFlag();

        int getScore();
        void incrementScore();

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX();
        int getBoardSizeY();

        void generateFood(const objPos& blockOff);
        // 2B - Generate food function, straight from PPA3

        void getFoodPos(objPos& returnPos);
        // 2B - Get food position function

        bool getLoseFlag() const;
};

#endif
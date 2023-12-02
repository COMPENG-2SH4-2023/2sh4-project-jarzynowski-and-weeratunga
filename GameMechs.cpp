#include "GameMechs.h"

GameMechs::GameMechs()
{

}

GameMechs::GameMechs(int boardX, int boardY)
{
    
}

// do you need a destructor?
// yes scotty chen

bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

char GameMechs::getInput()
{
    return input; // Return the input
}

int GameMechs::getBoardSizeX()
{
    return 40;
}

int GameMechs::getBoardSizeY()
{
    return 10;
}


void GameMechs::setExitTrue()
{

}

void GameMechs::setInput(char this_input)
{
    input = this_input; // Set input to the input passed in

    if (input == '`')
    {
        exitFlag = true;
    }

}

void GameMechs::clearInput()
{
    input = ' '; // Clear the input

}

int GameMechs::getScore()
{
    return 69420; // For now.
}



#include "GameMechs.h"

#include <cstdlib>
#include <ctime>


GameMechs::GameMechs() : score(0)
{

}

GameMechs::GameMechs(int boardX, int boardY) : score(0)
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
    exitFlag = true;
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

void GameMechs::incrementScore(){
    score++;
}



int GameMechs::getScore()
{
    return score; // For now.
}

void GameMechs::generateFood(const objPos& blockOff) {
    srand(time(NULL)); // Seed for random number generation

    // Assuming getBoardSizeX() and getBoardSizeY() return the size of the board
    int boardSizeX = getBoardSizeX();
    int boardSizeY = getBoardSizeY();

    int x, y;
    do {
        // Generate random position within the board boundaries
        x = rand() % (boardSizeX - 2) + 1; // -2 and +1 to adjust for board edges
        y = rand() % (boardSizeY - 2) + 1;

        // Repeat if the generated position is the same as the player's position
    } while (x == blockOff.x && y == blockOff.y);

    // Set the food position
    foodPos.x = x;
    foodPos.y = y;
    //foodPos.icon = '*'; // Assuming '*' is the symbol for food
    // I AM CHANGING THIS SO ITS OOP BULLSHIT SINCE I AM JUST PASSING
    // THE SYMBOL VIA DRAW SCREEN DUE TO LAZINESS!!!!!!!!!!!


}

void GameMechs::getFoodPos(objPos& returnPos) {
    returnPos = foodPos; // Assign the food position to returnPos
}


#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
     playerPosList = new objPosArrayList();


     // Add the first element at starting position
    objPos startingPos(20, 5, '*'); // Creating an objPos using the constructor (int xPos, int yPos, char sym)
    objPos secondPos(20, 6, '*');
    objPos thirdPos(20, 7, '*');
    playerPosList->insertHead(startingPos); // Assuming insertHead inserts an objPos at the head of the list
    playerPosList->insertTail(secondPos);
    playerPosList->insertTail(thirdPos);



    

}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList; // Free the memory for playerPosList
}

objPosArrayList* Player::getPlayerPos() {
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic   
    char input = mainGameMechsRef->getInput();

    switch(input)
    {
        case 'w':
                if (myDir != UP && myDir != DOWN)
                {
                    myDir = UP;
                }
                break;
                
            case 'a':
                if (myDir != LEFT && myDir != RIGHT)
                {
                    myDir = LEFT;
                }
                break;

            case 's':
                if (myDir != UP && myDir != DOWN)
                {
                    myDir = DOWN;
                }
                break;

            case 'd':
                if (myDir != LEFT && myDir != RIGHT)
                {
                    myDir = RIGHT;
                }
                break;

            default:
                break;
    }

}

void Player::movePlayer()
{
    //New in iteration 3
    objPos currentPos;
    playerPosList->getHeadElement(currentPos); // Get the current position of the player
    // PPA3 Finite State Machine logic
    switch(myDir)
    {
        case UP:
        currentPos.y--;
        if(currentPos.y <= 0)
        {
            currentPos.y = mainGameMechsRef->getBoardSizeY() - 2;
        }
        break;

        case DOWN:
        {
            currentPos.y++;
            if(currentPos.y >= mainGameMechsRef->getBoardSizeY())
            {
                currentPos.y = 1;
            }
            break;
        }

        case LEFT:
        {
            currentPos.x--;
            if(currentPos.x <= 0)
            {
                currentPos.x = mainGameMechsRef->getBoardSizeX() -2;
            }
            break;
        }

        case RIGHT:
        {
            currentPos.x++;
            if(currentPos.x >= mainGameMechsRef->getBoardSizeX())
            {
                currentPos.x = 1;
            }
            break;
        }
        

    }

    playerPosList->insertHead(currentPos); // Insert the updated position at the head of the list
    playerPosList->removeTail(); // Remove the last element from the list
}


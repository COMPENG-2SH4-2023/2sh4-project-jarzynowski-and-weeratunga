#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
     playerPosList = new objPosArrayList();


     // Add the first element at starting position
    objPos startingPos(20, 5, '*'); // Creating an objPos using the constructor (int xPos, int yPos, char sym)

    playerPosList->insertHead(startingPos); // Assuming insertHead inserts an objPos at the head of the list




    

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
    objPos newHead;
    playerPosList->getHeadElement(newHead); // Get the current head position of the player
    // PPA3 Finite State Machine logic
    switch(myDir)
    {
        case UP:
            newHead.y--;
            break;
        case DOWN:
            newHead.y++;
            break;
        case LEFT:
            newHead.x--;
            break;
        case RIGHT:
            newHead.x++;
            break;
        default:
            // Handle no movement case or invalid direction
            return;
    }
    
    // Wrap around logic for the snake
    if(newHead.y <= 0) newHead.y = mainGameMechsRef->getBoardSizeY() - 2;
    if(newHead.y >= mainGameMechsRef->getBoardSizeY()) newHead.y = 1;
    if(newHead.x <= 0) newHead.x = mainGameMechsRef->getBoardSizeX() - 2;
    if(newHead.x >= mainGameMechsRef->getBoardSizeX()) newHead.x = 1;
    
    // Check for food consumption
    objPos foodPos;
    mainGameMechsRef->getFoodPos(foodPos); // Get the current food position
    if(newHead.x == foodPos.x && newHead.y == foodPos.y)
    {
        // Increase score
        mainGameMechsRef->incrementScore();
        
        // Grow the snake - by not removing the tail when food is consumed
        mainGameMechsRef->generateFood(newHead); // Generate new food, which also should not overlap with the snake
    }
    else
    {
        playerPosList->removeTail(); // Remove the last element from the list only if food is not consumed
    }

    playerPosList->insertHead(newHead); // Insert the updated position at the head of the list
}



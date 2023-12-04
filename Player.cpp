#include "Player.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    playerPosList = new objPosArrayList();

    // Define the "head" of the snake, starting in the middle of the screen
    objPos startingPos(20, 5, '*'); // Creating an objPos using the constructor (int xPos, int yPos, char sym)
    playerPosList->insertHead(startingPos); // Assuming insertHead inserts an objPos at the head of the list


}

Player::~Player()
{
    delete playerPosList; // Free the memory for playerPosList
}

objPosArrayList* Player::getPlayerPos() {
    return playerPosList;
}

// Boolean to check if the new head position is the same as any of the other segments of the snake
bool Player::checkSelfCollision(const objPos& newHeadPosition) {
    
    // Start the loop at 1 to skip checking the head against itself
    for (int i = 1; i < playerPosList->getSize(); ++i) {
        
        objPos currentSegment;
        playerPosList->getElement(currentSegment, i);
       
        if (newHeadPosition.x == currentSegment.x && newHeadPosition.y == currentSegment.y) {
            return true; // Collision detected
        }
    }
    return false; // No collision detected
}

// FSM logic to update the player direction
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

// FSM logic to move the player
void Player::movePlayer()
{
    objPos newHead;
    playerPosList->getHeadElement(newHead); // Get the current head position of the player
    
    // PPA-3 FSM logic
    switch(myDir)
    {
        case UP: newHead.y--; break;
        case DOWN: newHead.y++; break;
        case LEFT: newHead.x--; break;
        case RIGHT: newHead.x++; break;
        default: return; // No movement case or invalid direction

    }
    
    // Wrap around logic for the snake
    if(newHead.y <= 0) newHead.y = mainGameMechsRef->getBoardSizeY() - 2;
    if(newHead.y >= mainGameMechsRef->getBoardSizeY()) newHead.y = 1;
    if(newHead.x <= 0) newHead.x = mainGameMechsRef->getBoardSizeX() - 2;
    if(newHead.x >= mainGameMechsRef->getBoardSizeX()) newHead.x = 1;
    
    // Collision Check
    if (checkSelfCollision(newHead))
    {
        mainGameMechsRef->setExitTrue();
        mainGameMechsRef->setLoseFlag();
        return;
    }

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



#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.setObjPos(5,5,'*');
}


Player::~Player()
{
    // delete any heap members here
    //nothing needed for now since "new" not used to allocate anything yet
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
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
                    myDir = LEFT;
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
    // PPA3 Finite State Machine logic
    switch(myDir)
    {
        case UP:
        playerPos.y--;
        if(playerPos.y <= 0)
        {
            playerPos.y = mainGameMechsRef->getBoardSizeY() - 2;
        }
        break;

        case DOWN:
        {
            playerPos.y++;
            if(playerPos.y >= mainGameMechsRef->getBoardSizeY())
            {
                playerPos.y = 1;
            }
            break;
        }

        case LEFT:
        {
            playerPos.x--;
            if(playerPos.x <= 0)
            {
                playerPos.x = mainGameMechsRef->getBoardSizeX() -2;
            }
            break;
        }

        case RIGHT:
        {
            playerPos.x++;
            if(playerPos.x >= mainGameMechsRef->getBoardSizeX())
            {
                playerPos.x = 1;
            }
            break;
        }

    }
}


#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"


using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM;
Player* myPlayer;

bool exitFlag;


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(!myGM->getExitFlagStatus())  
    {
        DrawScreen(); // Switched the order of DrawScreen and GetInput, since wouldnt print without and input lol
        GetInput();
        RunLogic();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    myGM = new GameMechs(26, 13);
    myPlayer = new Player(myGM);
    objPos playerStartPos(26,13,'*');
   // objPos player1(26,14,'*');
   // objPos player2(26,15,'*');

    objPosArrayList* playerPosList = myPlayer->getPlayerPos();
    //playerPosList->insertHead(playerStartPos);
    //playerPosList->insertTail(player1);
    //playerPosList->insertTail(player2);

    

    myGM->generateFood(playerStartPos);

    //Scott didn't have this here so not sure if we should keep or not
    exitFlag = false;
}

void GetInput(void)
{
    if (MacUILib_hasChar()){
        char input = MacUILib_getChar();
        myGM->setInput(input);
    }
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

    //so that input does not need to be repeatedly processed
    myGM->clearInput();
    // pointer is crazy!!!!!!!!!!!
}

void DrawScreen(void)
{
    MacUILib_clearScreen();  

    // Retrieve the player position list
    objPosArrayList* playerPosList = myPlayer->getPlayerPos();

    objPos foodPos;
    myGM->getFoodPos(foodPos);

    for(int i = 0; i < myGM->getBoardSizeY(); i++)
    {
        for(int j = 0; j < myGM->getBoardSizeX(); j++)
        {
            // Draw the borders
            if(i == 0 || i == myGM->getBoardSizeY() - 1 || j == 0 || j == myGM->getBoardSizeX() -1)
            {
                printf("%c", '#');
            }
            else
            {
                //this just checks if smthn was drawn or not
                bool drawn = false;

                // Check if player is at this position in the list
                for(int k = 0; k < playerPosList->getSize(); k++)
                {
                    objPos currentPos;
                    playerPosList->getElement(currentPos, k);

                    if (currentPos.x == j && currentPos.y == i)
                    {
                        //draws the player's symbol
                        //I'm trying to draw more than one at a time now
                        printf("%c", currentPos.symbol); 
                        drawn = true;
                        break;
                    }
                }
          
                // If no player is at this position, check for food
                if (!drawn && j == foodPos.x && i == foodPos.y)
                {
                    printf("*"); // Draw the food (assuming '*' represents food)
                }
                else if (!drawn)
                {
                    printf("%c", ' '); // Draw an empty space
                }
            }
        }
        printf("\n");
    }

    
    // Bottom Printing Sequence
    MacUILib_printf("--'COMPENG-2SH4 Snake'------------------\n");
    MacUILib_printf("----------------------------------------\n");
    MacUILib_printf("-- Current Score: %d \n", myGM->getScore());

    //This is how we're gonna print the head element when moving
    // Get the player position list
    //Get the head element
    objPos headPos;
    playerPosList->getHeadElement(headPos);

    MacUILib_printf("-- Current Coordinates (Head): <%d, %d> \n", headPos.x, headPos.y);
    MacUILib_printf("----------------------------------------\n");
    MacUILib_printf("-- Controls: ---------------------------\n");
    MacUILib_printf("-- W: Move Up, A: Move Left\n"); 
    MacUILib_printf("-- S: Move Down, D: Move Right\n");
    printf("----------------------------------------\n");
    MacUILib_printf("-- By: M. Jarzynowski & S. Weeratunga --\n");
    printf("----------------------------------------\n");

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();

    //deallocate heap instances
    delete myGM;
    delete myPlayer;
}

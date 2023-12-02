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

    objPos tempPos; 
    //get the player position
    myPlayer->getPlayerPos(tempPos);   

    for(int i = 0; i < myGM->getBoardSizeY(); i++)
    {
        for(int j = 0; j < myGM->getBoardSizeX(); j++)
        {
            //draw the borders
            if(i == 0 || i == myGM->getBoardSizeY() - 1 || j == 0 || j == myGM->getBoardSizeX() -1)
            {
                printf("%c", '#');
            }
            else if (j == tempPos.x && i == tempPos.y)
            {
                printf("%c", tempPos.symbol);
            }
            else
            {
                printf("%c", ' ');
            }
            
        }

        printf("\n");
    }
    
    // Bottom Printing Sequence
    MacUILib_printf("--'COMPENG-2SH4 Snake'------------------\n");
    MacUILib_printf("----------------------------------------\n");
    MacUILib_printf("-- Current Score: %d \n", myGM->getScore());
    MacUILib_printf("-- Current Coordinates: <%d, %d> \n", tempPos.x, tempPos.y);
    MacUILib_printf("----------------------------------------\n");
    MacUILib_printf("-- Controls: ---------------------------\n");
    MacUILib_printf("-- W: Move Up, A: Move Left\n"); 
    MacUILib_printf("-- S: Move Down, D: Move Right\n");
    printf("----------------------------------------\n");
    MacUILib_printf("-- By: M. Jarzynowski & S. Weeratunga --\n");
    printf("----------------------------------------\n");



    
    //  printf("--'Find-the String'---------------------\n");
    // printf("----------------------------------------\n");
    // printf("Mystery String: %s\n", mysteryString);
    // printf("Move Count: %d\n", moveCount);

    // // Added from PPA2

    // // Coordinates, game speed, and controls printing under the game board
    // printf("----------------------------------------\n");
    // printf("Current Coordinates, (%d, %d)\n", player.x, player.y); // Print the current player coordinates
    // printf("Current Speed Level: %d" " (1-5)\n", gameSpeedIndex + 1); 
    // printf("----------------------------------------\n");
    // printf("Controls: \n");
    // printf("W: Move Up, A: Move Left, S: Move Down, D: Move Right\n");
    // printf("Q: Increase Speed, E: Decrease Speed, SPACE: Exit\n");
    // printf("----------------------------------------\n");
    
    
    // //getScore is an error for now but won't be once implemented
    
    
    
    
    // MacUILib_printf("Score: %d, Player Pos: <%d, %d>\n", myGM->getScore(), tempPos.x, tempPos.y);
    // // Added from PPA3

   
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

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

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
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
    myGM->getInput();
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

    //so that input does not need to be repeatedly processed
    myGM->clearInput();
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
    //getScore is an error for now but won't be once implemented
    MacUILib_printf("Score: %d, Player Pos: <%d, %d>\n", myGM->getScore(), tempPos.x, tempPos.y);

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

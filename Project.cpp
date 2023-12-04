// Basic Header Files, both from the MacUILib and C++ Standard Library
#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000 // 0.1s delay

// Consider these as references to the Main Game Mechanisms and the Player
GameMechs* myGM;
Player* myPlayer;

bool exitFlag = false; // exitFlag to end game

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{
    Initialize();
    // While the exitFlag is false, keep running the game
    while(!myGM->getExitFlagStatus())  
    {
        DrawScreen();
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
    
    myGM = new GameMechs(40, 10); // Board, defined as 40 x 10
    myPlayer = new Player(myGM); // Define a new player with a reference to the main game mechanisms
    objPos playerStartPos(20,5,'*'); // Starting position of the player

    objPosArrayList* playerPosList = myPlayer->getPlayerPos();

    myGM->generateFood(playerStartPos); // Generate the food at a random position
}

void GetInput(void)
{
    // Check if there is input, if there is
    // set the input in the main game mechanisms
    if (MacUILib_hasChar()){
        char input = MacUILib_getChar();
        myGM->setInput(input);
    }
}

void RunLogic(void)
{
    // Compared to PPA-3, logic was defined within the Player class
    
    myPlayer->updatePlayerDir(); // Update the player direction
    myPlayer->movePlayer(); // Move the player

    myGM->clearInput(); // Clear the input
}

void DrawScreen(void)
{
    MacUILib_clearScreen();  

    objPosArrayList* playerPosList = myPlayer->getPlayerPos(); // Get the player position list

    objPos foodPos; // Get the food position
    myGM->getFoodPos(foodPos); // Bring it into game mechanics

    objPos headPos; // Get the head position
    playerPosList->getHeadElement(headPos); // Bring it into the player position list

    // For each row and column, defined by the board size...
    for(int i = 0; i < myGM->getBoardSizeY(); i++)
    {
        for(int j = 0; j < myGM->getBoardSizeX(); j++)
        {
            // Draw the board edges as "#"'s
            if(i == 0 || i == myGM->getBoardSizeY() - 1 || j == 0 || j == myGM->getBoardSizeX() -1)
            {
                printf("%c", '#');
            }
            
            // Else, consider the player and food...
            else
            {
                bool drawn = false; // Flag to check if something has been drawn at this position

                // For each element in the player position list...
                for(int k = 0; k < playerPosList->getSize(); k++)
                {
                    objPos currentPos;
                    playerPosList->getElement(currentPos, k);

                    // If the player is at this position, draw the player...
                    if (currentPos.x == j && currentPos.y == i)
                    {
                        printf("%c", currentPos.symbol); // Draw the player, referencing the symbol at this position
                        drawn = true;
                        break;
                    }
                }
          
                // If theres no player or border detected, consider the food...
                if (!drawn && j == foodPos.x && i == foodPos.y)
                {
                    printf("*"); // Draw the food (assuming '*' represents food)
                }
                // If theres nothing...
                else if (!drawn)
                {
                    printf("%c", ' '); // Draw an empty space
                }
            }
        }
        printf("\n");
    }

    // Bottom "Status Bar"
    MacUILib_printf("--'Simply Snake' (Classic Edition) -----\n"); 
    MacUILib_printf("----------------------------------------\n");
    MacUILib_printf("-- Current Score: %d \n", myGM->getScore());
    MacUILib_printf("-- Head Coordinates: <%d, %d> \n", headPos.x, headPos.y);
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
    // Game Over Messages
    MacUILib_clearScreen();    
    
    // If the player crashes into themselves, and doesnt quit, hence true and false...
    if(myGM->getExitFlagStatus() == 1 && myGM->getLoseFlag() == true){
        
        cout << "You crashed into yourself, you're done :(" << endl;
        cout << "Consider 'getting good' and trying again." << endl;
        cout << "Your final score was: " << myGM->getScore() << endl;
    
    // If the player crashes into the wall, and doesnt quit, hence true and false...
    }else if (myGM->getExitFlagStatus() ==1 && myGM->getLoseFlag() == false){
        cout << "You quit the game!" << endl;
        cout << "Too hard?" << endl;
        cout << "Your final score was: " << myGM->getScore() << endl;
    }
    MacUILib_uninit();

    // Deallocate Heap Memory
    delete myGM;
    delete myPlayer;
    // No leak. No problem.
}

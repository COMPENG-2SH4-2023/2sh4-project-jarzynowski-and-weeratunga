#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef);
        ~Player();
        
        objPosArrayList* getPlayerPos(); 
        void updatePlayerDir();
        void movePlayer();

        bool checkFoodConsumption(); // This function checks if the player has consumed food
        void increasePlayerLength(); // This function increases the length of the player

        bool checkSelfCollision(const objPos& newHeadPosition); // This function checks if the player has collided with itself

    private:
            
        enum Dir myDir;
        
        objPosArrayList* playerPosList; // This is the list of positions occupied by the player
        GameMechs* mainGameMechsRef; // Need a reference to the Main Game Mechanisms
};

#endif
#ifndef GAME_H
#define GAME_H

#include "types.h"

// Game Initialization and Start
void startingMessage(void);
void startGame(void);

// Turn Order
int rollDice(void);
void setPlayOrder(void);

// Game Control
void playGame(void);
int countSolventPlayers(void);
void endGame(void);
void displayRoundSummary(int roundNumber);

#endif
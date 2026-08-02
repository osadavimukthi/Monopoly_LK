#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "types.h"
#include "players.h"
#include "game.h"
#include "board.h"

int rollDice()
{
    return rand() % 6 + 1;
}

void startGame()
{

    board();
    playerStructure();
/*
printf("MONOPOLY-LK Simulation\n\n");

printf("Player 1: Aggresive Investor\n");
printf("Player 2: Conservative Banker\n");
printf("Player 3: Risk Taker\n");
printf("Player 4: Opportunistic Trader\n\n");

printf("Each player Begins with LKR 30 000 \n\n");

int playerRolls[4];
playerRolls[0] = rollDice()+rollDice();
playerRolls[1] = rollDice()+rollDice();
playerRolls[2] = rollDice()+rollDice();
playerRolls[3] = rollDice()+rollDice();



printf("Aggresive investor rolls %d \n", playerRolls[0]);
printf("Conservative Banker rolls %d \n", playerRolls[1]);
printf("Risk Taker rolls %d \n", playerRolls[2]);
printf("Opportunistic Trader rolls %d \n", playerRolls[3]);*/
}



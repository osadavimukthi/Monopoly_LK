#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int rollDice()
{
    return rand() % 6 + 1;
}

void startGame()
{

printf("MONOPOLY-LK Simulation\n\n");

printf("Player 1: Aggresive Investor\n");
printf("Player 2: Conservative Banker\n");
printf("Player 3: Risk Taker\n");
printf("Player 4: Opportunistic Trader\n\n");

printf("Each player Begins with LKR 30 000 \n\n");

printf("Aggresive investor rolls %d \n", rollDice()+rollDice());
printf("Conservative Banker rolls %d \n", rollDice()+rollDice());
printf("Risk Taker rolls %d \n", rollDice()+rollDice());
printf("Opportunistic Trader rolls %d \n", rollDice()+rollDice());
}



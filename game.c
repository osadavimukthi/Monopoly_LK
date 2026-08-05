#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "types.h"
#include "players.h"
#include "board.h"
#include "buyandrent.h"

void startingMasage()
{
    printf("MONOPOLY-LK Simulation\n\n");
    
    printf("Player 1: Aggresive Investor\n");
    printf("Player 2: Conservative Banker\n");
    printf("Player 3: Risk Taker\n");
    printf("Player 4: Opportunistic Trader\n\n");

    printf("Each player Begins with LKR 30 000\n\n");
}   
//void defineBoard();
//void playerStructure();

int rollDice()
{
    return rand() % 6 + 1;
}
void setPlayOrder()
{
    srand(time(NULL));   // Seed the random number generator ONCE

    int playerRolls[4];

    playerRolls[0] = rollDice() + rollDice();
    playerRolls[1] = rollDice() + rollDice();
    playerRolls[2] = rollDice() + rollDice();
    playerRolls[3] = rollDice() + rollDice();

    printf("Aggresive Investor rolls %d\n", playerRolls[0]);
    printf("Conservative Banker rolls %d\n", playerRolls[1]);
    printf("Risk Taker rolls %d\n", playerRolls[2]);
    printf("Opportunistic Trader rolls %d\n", playerRolls[3]);
    
    int i=0;
    int j=1;
    
    while(i<4){
        j = i + 1;
        while(j<4){
            if(playerRolls[i]==playerRolls[j]){
                printf("%s and %s have the same roll\n", players[i].name, players[j].name);
            }
            j++;
        }
        i++;
    }

    //fake priority for now
    players[0].priority = 3;
    players[1].priority = 4;
    players[2].priority = 1;
    players[3].priority = 2;


    printf("\nTurn order:\n");

    int priority = 1;

while(priority <= 4)
{
    int k = 0;

    while(k < 4)
    {
        if(players[k].priority == priority)
        {
            printf("%s\n", players[k].name);
        }

        k++;
    }

    priority++;
}
   

}

void playGame()
{
    int gameRound = 0;
    int bankruptedPlayerCount = 0;

    printf("\n*******************************\n");
    printf("Game Round %d Starts\n", gameRound + 1);
    printf("*******************************\n\n");

    while(gameRound < 5)
    {
        /* Every player gets exactly one turn */
        for(int ongoingPlayer = 1; ongoingPlayer <= 4; ongoingPlayer++)
        {
            for(int k = 0; k < 4; k++)
            {
                if(!players[k].isBankrupt)
                {
                    if(players[k].priority == ongoingPlayer)
                    {
                        switch(players[k].priority)
                        {
                            case 1:
                                printf("%s goes first\n", players[k].name);
                                break;

                            case 2:
                                printf("%s goes second\n", players[k].name);
                                break;

                            case 3:
                                printf("%s goes third\n", players[k].name);
                                break;

                            case 4:
                                printf("%s goes fourth\n", players[k].name);
                                break;
                        }

                        /* Roll Dice */
                        players[k].lastRoll1 = rollDice();
                        players[k].lastRoll2 = rollDice();

                        int diceTotal = players[k].lastRoll1 + players[k].lastRoll2;

                        printf("%s rolled %d\n",
                            players[k].name,
                            diceTotal);

                        /* One turn completed */
                        players[k].playerTurn++;

                        players[k].oldPosition = players[k].currentPosition;
                        players[k].currentPosition += diceTotal;

                        /* Passed GO */
                        if(players[k].currentPosition >= 40)
                        {
                            players[k].currentPosition -= 40;

                            players[k].money += 2000;

                            players[k].playerRound++;

                            printf("%s passed GO and collects LKR 2000\n",
                                players[k].name);
                        }

                        printf("%s moves from %d to %d\n",
                            players[k].name,
                            players[k].oldPosition,
                            players[k].currentPosition);

                        printf("Player Turn  : %d\n", players[k].playerTurn);
                        printf("Player Round : %d\n\n", players[k].playerRound);

                        propertyBuyRent(players[k].currentPosition, k);
                        railwayBuyRent(players[k].currentPosition, k);
                        utilityBuyRent(players[k].currentPosition, k);
                        payTax(players[k].currentPosition, k);

                        playerBankrupt(k, bankruptedPlayerCount);
                    }
                }
            }
        }

        /* Check whether every non-bankrupt player has completed this game round */

        int completed = 1;

        for(int i = 0; i < 4; i++)
        {
            if(players[i].isBankrupt)
            {
                continue;
            }

            if(players[i].playerRound <= gameRound)
            {
                completed = 0;
                break;
            }
        }

        if(completed)
        {
            gameRound++;

            printf("=========================================\n");
            printf("Game Round %d Completed\n", gameRound);
            printf("=========================================\n\n");

            if(gameRound < 5)
            {
                printf("\n*******************************\n");
                printf("Game Round %d Starts\n", gameRound + 1);
                printf("*******************************\n\n");
            }
        }
    }

    printf("\n========== GAME OVER ==========\n");
}



void startGame(){
    startingMasage();
    setPlayOrder();
    playGame();


}

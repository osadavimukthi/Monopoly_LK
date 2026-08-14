#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "types.h"
#include "players.h"
#include "board.h"
#include "buyandrent.h"
#include "buildings.h"
#include "inflation.h"
#include "events.h"
#include "finance.h"
#include "auctions.h"
#define FULLROUNDS 100



void startingMasage()
{
    printf("MONOPOLY-LK Simulation\n\n");
    printf("Player 1: Aggresive Investor\n");
    printf("Player 2: Conservative Banker\n");
    printf("Player 3: Risk Taker\n");
    printf("Player 4: Opportunistic Trader\n\n");
    printf("Each player Begins with LKR 30 000\n\n");
}   

int rollDice()
{   
    return rand() % 6 + 1;
}

void setPlayOrder()
{
        srand(time(NULL));
    int playerRolls[4];
    int remaining[4] = {1, 1, 1, 1};
    int i;
    int j;
    int highestRoll;
    int highestCount;
    int priority = 1;

    /*
     * Roll two dice for every player
     */
    for(i = 0; i < 4; i++)
    {
        playerRolls[i] = rollDice() + rollDice();
    }

    printf("Aggresive Investor rolls %d\n", playerRolls[0]);
    printf("Conservative Banker rolls %d\n", playerRolls[1]);
    printf("Risk Taker rolls %d\n", playerRolls[2]);
    printf("Opportunistic Trader rolls %d\n", playerRolls[3]);

    /*
     * Continue until every player gets a priority
     */
    while(priority <= 4)
    {
        /*
         * Find the highest roll among players
         * who do not have a priority yet.
         */
        highestRoll = -1;

        for(i = 0; i < 4; i++)
        {
            if(remaining[i] == 1)
            {
                if(playerRolls[i] > highestRoll)
                {
                    highestRoll = playerRolls[i];
                }
            }
        }

        /*
         * Count how many remaining players
         * have the highest roll.
         */
        highestCount = 0;

        for(i = 0; i < 4; i++)
        {
            if(remaining[i] == 1 &&
               playerRolls[i] == highestRoll)
            {
                highestCount++;
            }
        }

        /*
         * If only one player has the highest roll,
         * that player gets the current priority.
         */
        if(highestCount == 1)
        {
            for(i = 0; i < 4; i++)
            {
                if(remaining[i] == 1 &&
                   playerRolls[i] == highestRoll)
                {
                    players[i].priority = priority;
                    remaining[i] = 0;

                    printf("%s gets priority %d\n",
                           players[i].name,
                           priority);

                    priority++;
                    break;
                }
            }
        }

        /*
         * If two or more players have the same
         * highest roll, only those players reroll.
         */
        else
        {
            printf("Tie for highest roll. Rerolling tied players.\n");

            for(i = 0; i < 4; i++)
            {
                if(remaining[i] == 1 &&
                   playerRolls[i] == highestRoll)
                {
                    playerRolls[i] = rollDice() + rollDice();

                    printf("%s rerolls %d\n",
                           players[i].name,
                           playerRolls[i]);
                }
            }
        }
    }

    /*
     * Display final turn order
     */
    printf("\nTurn order:\n");

    priority = 1;

    while(priority <= 4)
    {
        for(i = 0; i < 4; i++)
        {
            if(players[i].priority == priority)
            {
                printf("%s\n", players[i].name);
                break;
            }
        }

        priority++;
    }
}

void playGame()
{
    gameInfo.gameRound = 0;
    gameInfo.bankruptedPlayerCount = 0;

    printf("\n*******************************\n");
    printf("Game Round %d Starts\n", gameInfo.gameRound + 1);
    printf("*******************************\n\n");

    while(gameInfo.gameRound < FULLROUNDS)
    {
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

                        players[k].lastRoll1 = rollDice();
                        players[k].lastRoll2 = rollDice();

                        int diceTotal = players[k].lastRoll1 + players[k].lastRoll2;

                        printf("%s rolled %d\n",players[k].name,diceTotal);

                        players[k].playerTurn++;

                        if(players[k].isInJail)
                        {
                            outOfJail(players[k].currentPosition, k);
                        }

                        /* Player is not in Jail */
                        else
                        {
                            players[k].oldPosition =players[k].currentPosition;
                            players[k].currentPosition += diceTotal;

                            if(players[k].currentPosition >= 40)
                            {
                                players[k].currentPosition -= 40;

                                players[k].money += 2000;

                                players[k].playerRound++;

                                printf("%s passed GO and collects LKR 2000\n",players[k].name);
                            }

                            

                            printf("%s moves from %d to %d\n",players[k].name,players[k].oldPosition,players[k].currentPosition);

                            printf("Player Turn  : %d\n",players[k].playerTurn);

                            printf("Player Round : %d\n\n",players[k].playerRound);

                            /* Check Go To Jail */
                            gotoJail(players[k].currentPosition, k);

                            /* Only resolve landing if player was not sent to Jail */
                            if(!players[k].isInJail)
                            {
                               /* Only resolve landing if player was not sent to Jail */
                                {
                                    switch(board[players[k].currentPosition].type)
                                    {
                                        case Start:
                                            /* GO has already been handled above */
                                            printf("%s landed on GO.\n\n", players[k].name);
                                            break;

                                        case Property:
                                            propertyBuyRent(players[k].currentPosition, k);
                                            break;

                                        case Railway:
                                            railwayBuyRent(players[k].currentPosition, k);
                                            break;

                                        case Utility:
                                            utilityBuyRent(players[k].currentPosition, k);
                                            break;

                                        case Tax:
                                            payTax(players[k].currentPosition, k);
                                            break;

                                        case CommunityFund:
                                            communityDevelopmentFund(k);
                                            break;

                                        case Event:
                                            printf("%s landed on an Event square.\n\n",
                                                players[k].name);
                                            break;

                                        case Insurance:
                                            printf("%s landed on an Insurance square.\n\n",
                                                players[k].name);
                                            break;

                                        case Bank:
                                            printf("%s landed on Bank of Ceylon.\n\n",
                                                players[k].name);
                                            manageLoan(k);
                                            break;

                                        case Jail:
                                            printf("%s is visiting Jail.\n\n",
                                                players[k].name);
                                            break;

                                        case FreeParking:
                                            printf("%s landed on Free Parking.\n\n",
                                                players[k].name);
                                            break;

                                        case GoToJail:
                                            /* Already handled by gotoJail() above */
                                            break;
                                    }
                                }
                            }
                            renovateProperty(players[k].currentPosition, k);
                            for(int i = 0; i < 22; i++)
                            {
                                if(properties[i].squareNumber == players[k].currentPosition)
                                {
                                    checkMonopoly(k, properties[i].colorGroup);
                                    break;
                                }
                            }
                            printf("\n--- %s Construction ---\n", players[k].name);

                            ///constructBuildings(k);
                            playerConstruction(k);
                            playerBankrupt(k, &gameInfo.bankruptedPlayerCount);
                        }
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

            if(players[i].playerRound <= gameInfo.gameRound)
            {
                completed = 0;
                break;
            }
        }

        if(completed)
        {
            gameInfo.gameRound++;
            for(int i = 0; i < 4; i++)
            {
                if(players[i].isBankrupt == 0)
                {
                    updateLoanInterest(i);

                    if(players[i].loanRound >= 20)
                    {
                        propertyForeclose(i);
                    }
                }
            }
            updateMarketRounds(gameInfo.gameRound);
            inflation(gameInfo.gameRound);
            economicEvents(gameInfo.gameRound);
            governmentRegulations(gameInfo.gameRound);
            printf("\n\n");

            printf("=========================================\n");
            printf("Game Round %d Completed\n", gameInfo.gameRound);
            printf("=========================================\n\n");

            if(gameInfo.gameRound < FULLROUNDS)
            {
                printf("\n*******************************\n");
                printf("Game Round %d Starts\n", gameInfo.gameRound + 1);
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

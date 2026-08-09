#include <stdio.h>
#include "game.h"
#include "types.h"
#include "players.h"
#include "board.h"
#include "buyandrent.h"
#include "buildings.h"

#define INITIALCASH 30000
struct player players[4] = {

    // playerID,             name,                    priority, oldPos, currPos, money,       taxableMoney, ownedProperties, ownedCount, isInJail, jailTurns, isBankrupt, ownedRailways, railwayCount, ownedUtilities, utilityCount, hasLoan, lastRoll1, lastRoll2, playerRound, playerTurn, obtainableMaximumLoan

    {aggresiveInvestor,   "Aggressive Investor",   0,        0,      0,       INITIALCASH, 0,             {-1},             0,          0,        0,          0,          {-1},          0,             {-1},           0,              0,       0,         0,         0,           0,          0},

    {conservativeBanker,  "Conservative Banker",   0,        0,      0,       INITIALCASH, 0,             {-1},             0,          0,        0,          0,          {-1},          0,             {-1},           0,              0,       0,         0,         0,           0,          0},

    {riskTaker,           "Risk Taker",            0,        0,      0,       INITIALCASH, 0,             {-1},             0,          0,        0,          0,          {-1},          0,             {-1},           0,              0,       0,         0,         0,           0,          0},

    {opportunisticTrader, "Opportunistic Trader",  0,        0,      0,       INITIALCASH, 0,             {-1},             0,          0,        0,          0,          {-1},          0,             {-1},           0,              0,       0,         0,         0,           0,          0}
};


void playerBankrupt(int playerID, int *bankruptedPlayerCount)
{
    if(players[playerID].money <= 0 && !players[playerID].isBankrupt)
    {
        printf("%s has been declared bankrupt.\n", players[playerID].name);
        printf("Remaining assets transferred to the Bank.\n\n");

        players[playerID].isBankrupt = 1;

        while(players[playerID].ownedPropertiesCount > 0)
        {
            int propertySquare = players[playerID].ownedProperties[
                players[playerID].ownedPropertiesCount - 1];

            int propertyIndex = 0;

            while(propertyIndex < 22)
            {
                if(properties[propertyIndex].squareNumber == propertySquare)
                {
                    break;
                }

                propertyIndex++;
            }

            players[playerID].ownedProperties[
                players[playerID].ownedPropertiesCount - 1] = -1;

            players[playerID].ownedPropertiesCount--;

            if(propertyIndex < 22)
            {
                properties[propertyIndex].hasOwner = 0;
                properties[propertyIndex].owner = -1;
                properties[propertyIndex].isMortgaged = 0;
                properties[propertyIndex].isInsured = 0;
                properties[propertyIndex].houseCount = 0;
                properties[propertyIndex].hotelCount = 0;
            }
        }

        for(int i = 0; i < 4; i++)
        {
            if(railways[i].owner == playerID)
            {
                railways[i].owner = -1;
                railways[i].hasOwner = 0;
                railways[i].isMortgaged = 0;
                railways[i].currentRent = 250;
            }

            players[playerID].ownedRailways[i] = -1;
        }


        for(int i = 0; i < 2; i++)
        {
            if(utilities[i].owner == playerID)
            {
                utilities[i].owner = -1;
                utilities[i].hasOwner = 0;
                utilities[i].isMortgaged = 0;
                utilities[i].currentRent = 0;
            }

            players[playerID].ownedUtilities[i] = -1;
        }

        players[playerID].ownedPropertiesCount = 0;
        players[playerID].ownedRailwayCount = 0;
        players[playerID].ownedUtilitiesCount = 0;

        players[playerID].hasLoan = 0;

        (*(bankruptedPlayerCount))++;
    }
}

void gotoJail(int playerSquare, int k)
{
    if (playerSquare == 30) {
        players[k].currentPosition = 10; 
        players[k].isInJail = 1; 
        players[k].jailTurnCount = 0; 
        printf("%s has been sent to Jail!\n", players[k].name);
    }
}
void outOfJail(int playerSquare, int k)
{
    if(players[k].lastRoll1 == players[k].lastRoll2)
    {
        printf("%s rolled doubles and is out of Jail!\n", players[k].name);
        players[k].isInJail = 0;
        players[k].jailTurnCount = 0;
    }
    else if(players[k].money >= 300)
    {
        printf("%s paid LKR 300 to get out of Jail.\n", players[k].name);
        players[k].money -= 300;
        players[k].isInJail = 0;
        players[k].jailTurnCount = 0;
    }
    else if(players[k].jailTurnCount < 2)
    {
        players[k].jailTurnCount++;
        printf("%s is still in Jail. Turn %d of 3.\n",
               players[k].name,
               players[k].jailTurnCount);
    }
    else if(players[k].jailTurnCount == 2)
    {
        players[k].jailTurnCount++;
        printf("%s has served 3 turns in Jail and is now released.\n",
               players[k].name);
        players[k].isInJail = 0;
        players[k].jailTurnCount = 0;
    }
}
void playerConstruction(int k)
{
    switch(players[k].playerID)
    {
        case aggresiveInvestor:
            aggressiveConstruction(k);
            break;

        case conservativeBanker:
            /* later */
            break;

        case riskTaker:
            /* later */
            break;

        case opportunisticTrader:
            /* later */
            break;
    }
}

void aggressiveConstruction(int k)
{
    int building = 1;

    while(building)
    {
        building = 0;

        /* Brown */
        if(properties[0].owner == players[k].playerID &&
           properties[1].owner == players[k].playerID)
        {
            if(properties[0].houseCount <= properties[1].houseCount &&
               properties[0].houseCount < 4)
            {
                if(players[k].money >= properties[0].houseConstructionCost)
                {
                    buildHouse(k, properties[0].squareNumber);
                    building = 1;
                }
            }

            if(properties[1].houseCount <= properties[0].houseCount &&
               properties[1].houseCount < 4)
            {
                if(players[k].money >= properties[1].houseConstructionCost)
                {
                    buildHouse(k, properties[1].squareNumber);
                    building = 1;
                }
            }
        }

        /* Light Blue */
        if(properties[2].owner == players[k].playerID &&
           properties[3].owner == players[k].playerID &&
           properties[4].owner == players[k].playerID)
        {
            if(properties[2].houseCount <= properties[3].houseCount &&
               properties[2].houseCount <= properties[4].houseCount &&
               properties[2].houseCount < 4)
            {
                if(players[k].money >= properties[2].houseConstructionCost)
                {
                    buildHouse(k, properties[2].squareNumber);
                    building = 1;
                }
            }

            if(properties[3].houseCount <= properties[2].houseCount &&
               properties[3].houseCount <= properties[4].houseCount &&
               properties[3].houseCount < 4)
            {
                if(players[k].money >= properties[3].houseConstructionCost)
                {
                    buildHouse(k, properties[3].squareNumber);
                    building = 1;
                }
            }

            if(properties[4].houseCount <= properties[2].houseCount &&
               properties[4].houseCount <= properties[3].houseCount &&
               properties[4].houseCount < 4)
            {
                if(players[k].money >= properties[4].houseConstructionCost)
                {
                    buildHouse(k, properties[4].squareNumber);
                    building = 1;
                }
            }
        }

        /* Pink */
        if(properties[5].owner == players[k].playerID &&
           properties[6].owner == players[k].playerID &&
           properties[7].owner == players[k].playerID)
        {
            if(properties[5].houseCount <= properties[6].houseCount &&
               properties[5].houseCount <= properties[7].houseCount &&
               properties[5].houseCount < 4)
            {
                if(players[k].money >= properties[5].houseConstructionCost)
                {
                    buildHouse(k, properties[5].squareNumber);
                    building = 1;
                }
            }

            if(properties[6].houseCount <= properties[5].houseCount &&
               properties[6].houseCount <= properties[7].houseCount &&
               properties[6].houseCount < 4)
            {
                if(players[k].money >= properties[6].houseConstructionCost)
                {
                    buildHouse(k, properties[6].squareNumber);
                    building = 1;
                }
            }

            if(properties[7].houseCount <= properties[5].houseCount &&
               properties[7].houseCount <= properties[6].houseCount &&
               properties[7].houseCount < 4)
            {
                if(players[k].money >= properties[7].houseConstructionCost)
                {
                    buildHouse(k, properties[7].squareNumber);
                    building = 1;
                }
            }
        }

        /* Orange */
        if(properties[8].owner == players[k].playerID &&
           properties[9].owner == players[k].playerID &&
           properties[10].owner == players[k].playerID)
        {
            if(properties[8].houseCount <= properties[9].houseCount &&
               properties[8].houseCount <= properties[10].houseCount &&
               properties[8].houseCount < 4)
            {
                if(players[k].money >= properties[8].houseConstructionCost)
                {
                    buildHouse(k, properties[8].squareNumber);
                    building = 1;
                }
            }

            if(properties[9].houseCount <= properties[8].houseCount &&
               properties[9].houseCount <= properties[10].houseCount &&
               properties[9].houseCount < 4)
            {
                if(players[k].money >= properties[9].houseConstructionCost)
                {
                    buildHouse(k, properties[9].squareNumber);
                    building = 1;
                }
            }

            if(properties[10].houseCount <= properties[8].houseCount &&
               properties[10].houseCount <= properties[9].houseCount &&
               properties[10].houseCount < 4)
            {
                if(players[k].money >= properties[10].houseConstructionCost)
                {
                    buildHouse(k, properties[10].squareNumber);
                    building = 1;
                }
            }
        }

        /* Red */
        if(properties[11].owner == players[k].playerID &&
           properties[12].owner == players[k].playerID &&
           properties[13].owner == players[k].playerID)
        {
            if(properties[11].houseCount <= properties[12].houseCount &&
               properties[11].houseCount <= properties[13].houseCount &&
               properties[11].houseCount < 4)
            {
                if(players[k].money >= properties[11].houseConstructionCost)
                {
                    buildHouse(k, properties[11].squareNumber);
                    building = 1;
                }
            }

            if(properties[12].houseCount <= properties[11].houseCount &&
               properties[12].houseCount <= properties[13].houseCount &&
               properties[12].houseCount < 4)
            {
                if(players[k].money >= properties[12].houseConstructionCost)
                {
                    buildHouse(k, properties[12].squareNumber);
                    building = 1;
                }
            }

            if(properties[13].houseCount <= properties[11].houseCount &&
               properties[13].houseCount <= properties[12].houseCount &&
               properties[13].houseCount < 4)
            {
                if(players[k].money >= properties[13].houseConstructionCost)
                {
                    buildHouse(k, properties[13].squareNumber);
                    building = 1;
                }
            }
        }

        /* Yellow */
        if(properties[14].owner == players[k].playerID &&
           properties[15].owner == players[k].playerID &&
           properties[16].owner == players[k].playerID)
        {
            if(properties[14].houseCount <= properties[15].houseCount &&
               properties[14].houseCount <= properties[16].houseCount &&
               properties[14].houseCount < 4)
            {
                if(players[k].money >= properties[14].houseConstructionCost)
                {
                    buildHouse(k, properties[14].squareNumber);
                    building = 1;
                }
            }

            if(properties[15].houseCount <= properties[14].houseCount &&
               properties[15].houseCount <= properties[16].houseCount &&
               properties[15].houseCount < 4)
            {
                if(players[k].money >= properties[15].houseConstructionCost)
                {
                    buildHouse(k, properties[15].squareNumber);
                    building = 1;
                }
            }

            if(properties[16].houseCount <= properties[14].houseCount &&
               properties[16].houseCount <= properties[15].houseCount &&
               properties[16].houseCount < 4)
            {
                if(players[k].money >= properties[16].houseConstructionCost)
                {
                    buildHouse(k, properties[16].squareNumber);
                    building = 1;
                }
            }
        }

        /* Green */
        if(properties[17].owner == players[k].playerID &&
           properties[18].owner == players[k].playerID &&
           properties[19].owner == players[k].playerID)
        {
            if(properties[17].houseCount <= properties[18].houseCount &&
               properties[17].houseCount <= properties[19].houseCount &&
               properties[17].houseCount < 4)
            {
                if(players[k].money >= properties[17].houseConstructionCost)
                {
                    buildHouse(k, properties[17].squareNumber);
                    building = 1;
                }
            }

            if(properties[18].houseCount <= properties[17].houseCount &&
               properties[18].houseCount <= properties[19].houseCount &&
               properties[18].houseCount < 4)
            {
                if(players[k].money >= properties[18].houseConstructionCost)
                {
                    buildHouse(k, properties[18].squareNumber);
                    building = 1;
                }
            }

            if(properties[19].houseCount <= properties[17].houseCount &&
               properties[19].houseCount <= properties[18].houseCount &&
               properties[19].houseCount < 4)
            {
                if(players[k].money >= properties[19].houseConstructionCost)
                {
                    buildHouse(k, properties[19].squareNumber);
                    building = 1;
                }
            }
        }

        /* Dark Blue */
        if(properties[20].owner == players[k].playerID &&
           properties[21].owner == players[k].playerID)
        {
            if(properties[20].houseCount <= properties[21].houseCount &&
               properties[20].houseCount < 4)
            {
                if(players[k].money >= properties[20].houseConstructionCost)
                {
                    buildHouse(k, properties[20].squareNumber);
                    building = 1;
                }
            }

            if(properties[21].houseCount <= properties[20].houseCount &&
               properties[21].houseCount < 4)
            {
                if(players[k].money >= properties[21].houseConstructionCost)
                {
                    buildHouse(k, properties[21].squareNumber);
                    building = 1;
                }
            }
        }
    }
}
/*
void determineWinner(){
    int b =0;
    while(b<4)
    {
        if(players[b].isBankrupt==0)
        {
            players[b].netWorth = players[b].money;
        b++;
    }
}
*/
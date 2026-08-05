#include <stdio.h>
#include "game.h"
#include "types.h"
#include "players.h"
#include "board.h"
#include "buyandrent.h"

#define INITIALCASH 30000

//void playerStructure(){

struct player players[4] = {
    // playerID,             name,                    priority, oldPos, currPos, money,       taxableMoney, ownedProps, ownedCount, isInJail, jailTurns, isBankrupt, railwayCount, ownedUtilities, utilityCount, hasLoan, lastRoll1, lastRoll2, playerRound, playerTurn

    {aggresiveInvestor,   "Aggressive Investor",   0,        0,      0,       INITIALCASH, 0,             {-1},        0,          0,        0,         0,          0,            {-1},            0,            0,       0,         0,         0,           0},

    {conservativeBanker,  "Conservative Banker",   0,        0,      0,       INITIALCASH, 0,             {-1},        0,          0,        0,         0,          0,            {-1},            0,            0,       0,         0,         0,           0},

    {riskTaker,           "Risk Taker",            0,        0,      0,       INITIALCASH, 0,             {-1},        0,          0,        0,         0,          0,            {-1},            0,            0,       0,         0,         0,           0},

    {opportunisticTrader, "Opportunistic Trader",  0,        0,      0,       INITIALCASH, 0,             {0},        0,          0,        0,         0,          0,            {0},            0,            0,       0,         0,         0,           0}
};

//}

void playerBankrupt(int playerID, int bankruptedPlayerCount)
{
    if(players[playerID].money <= 0 && !players[playerID].isBankrupt)
    {
        printf("%s has been declared bankrupt.\n", players[playerID].name);
        printf("Remaining assets transferred to the Bank.\n\n");

        players[playerID].isBankrupt = 1;

        /* Release Properties */
        while(players[playerID].ownedPropertiesCount > 0)
        {
            int propertyIndex = players[playerID].ownedProperties[players[playerID].ownedPropertiesCount - 1];

            players[playerID].ownedProperties[players[playerID].ownedPropertiesCount - 1] = -1;
            players[playerID].ownedPropertiesCount--;

            properties[propertyIndex].hasOwner = 0;
            properties[propertyIndex].owner = -1;
            properties[propertyIndex].isMortgaged = 0;
            properties[propertyIndex].isInsured = 0;
            properties[propertyIndex].houseCount = 0;
            properties[propertyIndex].hotelCount = 0;
        }

        /* Release Railways */
        for(int i = 0; i < 4; i++)
        {
            if(railways[i].owner == playerID)
            {
                railways[i].owner = -1;
                railways[i].hasOwner = 0;
                railways[i].isMortgaged = 0;
            }

            players[playerID].ownedRailways[i] = -1;
        }

        /* Release Utilities */
        for(int i = 0; i < 2; i++)
        {
            if(utilities[i].owner == playerID)
            {
                utilities[i].owner = -1;
                utilities[i].hasOwner = 0;
                utilities[i].isMortgaged = 0;
            }

            players[playerID].ownedUtilities[i] = -1;
        }

        players[playerID].ownedPropertiesCount = 0;
        players[playerID].ownedRailwayCount = 0;
        players[playerID].ownedUtilitiesCount = 0;

        players[playerID].hasLoan = 0;

        (bankruptedPlayerCount)++;
    }
}
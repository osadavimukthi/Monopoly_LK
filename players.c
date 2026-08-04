#include <stdio.h>
#include "types.h"

#define INITIALCASH 30000

//void playerStructure(){

struct player players[4] = {
    // playerID,             name,                    priority, oldPos, currPos, money,       ownedProps, ownedCount, isInJail, jailTurns, isBankrupt, railwayCount, utility, hasLoan, lastRoll1, lastRoll2, playerRound, playerTurn

    {aggresiveInvestor,   "Aggressive Investor",   0,        0,      0,       INITIALCASH, {0},        0,          0,        0,         0,          0,            0,       0,       0,         0,         0,           0},

    {conservativeBanker,  "Conservative Banker",   0,        0,      0,       INITIALCASH, {0},        0,          0,        0,         0,          0,            0,       0,       0,         0,         0,           0},

    {riskTaker,           "Risk Taker",            0,        0,      0,       INITIALCASH, {0},        0,          0,        0,         0,          0,            0,       0,       0,         0,         0,           0},

    {opportunisticTrader, "Opportunistic Trader",  0,        0,      0,       INITIALCASH, {0},        0,          0,        0,         0,          0,            0,       0,       0,         0,         0,           0}
};

//}
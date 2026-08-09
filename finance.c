#include <stdio.h>
#include "types.h"

//void board();

struct Insurance insurance[3]={
    {basicPropertyInsurance,0, {fire, flood, -1, -1, -1, -1, -1}, 5, 80},

    {
        comprehensiveInsurance, 0, {fire, flood, riot, -1, -1, vandalism, earthquake}, 10, 100
    },
    {
        BusinessInterruptionInsurance, 0, {fire, flood, riot, buildingCollapse, electricalFailure, vandalism, earthquake}, 15, 70
    },
};

int calculateMaximumLoan(int playerId){
    int maximumLoan = 0;
    int c = 0;
    players[playerId].obtainableMaximumLoan = 0;

    while(c < 22){
        if(properties[c].hasOwner && !(properties[c].isMortgaged) && properties[c].owner == players[playerId].playerID)
        {
            int loanValue = properties[c].mortgagedValue * 0.75;
            players[playerId].obtainableMaximumLoan += loanValue;
            maximumLoan += loanValue;
        }
        c++;
    }

    c = 0;
    while(c < 4){
        if(railways[c].hasOwner && !(railways[c].isMortgaged) && railways[c].owner == players[playerId].playerID)
        {
            int loanValue = railways[c].mortgageValue * 0.75;
            players[playerId].obtainableMaximumLoan += loanValue;
            maximumLoan += loanValue;
        }
        c++;
    }

    c = 0;
    while(c < 2){
        if(utilities[c].hasOwner && !(utilities[c].isMortgaged) && utilities[c].owner == players[playerId].playerID)
        {
            int loanValue = utilities[c].mortgageValue * 0.75;
            players[playerId].obtainableMaximumLoan += loanValue;
            maximumLoan += loanValue;
        }
        c++;
    }

    return maximumLoan;
}

void obtainLoan(int playerID)
{
    int loanAmount = calculateMaximumLoan(playerID);
    players[playerID].money += loanAmount;
    players[playerID].obtainableMaximumLoan = 0;
    printf("%s has obtained a loan of %d LKR.\n", players[playerID].name, loanAmount);

    int d = 0;
    while(d < 22){
        if(properties[d].hasOwner && !(properties[d].isMortgaged) && properties[d].owner == players[playerID].playerID)
        {
            properties[d].isMortgaged = 1;
        }
        d++;
    }

    d = 0;
    while(d < 4){
        if(railways[d].hasOwner && !(railways[d].isMortgaged) && railways[d].owner == players[playerID].playerID)
        {
            railways[d].isMortgaged = 1;
        }
        d++;
    }

    d = 0;
    while(d < 2){
        if(utilities[d].hasOwner && !(utilities[d].isMortgaged) && utilities[d].owner == players[playerID].playerID)
        {
            utilities[d].isMortgaged = 1;
        }
        d++;
    }
}

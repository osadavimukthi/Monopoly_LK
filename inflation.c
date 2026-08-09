#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"

void propertyInflation(int randomPercentage)
{
    int i = 0;
    while(i<22){
    properties[i].currentPrice = properties[i].currentPrice * (1 + (randomPercentage / 100.0));
    
    properties[i].houseConstructionCost = properties[i].houseConstructionCost * (1 + (randomPercentage / 100.0));
    properties[i].hotelConstructionCost = properties[i].hotelConstructionCost * (1 + (randomPercentage / 100.0));
    properties[i].currentRent = properties[i].currentRent * (1 + (randomPercentage / 100.0));
    i++;
    }
    printf("Property prices have been updated due to inflation.\n");
}

void insuaranceInflation(int randomPercentage)
{
    int i = 0;
    while(i<3)
    {
    insurance[i].insurancePremium = insurance[i].insurancePremium * (1 + (randomPercentage / 100.0));
    i++;
    }
    printf("Insurance premiums have been updated due to inflation.\n");
}

void loanInflation(int randomPercentage)
{
    int i = 0;
    while(i<4)
    {
    playerLoans[i].interestRate = playerLoans[i].interestRate * (1 + (randomPercentage / 100.0));
    i++;
    }
    printf("Loan interest rates have been updated due to inflation.\n");
}


void inflation(int gameRound)
{
    if(gameRound % 10 == 0)
    {
        int random[6] = {-3,0,2,5,8,12};
        srand(time(NULL));
        int randomPercentage = random[rand() % 6];
        switch(randomPercentage)
        {
            case -3:
                printf("Inflation: -3%%\n");
                propertyInflation(randomPercentage);
                insuaranceInflation(randomPercentage);
                loanInflation(randomPercentage);
                break;
            case 0:
                printf("Inflation: 0%%\n");
                propertyInflation(randomPercentage);
                insuaranceInflation(randomPercentage);
                loanInflation(randomPercentage);
                break;
            case 2:
                printf("Inflation: 2%%\n");
                propertyInflation(randomPercentage);
                insuaranceInflation(randomPercentage);
                loanInflation(randomPercentage);
                break;
            case 5:
                printf("Inflation: 5%%\n");
                propertyInflation(randomPercentage);
                insuaranceInflation(randomPercentage);
                loanInflation(randomPercentage);
                break;
            case 8:
                printf("Inflation: 8%%\n");
                propertyInflation(randomPercentage);
                insuaranceInflation(randomPercentage);
                loanInflation(randomPercentage);
                break;
            case 12:
                printf("Inflation: 12%%\n");
                propertyInflation(randomPercentage);
                insuaranceInflation(randomPercentage);
                loanInflation(randomPercentage);
                break;
        }
    }
}
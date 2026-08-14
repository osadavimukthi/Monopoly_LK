#include <stdio.h>
#include <stdlib.h>
#include "types.h"

void propertyInflation(int randomPercentage)
{
    int i = 0;

    while(i < 22)
    {
        properties[i].currentPrice =
            properties[i].currentPrice *
            (100 + randomPercentage) / 100;

        properties[i].houseConstructionCost =
            properties[i].houseConstructionCost *
            (100 + randomPercentage) / 100;

        properties[i].hotelConstructionCost =
            properties[i].hotelConstructionCost *
            (100 + randomPercentage) / 100;

        properties[i].currentRent =
            properties[i].currentRent *
            (100 + randomPercentage) / 100;

        properties[i].repairCost =
            properties[i].repairCost *
            (100 + randomPercentage) / 100;

        i++;
    }

    printf("Property prices, building costs, rent and repair costs "
           "have been updated due to inflation.\n");
}


void insuaranceInflation(int randomPercentage)
{
    int i = 0;

    while(i < 3)
    {
        insurance[i].insurancePremium =
            insurance[i].insurancePremium *
            (100 + randomPercentage) / 100;

        i++;
    }

    printf("Insurance premiums have been updated due to inflation.\n");
}


void loanInflation(int randomPercentage)
{
    rates.interestRate =
        rates.interestRate *
        (100 + randomPercentage) / 100;

    printf("Loan interest rate has been updated due to inflation.\n");
}


void inflation(int gameRound)
{
    int random[6] = {-3, 0, 2, 5, 8, 12};
    int randomPercentage;

    if(gameRound % 10 == 0)
    {
        randomPercentage = random[rand() % 6];

        printf("\nInflation: %d%%\n",
               randomPercentage);

        propertyInflation(randomPercentage);
        insuaranceInflation(randomPercentage);
        loanInflation(randomPercentage);
    }
}
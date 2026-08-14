#include <stdio.h>
#include "types.h"

struct rate rates = {8, 15};  // 8% interest rate, 15% income tax rate
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

int calculateMaximumLoan(int playerId)
{
    int maximumLoan = 0;
    int c = 0;
    int loanValue;

    players[playerId].obtainableMaximumLoan = 0;

    while(c < 22)
    {
        if(properties[c].hasOwner &&
           properties[c].isMortgaged == 0 &&
           properties[c].owner == players[playerId].playerID)
        {
            loanValue = (properties[c].mortgagedValue * 75) / 100;
            maximumLoan += loanValue;
        }
        c++;
    }
    c = 0;
    while(c < 4)
    {
        if(railways[c].hasOwner && railways[c].isMortgaged == 0 
            && railways[c].owner == players[playerId].playerID)
        {
            loanValue = (railways[c].mortgageValue * 75) / 100;
            maximumLoan += loanValue;
        }

        c++;
    }

    c = 0;

    while(c < 2)
    {
        if(utilities[c].hasOwner &&
           utilities[c].isMortgaged == 0 &&
           utilities[c].owner == players[playerId].playerID)
        {
            loanValue = (utilities[c].mortgageValue * 75) / 100;
            maximumLoan += loanValue;
        }

        c++;
    }

    players[playerId].obtainableMaximumLoan = maximumLoan;
    return maximumLoan;
}

void lockLoanCollateral(int playerID)
{
    int i;

    for(i = 0; i < 22; i++)
    {
        if(properties[i].hasOwner && properties[i].isMortgaged == 0 
            && properties[i].owner == players[playerID].playerID)
        {
            properties[i].isLoanLocked = 1;
        }
    }

    for(i = 0; i < 4; i++)
    {
        if(railways[i].hasOwner && railways[i].isMortgaged == 0 
            && railways[i].owner == players[playerID].playerID)
        {
            railways[i].isLoanLocked = 1;
        }
    }

    for(i = 0; i < 2; i++)
    {
        if(utilities[i].hasOwner &&
           utilities[i].isMortgaged == 0 &&
           utilities[i].owner == players[playerID].playerID)
        {
            utilities[i].isLoanLocked = 1;
        }
    }
}

void unlockLoanCollateral(int playerID)
{
    int i;

    for(i = 0; i < 22; i++)
    {
        if(properties[i].owner == players[playerID].playerID)
        {
            properties[i].isLoanLocked = 0;
        }
    }

    for(i = 0; i < 4; i++)
    {
        if(railways[i].owner == players[playerID].playerID)
        {
            railways[i].isLoanLocked = 0;
        }
    }

    for(i = 0; i < 2; i++)
    {
        if(utilities[i].owner == players[playerID].playerID)
        {
            utilities[i].isLoanLocked = 0;
        }
    }
}
void obtainLoan(int playerID, int playerPosition)
{
    int loanAmount;

    if(board[playerPosition].type != Bank)
    {
        return;
    }

    if(players[playerID].hasLoan == 1)
    {
        printf("%s already has an active loan.\n\n",
               players[playerID].name);

        return;
    }

    loanAmount = calculateMaximumLoan(playerID);

    if(loanAmount <= 0)
    {
        printf("%s does not have sufficient collateral for a loan.\n\n",
               players[playerID].name);

        return;
    }

    players[playerID].money += loanAmount;

    players[playerID].currentLoan = loanAmount;

players[playerID].hasLoan = 1;

players[playerID].loanRound = 0;

players[playerID].loanInterestRate = rates.interestRate;

    players[playerID].obtainableMaximumLoan = 0;

    lockLoanCollateral(playerID);

    printf("%s has obtained a secured loan.\n\n",
           players[playerID].name);

    printf("Loan Amount : LKR %d\n",
           loanAmount);

    printf("Interest Rate : %d%%\n",
           rates.interestRate);

    printf("Duration : 20 rounds\n\n");
}

void updateLoanInterest(int playerID)
{
    if(players[playerID].hasLoan == 1)
    {
        players[playerID].currentLoan =
            players[playerID].currentLoan +
            (players[playerID].currentLoan *
             players[playerID].loanInterestRate / 100);

        players[playerID].loanRound++;

        printf("%s loan interest accumulated.\n",
               players[playerID].name);

        printf("Interest Rate : %d%%\n",
               players[playerID].loanInterestRate);

        printf("Outstanding Loan : LKR %d\n",
               players[playerID].currentLoan);

        printf("Loan Round : %d / 20\n\n",
               players[playerID].loanRound);
    }
}

void repayFullLoan(int playerID)
{
    if(board[players[playerID].currentPosition].type != Bank)
    {
        printf("%s is not at the Bank.\n\n",
               players[playerID].name);

        return;
    }

    if(players[playerID].hasLoan == 0)
    {
        printf("%s does not have an active loan.\n\n",
               players[playerID].name);

        return;
    }

    if(players[playerID].money < players[playerID].currentLoan)
    {
        printf("%s does not have enough money to repay the full loan.\n\n",
               players[playerID].name);

        return;
    }

    players[playerID].money -= players[playerID].currentLoan;

    printf("%s repaid the full loan of LKR %d.\n",
           players[playerID].name,
           players[playerID].currentLoan);

    players[playerID].currentLoan = 0;

players[playerID].hasLoan = 0;

players[playerID].loanRound = 0;

players[playerID].loanInterestRate = 0;

players[playerID].obtainableMaximumLoan = 0;

    unlockLoanCollateral(playerID);

    printf("%s has fully repaid the loan.\n",
           players[playerID].name);

    printf("Loan collateral has been unlocked.\n\n");
}
void repayPartofLoan(int playerID, int amount)
{
    if(board[players[playerID].currentPosition].type != Bank)
    {
        printf("%s is not at the Bank.\n\n",
               players[playerID].name);

        return;
    }

    if(players[playerID].hasLoan == 0)
    {
        printf("%s does not have an active loan.\n\n",
               players[playerID].name);

        return;
    }

    if(amount <= 0)
    {
        printf("Invalid repayment amount.\n\n");

        return;
    }

    if(amount > players[playerID].money)
    {
        printf("%s does not have enough money to repay LKR %d.\n\n",
               players[playerID].name,
               amount);

        return;
    }

    if(amount > players[playerID].currentLoan)
    {
        amount = players[playerID].currentLoan;
    }

    players[playerID].money -= amount;

    players[playerID].currentLoan -= amount;

    printf("%s paid LKR %d of the loan.\n",
           players[playerID].name,
           amount);

    printf("Outstanding Loan : LKR %d\n\n",
           players[playerID].currentLoan);

    if(players[playerID].currentLoan == 0)
{
    players[playerID].hasLoan = 0;

    players[playerID].loanRound = 0;

    players[playerID].loanInterestRate = 0;

    players[playerID].obtainableMaximumLoan = 0;

        unlockLoanCollateral(playerID);

        printf("%s has fully repaid the loan.\n",
               players[playerID].name);

        printf("Loan collateral has been unlocked.\n\n");
    }
}
void increaseLoan(int playerID, int amount)
{
    int maximumLoan;
    int maximumAdditionalLoan;

    if(board[players[playerID].currentPosition].type != Bank)
    {
        printf("%s is not at the Bank.\n\n",
               players[playerID].name);

        return;
    }

    if(players[playerID].hasLoan == 0)
    {
        printf("%s does not have an active loan.\n\n",
               players[playerID].name);

        return;
    }

    if(amount <= 0)
    {
        printf("Invalid loan increase amount.\n\n");

        return;
    }

    maximumLoan = calculateMaximumLoan(playerID);

    maximumAdditionalLoan =
        maximumLoan - players[playerID].currentLoan;

    if(maximumAdditionalLoan <= 0)
    {
        printf("%s cannot increase the loan.\n",
               players[playerID].name);

        printf("Current Loan : LKR %d\n",
               players[playerID].currentLoan);

        printf("Maximum Loan : LKR %d\n\n",
               maximumLoan);

        return;
    }

    if(amount > maximumAdditionalLoan)
    {
        amount = maximumAdditionalLoan;
    }

    players[playerID].money += amount;

    players[playerID].currentLoan += amount;

    players[playerID].obtainableMaximumLoan = 0;

    lockLoanCollateral(playerID);

    printf("%s increased the loan by LKR %d.\n",
           players[playerID].name,
           amount);

    printf("Total Outstanding Loan : LKR %d\n",
           players[playerID].currentLoan);

    printf("Interest Rate : %d%%\n",
           players[playerID].loanInterestRate);

    printf("Loan Round : %d / 20\n",
           players[playerID].loanRound);

    printf("Remaining Cash : LKR %d\n\n",
           players[playerID].money);
}

void extendLoanPeriod(int playerID)
{
    if(board[players[playerID].currentPosition].type != Bank)
    {
        printf("%s is not at the Bank.\n\n",
               players[playerID].name);

        return;
    }

    if(players[playerID].hasLoan == 0)
    {
        printf("%s does not have an active loan.\n\n",
               players[playerID].name);

        return;
    }

    players[playerID].loanRound = 0;

    printf("%s extended the loan period.\n",
           players[playerID].name);

    printf("New Loan Round : 0 / 20\n\n");
}

void propertyForeclose(int playerID)
{
    int i;
    int j;
    int k;
    int propertySquare;

    if(players[playerID].hasLoan == 1 &&
       players[playerID].loanRound >= 20)
    {
        printf("\n%s has defaulted on the loan.\n",
               players[playerID].name);


        /* Foreclose Properties */

        for(i = 0; i < 22; i++)
        {
            if(properties[i].owner ==
               players[playerID].playerID &&
               properties[i].isLoanLocked == 1)
            {
                propertySquare =
                    properties[i].squareNumber;

                properties[i].hasOwner = 0;
                properties[i].owner = -1;
                properties[i].isLoanLocked = 0;
                properties[i].isMortgaged = 0;
                properties[i].houseCount = 0;
                properties[i].hotelCount = 0;
                properties[i].isInsured = 0;


                /* Remove property from player's list */

                for(j = 0;
                    j < players[playerID].ownedPropertiesCount;
                    j++)
                {
                    if(players[playerID].ownedProperties[j] ==
                       propertySquare)
                    {
                        for(k = j;
                            k < players[playerID].ownedPropertiesCount - 1;
                            k++)
                        {
                            players[playerID].ownedProperties[k] =
                                players[playerID].ownedProperties[k + 1];
                        }

                        players[playerID].ownedPropertiesCount--;

                        players[playerID].ownedProperties[
                            players[playerID].ownedPropertiesCount] = -1;

                        break;
                    }
                }
            }
        }


        /* Foreclose Railways */

        for(i = 0; i < 4; i++)
        {
            if(railways[i].owner ==
               players[playerID].playerID &&
               railways[i].isLoanLocked == 1)
            {
                railways[i].hasOwner = 0;
                railways[i].owner = -1;
                railways[i].isLoanLocked = 0;
                railways[i].isMortgaged = 0;
                railways[i].currentRent = 250;


                /* Remove railway from player's list */

                for(j = 0;
                    j < players[playerID].ownedRailwayCount;
                    j++)
                {
                    if(players[playerID].ownedRailways[j] ==
                       railways[i].squareNumber)
                    {
                        for(k = j;
                            k < players[playerID].ownedRailwayCount - 1;
                            k++)
                        {
                            players[playerID].ownedRailways[k] =
                                players[playerID].ownedRailways[k + 1];
                        }

                        players[playerID].ownedRailwayCount--;

                        players[playerID].ownedRailways[
                            players[playerID].ownedRailwayCount] = -1;

                        break;
                    }
                }
            }
        }


        /* Foreclose Utilities */

        for(i = 0; i < 2; i++)
        {
            if(utilities[i].owner ==
               players[playerID].playerID &&
               utilities[i].isLoanLocked == 1)
            {
                utilities[i].hasOwner = 0;
                utilities[i].owner = -1;
                utilities[i].isLoanLocked = 0;
                utilities[i].isMortgaged = 0;
                utilities[i].currentRent = 0;


                /* Remove utility from player's list */

                for(j = 0;
                    j < players[playerID].ownedUtilitiesCount;
                    j++)
                {
                    if(players[playerID].ownedUtilities[j] ==
                       utilities[i].squareNumber)
                    {
                        for(k = j;
                            k < players[playerID].ownedUtilitiesCount - 1;
                            k++)
                        {
                            players[playerID].ownedUtilities[k] =
                                players[playerID].ownedUtilities[k + 1];
                        }

                        players[playerID].ownedUtilitiesCount--;

                        players[playerID].ownedUtilities[
                            players[playerID].ownedUtilitiesCount] = -1;

                        break;
                    }
                }
            }
        }


        /* Clear Loan */

        players[playerID].currentLoan = 0;
players[playerID].hasLoan = 0;
players[playerID].loanRound = 0;
players[playerID].loanInterestRate = 0;
players[playerID].obtainableMaximumLoan = 0;


        printf("Collateral has been foreclosed.\n");
        printf("Outstanding debt has been cleared.\n\n");
    }
}


void renovateProperty(int squareNumber, int playerID)
{
    int propertyIndex = -1;
    int i;
    int renovationCost;

    for(i = 0; i < 22; i++)
    {
        if(properties[i].squareNumber == squareNumber)
        {
            propertyIndex = i;
            break;
        }
    }

    if(propertyIndex == -1)
    {
        return;
    }

    if(properties[propertyIndex].owner != players[playerID].playerID)
    {
        return;
    }

    if(properties[propertyIndex].depreciationPercent == 0)
    {
        return;
    }

    renovationCost = properties[propertyIndex].currentPrice * 10 / 100;

    if(players[playerID].money >= renovationCost)
    {
        players[playerID].money -= renovationCost;

        properties[propertyIndex].propertyAge = 0;
        properties[propertyIndex].depreciationPercent = 0;

        printf("%s renovated %s for LKR %d.\n",
               players[playerID].name,
               properties[propertyIndex].name,
               renovationCost);
    }
}

void communityDevelopmentFund(int playerID)
{
    int i;
    int totalAssets = 0;
    int tax;

    for(i = 0; i < 22; i++)
    {
        if(properties[i].hasOwner &&
           properties[i].owner == players[playerID].playerID)
        {
            totalAssets += properties[i].currentPrice;
        }
    }

    tax = totalAssets * 10 / 100;

    players[playerID].money -= tax;
    players[playerID].taxableMoney -= tax;

    printf("%s landed on Community Development Fund.\n",players[playerID].name);

    printf("Total Property Assets : LKR %d\n",totalAssets);

    printf("Community Development Fund Tax : LKR %d\n\n",tax);
}

void playerBankrupt(int playerID, int *bankruptedPlayerCount)
{
    int i;
    int j;
    int totalAssets = 0;
    int totalLiabilities = 0;
    int propertyIndex;

    /*
     * Calculate the player's available assets.
     *
     * Cash
     */
    totalAssets = players[playerID].money;

    /*
     * Property values
     */
    for(i = 0; i < players[playerID].ownedPropertiesCount; i++)
    {
        propertyIndex = -1;

        for(j = 0; j < 22; j++)
        {
            if(properties[j].squareNumber ==
               players[playerID].ownedProperties[i])
            {
                propertyIndex = j;
                break;
            }
        }

        if(propertyIndex != -1)
        {
            totalAssets += properties[propertyIndex].currentPrice;
        }
    }

    /*
     * Railway values
     */
    for(i = 0; i < 4; i++)
    {
        if(railways[i].owner == players[playerID].playerID)
        {
            totalAssets += railways[i].currentPrice;
        }
    }

    /*
     * Utility values
     */
    for(i = 0; i < 2; i++)
    {
        if(utilities[i].owner == players[playerID].playerID)
        {
            totalAssets += utilities[i].currentPrice;
        }
    }

    /*
     * Current outstanding loan is a liability.
     */
    totalLiabilities = players[playerID].currentLoan;

    /*
     * Do not declare bankruptcy simply because
     * the player has no cash.
     *
     * Bankruptcy occurs when liabilities exceed
     * available assets.
     */
    if(totalLiabilities <= totalAssets ||
       players[playerID].isBankrupt)
    {
        return;
    }

    printf("%s has been declared bankrupt.\n",
           players[playerID].name);

    printf("Remaining assets transferred to the Bank.\n\n");

    players[playerID].isBankrupt = 1;

    /*
     * Remove all properties.
     *
     * Buildings are demolished.
     * Insurance expires.
     * Mortgage and loan-lock information is cleared.
     */
    for(i = 0; i < players[playerID].ownedPropertiesCount; i++)
    {
        propertyIndex = -1;

        for(j = 0; j < 22; j++)
        {
            if(properties[j].squareNumber ==
               players[playerID].ownedProperties[i])
            {
                propertyIndex = j;
                break;
            }
        }

        if(propertyIndex != -1)
        {
            properties[propertyIndex].hasOwner = 0;
            properties[propertyIndex].owner = -1;

            properties[propertyIndex].isMortgaged = 0;
            properties[propertyIndex].isLoanLocked = 0;

            /*
             * Insurance expires.
             */
            properties[propertyIndex].isInsured = 0;

            /*
             * Demolish all buildings.
             */
            properties[propertyIndex].houseCount = 0;
            properties[propertyIndex].hotelCount = 0;
        }

        players[playerID].ownedProperties[i] = -1;
    }

    players[playerID].ownedPropertiesCount = 0;

    /*
     * Release all railways.
     */
    for(i = 0; i < 4; i++)
    {
        if(railways[i].owner == players[playerID].playerID)
        {
            railways[i].owner = -1;
            railways[i].hasOwner = 0;

            railways[i].isMortgaged = 0;
            railways[i].isLoanLocked = 0;

            railways[i].currentRent =
                railways[i].baseRent;
        }

        players[playerID].ownedRailways[i] = -1;
    }

    players[playerID].ownedRailwayCount = 0;

    /*
     * Release all utilities.
     */
    for(i = 0; i < 2; i++)
    {
        if(utilities[i].owner == players[playerID].playerID)
        {
            utilities[i].owner = -1;
            utilities[i].hasOwner = 0;

            utilities[i].isMortgaged = 0;
            utilities[i].isLoanLocked = 0;

            utilities[i].currentRent =
                utilities[i].baseRent;
        }

        players[playerID].ownedUtilities[i] = -1;
    }

    players[playerID].ownedUtilitiesCount = 0;

    /*
     * Loan is cleared because the player
     * has been declared bankrupt.
     */
    players[playerID].hasLoan = 0;
    players[playerID].currentLoan = 0;
    players[playerID].loanRound = 0;
    players[playerID].loanInterestRate = 0;
    players[playerID].obtainableMaximumLoan = 0;

    /*
     * Count the bankrupt player only once.
     */
    (*bankruptedPlayerCount)++;
}
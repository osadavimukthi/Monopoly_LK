#include <stdio.h>
#include "types.h"
#include "finance.h"

struct rate rates = {8, 15};  // 8% interest rate, 15% income tax rate
//void board();
    
struct Insurance insurance[3] =
{
    {
        basicPropertyInsurance,
        0,
        {fire, flood, -1, -1, -1, -1, -1},
        5,
        80
    },

    {
        comprehensiveInsurance,
        0,
        {fire, flood, riot, -1, -1, vandalism, earthquake},
        10,
        100
    },

    {
        BusinessInterruptionInsurance,
        0,
        {
            fire,
            flood,
            riot,
            buildingCollapse,
            electricalFailure,
            vandalism,
            earthquake
        },
        15,
        100
    }
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
           properties[c].isClosed == 0 &&
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
        if(properties[i].hasOwner &&
           properties[i].isMortgaged == 0 &&
           properties[i].isClosed == 0 &&
           properties[i].isLoanLocked == 0 &&
           properties[i].owner == players[playerID].playerID)
        {
            properties[i].isLoanLocked = 1;
        }
    }

    for(i = 0; i < 4; i++)
    {
        if(railways[i].hasOwner &&
           railways[i].isMortgaged == 0 &&
           railways[i].isLoanLocked == 0 &&
           railways[i].owner == players[playerID].playerID)
        {
            railways[i].isLoanLocked = 1;
        }
    }

    for(i = 0; i < 2; i++)
    {
        if(utilities[i].hasOwner &&
           utilities[i].isMortgaged == 0 &&
           utilities[i].isLoanLocked == 0 &&
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
                properties[i].isClosed = 0;


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

        if(!shouldRenovateProperty(
            playerID,
            properties[propertyIndex].depreciationPercent))
        {
            return;
        }

    renovationCost = properties[propertyIndex].currentPrice * 10 / 100;

    if(players[playerID].money >= renovationCost)
{
    players[playerID].money -= renovationCost;

    if(properties[propertyIndex].depreciationPercent > 0)
    {
        properties[propertyIndex].currentPrice =
            properties[propertyIndex].currentPrice *
            100 /
            (100 - properties[propertyIndex].depreciationPercent);
    }

    properties[propertyIndex].propertyAge = 0;
    properties[propertyIndex].depreciationPercent = 0;

    printf("%s renovated %s for LKR %d.\n",
           players[playerID].name,
           properties[propertyIndex].name,
           renovationCost);

    printf("Property depreciation restored.\n");
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

    totalAssets += players[playerID].money;
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

int calculateAverageBuildingCondition(int propertyIndex)
{
    int i;
    int totalCondition = 0;
    int buildingCount = 0;

    /*
     * Buildings on the same property may have different
     * condition ratings. Therefore, the average condition
     * is used to represent the overall building condition
     * of the property when determining rent collection.
     */

    if(properties[propertyIndex].hotelCount > 0)
    {
        return properties[propertyIndex].buildingCondition[0];
    }

    for(i = 0; i < properties[propertyIndex].houseCount; i++)
    {
        totalCondition +=
            properties[propertyIndex].buildingCondition[i];

        buildingCount++;
    }

    if(buildingCount == 0)
    {
        return 100;
    }

    return totalCondition / buildingCount;
}

int getConditionRentPercentage(int averageCondition)
{
    if(averageCondition >= 90)
    {
        return 100;
    }
    else if(averageCondition >= 75)
    {
        return 90;
    }
    else if(averageCondition >= 50)
    {
        return 75;
    }
    else if(averageCondition >= 25)
    {
        return 50;
    }

    return 0;
}

void updateBuildingCondition()
{
    int i;
    int j;

    for(i = 0; i < 22; i++)
    {
        if(properties[i].hasOwner == 0)
        {
            continue;
        }

        if(properties[i].hotelCount > 0)
        {
            properties[i].buildingCondition[0] -= 2;

            if(properties[i].buildingCondition[0] < 0)
            {
                properties[i].buildingCondition[0] = 0;
            }
        }
        else
        {
            for(j = 0; j < properties[i].houseCount; j++)
            {
                properties[i].buildingCondition[j] -= 2;

                if(properties[i].buildingCondition[j] < 0)
                {
                    properties[i].buildingCondition[j] = 0;
                }
            }
        }
    }
}

void updatePropertyDepreciation()
{
    int i;
    int oldDepreciation;
    int newDepreciation;

    for(i = 0; i < 22; i++)
    {
        if(properties[i].hasOwner == 0)
        {
            continue;
        }

        /* Property age increases every complete Game Round */
        properties[i].propertyAge++;

        /*
         * Depreciation starts only after the property
         * becomes older than 50 rounds.
         */
        if(properties[i].propertyAge > 50)
        {
            /*
             * Apply 1% depreciation every 5 rounds
             * after the first 50 rounds.
             */
            if((properties[i].propertyAge - 50) % 5 == 0)
            {
                oldDepreciation =
                    properties[i].depreciationPercent;

                /*
                 * Maximum depreciation is 30%.
                 */
                if(oldDepreciation < 30)
                {
                    newDepreciation =
                        oldDepreciation + 1;

                    if(newDepreciation > 30)
                    {
                        newDepreciation = 30;
                    }

                    /*
                     * Convert the current depreciated value
                     * to the new depreciation level.
                     *
                     * Example:
                     * 0% -> 1%
                     * 1% -> 2%
                     * 2% -> 3%
                     */
                    properties[i].currentPrice =
                        properties[i].currentPrice *
                        (100 - newDepreciation) /
                        (100 - oldDepreciation);

                    properties[i].depreciationPercent =
                        newDepreciation;

                    printf("\nProperty Depreciation\n");

                    printf("%s has depreciated by %d%%.\n",
                           properties[i].name,
                           newDepreciation);

                    printf("Current Value : LKR %d\n",
                           properties[i].currentPrice);
                }
            }
        }
    }
}

void maintainBuildings(int playerID)
{
    int i;
    int j;
    int maintenanceCost;
    int averageCondition;

    for(i = 0; i < 22; i++)
    {
        /* Check whether this property belongs to the player */
        if(properties[i].owner != players[playerID].playerID)
        {
            continue;
        }
        if(properties[i].isStructurallyDamaged)
    {
        if(shouldRenovateDamagedBuilding(playerID))
        {
            renovateDamagedBuilding(i, playerID);
        }
    }
        /* ==================== HOUSES ==================== */

        for(j = 0; j < properties[i].houseCount; j++)
        {
            /* No maintenance needed */
            if(properties[i].buildingCondition[j] >= 100)
            {
                continue;
            }

            /* Check player's strategy */
            if(!shouldMaintainBuilding(
                   playerID,
                   properties[i].buildingCondition[j]))
            {
                continue;
            }

            /* House maintenance = 5% of construction cost */
            maintenanceCost =
                properties[i].houseConstructionCost * 5 / 100;

            /* Structural damage increases maintenance cost by 50% */
            if(properties[i].isStructurallyDamaged)
            {
                maintenanceCost =
                    maintenanceCost * 150 / 100;
            }

            /* Check whether player has enough money */
            if(players[playerID].money >= maintenanceCost)
            {
                players[playerID].money -= maintenanceCost;

                properties[i].buildingCondition[j] = 100;

                printf("%s maintained a house on %s.\n",
                       players[playerID].name,
                       properties[i].name);

                printf("Maintenance Cost : LKR %d\n",
                       maintenanceCost);
            }
        }

        /* ==================== HOTEL ==================== */

        if(properties[i].hotelCount > 0)
        {
            /* No maintenance needed */
            if(properties[i].buildingCondition[0] < 100)
            {
                /* Check player's strategy */
                if(shouldMaintainBuilding(
                       playerID,
                       properties[i].buildingCondition[0]))
                {
                    /* Hotel maintenance = 8% of construction cost */
                    maintenanceCost =
                        properties[i].hotelConstructionCost * 8 / 100;

                    /* Structural damage increases maintenance cost by 50% */
                    if(properties[i].isStructurallyDamaged)
                    {
                        maintenanceCost =
                            maintenanceCost * 150 / 100;
                    }

                    /* Check whether player has enough money */
                    if(players[playerID].money >= maintenanceCost)
                    {
                        players[playerID].money -= maintenanceCost;

                        properties[i].buildingCondition[0] = 100;

                        printf("%s maintained the hotel on %s.\n",
                               players[playerID].name,
                               properties[i].name);

                        printf("Maintenance Cost : LKR %d\n",
                               maintenanceCost);
                    }
                }
            }
        }

        /* ==================== RESET IGNORED ROUNDS ==================== */

        averageCondition =
            calculateAverageBuildingCondition(i);

        /*
         * If all buildings are fully maintained,
         * the consecutive maintenance-ignore period ends.
         */
        if(averageCondition == 100)
        {
            properties[i].maintenanceIgnoredRounds = 0;
        }
    }
}

int shouldMaintainBuilding(int playerID, int condition)
{
    switch(players[playerID].playerID)
    {
        case aggresiveInvestor:

            if(condition < 75)
            {
                return 1;
            }

            break;

        case conservativeBanker:

            if(condition < 90)
            {
                return 1;
            }

            break;

        case riskTaker:

            if(condition < 25)
            {
                return 1;
            }

            break;

        case opportunisticTrader:

            if(condition < 75)
            {
                return 1;
            }

            break;
    }

    return 0;
}

int shouldRenovateDamagedBuilding(int playerID)
{
    switch(players[playerID].playerID)
    {
        case aggresiveInvestor:
            return 1;

        case conservativeBanker:
            return 1;

        case riskTaker:
            return 1;

        case opportunisticTrader:
            return 1;
    }

    return 0;
}

void updateMaintenanceDamage()
{
    int i;
    int averageCondition;

    for(i = 0; i < 22; i++)
    {
        /* Ignore properties without owners */
        if(properties[i].owner == -1)
        {
            continue;
        }

        /* Ignore properties without buildings */
        if(properties[i].houseCount == 0 &&
           properties[i].hotelCount == 0)
        {
            properties[i].maintenanceIgnoredRounds = 0;
            continue;
        }

        /* Calculate average condition of buildings */
        averageCondition =
            calculateAverageBuildingCondition(i);

        /*
         * If all buildings are at 100%, maintenance is not
         * being ignored, so reset the consecutive counter.
         */
        if(averageCondition == 100)
        {
            properties[i].maintenanceIgnoredRounds = 0;
        }
        else
        {
            /*
             * At least one building is below 100%, therefore
             * maintenance is being ignored.
             */
            properties[i].maintenanceIgnoredRounds++;
        }

        /*
         * Structural damage occurs after more than
         * 20 consecutive rounds without maintenance.
         */
        if(properties[i].maintenanceIgnoredRounds >= 21 &&
           properties[i].isStructurallyDamaged == 0)
        {
            properties[i].isStructurallyDamaged = 1;

            properties[i].currentPrice =
                properties[i].currentPrice * 85 / 100;

            printf("\nSTRUCTURAL DAMAGE\n");

            printf("%s has suffered structural damage.\n",
                   properties[i].name);

            printf("Property value reduced by 15%%.\n");
            printf("Maximum rent reduced by 25%%.\n");
            printf("Future maintenance costs increased by 50%%.\n\n");
        }
    }
}

void renovateDamagedBuilding(int propertyIndex, int playerID)
{
    int replacementValue;
    int renovationCost;
    int i;

    if(properties[propertyIndex].owner != players[playerID].playerID)
    {
        return;
    }

    if(properties[propertyIndex].isStructurallyDamaged == 0)
    {
        return;
    }

    /*
     * Calculate replacement value of the current buildings.
     */
    if(properties[propertyIndex].hotelCount > 0)
    {
        replacementValue =
            properties[propertyIndex].hotelConstructionCost;
    }
    else
    {
        replacementValue =
            properties[propertyIndex].houseConstructionCost *
            properties[propertyIndex].houseCount;
    }

    /*
     * Structural renovation costs 25% of replacement value.
     */
    renovationCost =
        replacementValue * 25 / 100;

    if(players[playerID].money < renovationCost)
    {
        return;
    }

    players[playerID].money -= renovationCost;

    /*
     * Restore the 15% property-value reduction.
     */
    properties[propertyIndex].currentPrice =
        properties[propertyIndex].currentPrice * 100 / 85;

    /*
     * Restore the 25% structural-rent reduction.
     *
     * currentRent was not permanently reduced when
     * structural damage occurred, so no direct rent
     * restoration is required here.
     */

    /*
     * Remove structural damage.
     */
    properties[propertyIndex].isStructurallyDamaged = 0;

    /*
     * Reset maintenance-ignore counter.
     */
    properties[propertyIndex].maintenanceIgnoredRounds = 0;

    /*
     * Restore all building conditions.
     */
    for(i = 0; i < properties[propertyIndex].houseCount; i++)
    {
        properties[propertyIndex].buildingCondition[i] = 100;
    }

    if(properties[propertyIndex].hotelCount > 0)
    {
        properties[propertyIndex].buildingCondition[0] = 100;
    }

    printf("\nStructural Renovation\n");

    printf("%s renovated %s.\n",
           players[playerID].name,
           properties[propertyIndex].name);

    printf("Renovation Cost : LKR %d\n",
           renovationCost);

    printf("Property value restored.\n");
    printf("Rental value restored.\n");
    printf("Building condition restored to 100%%.\n\n");
}

int shouldRenovateProperty(int playerID, int depreciation)
{
    switch(players[playerID].playerID)
    {
        case aggresiveInvestor:

            if(depreciation > 0)
            {
                return 1;
            }

            break;

        case conservativeBanker:

            if(depreciation > 10)
            {
                return 1;
            }

            break;

        case riskTaker:

            if(depreciation >= 30)
            {
                return 1;
            }

            break;

        case opportunisticTrader:

            if(depreciation > 15)
            {
                return 1;
            }

            break;
    }

    return 0;
}

int calculateNetWorth(int playerID)
{
    int netWorth = 0;
    int propertyValue = 0;
    int buildingValue = 0;
    int railwayValue = 0;
    int utilityValue = 0;
    int propertyIndex;
    int i;

    /*
     * Cash
     */
    netWorth = players[playerID].money;

    /*
     * Property values and building values
     */
    for(i = 0; i < 22; i++)
    {
        if(properties[i].owner == players[playerID].playerID)
        {
            /*
             * Current property market value
             */
            propertyValue += properties[i].currentPrice;

            /*
             * Houses
             */
            if(properties[i].houseCount > 0)
            {
                buildingValue +=
                    properties[i].houseCount *
                    properties[i].houseConstructionCost;
            }

            /*
             * Hotel
             */
            if(properties[i].hotelCount > 0)
            {
                buildingValue +=
                    properties[i].hotelCount *
                    properties[i].hotelConstructionCost;
            }
        }
    }

    /*
     * Railway values
     */
    for(i = 0; i < 4; i++)
    {
        if(railways[i].owner == players[playerID].playerID)
        {
            railwayValue += railways[i].currentPrice;
        }
    }

    /*
     * Utility values
     */
    for(i = 0; i < 2; i++)
    {
        if(utilities[i].owner == players[playerID].playerID)
        {
            utilityValue += utilities[i].currentPrice;
        }
    }

    /*
     * Add all assets
     */
    netWorth += propertyValue;
    netWorth += buildingValue;
    netWorth += railwayValue;
    netWorth += utilityValue;

    /*
     * Outstanding loan.
     *
     * currentLoan already includes accumulated interest
     * because updateLoanInterest() adds interest to currentLoan.
     */
    netWorth -= players[playerID].currentLoan;

    return netWorth;
}

int purchaseInsurance(int playerID, int propertyIndex, int policyType)
{
    int premium;

    if(properties[propertyIndex].owner != players[playerID].playerID)
    {
        return 0;
    }

    if(policyType < 0 || policyType > 2)
    {
        return 0;
    }

    /*
     * Business Interruption Insurance is only
     * applicable to properties containing hotels.
     */
    if(policyType == BusinessInterruptionInsurance &&
       properties[propertyIndex].hotelCount == 0)
    {
        return 0;
    }

    premium =
        properties[propertyIndex].currentPrice *
        insurance[policyType].installment_percentage / 100;

    if(players[playerID].money < premium)
    {
        printf("%s does not have enough money to purchase insurance for %s.\n\n",
               players[playerID].name,
               properties[propertyIndex].name);

        return 0;
    }

    players[playerID].money -= premium;

    properties[propertyIndex].isInsured = 1;

    properties[propertyIndex].insurancePolicyType =
        policyType;

    properties[propertyIndex].insuranceExpiryRound =
        gameInfo.gameRound + 20;

    printf("\nInsurance Purchased\n");
    printf("%s purchased insurance for %s.\n",
           players[playerID].name,
           properties[propertyIndex].name);

    if(policyType == basicPropertyInsurance)
    {
        printf("Policy : Basic Property Insurance\n");
    }
    else if(policyType == comprehensiveInsurance)
    {
        printf("Policy : Comprehensive Insurance\n");
    }
    else
    {
        printf("Policy : Business Interruption Insurance\n");
    }

    printf("Premium : LKR %d\n", premium);
    printf("Valid for : 20 rounds\n");
    printf("Expiry Round : %d\n\n",
           properties[propertyIndex].insuranceExpiryRound);

    return 1;
}

void updateInsurancePolicies(void)
{
    int i;
    int remainingRounds;

    for(i = 0; i < 22; i++)
    {
        if(properties[i].isInsured == 0)
        {
            continue;
        }

        remainingRounds =
            properties[i].insuranceExpiryRound -
            gameInfo.gameRound;

        /*
         * Three-round expiry warning.
         */
        if(remainingRounds == 3)
        {
            printf("\nInsurance Expiry Warning\n");

            printf("Insurance policy on %s expires in 3 rounds.\n\n",
                   properties[i].name);
        }

        /*
         * Policy expires after 20 rounds.
         */
        if(gameInfo.gameRound >=
           properties[i].insuranceExpiryRound)
        {
            printf("\nInsurance Expired\n");

            printf("Insurance policy on %s has expired.\n\n",
                   properties[i].name);

            properties[i].isInsured = 0;
            properties[i].insurancePolicyType = -1;
            properties[i].insuranceExpiryRound = 0;
        }
    }
}

int calculateInsuranceCompensation(int propertyIndex, int disaster)
{
    int policyType;
    int repairCost;
    int compensation;

    if(properties[propertyIndex].isInsured == 0)
    {
        return 0;
    }

    policyType =
        properties[propertyIndex].insurancePolicyType;

    if(isDisasterCovered(propertyIndex, disaster) == 0)
    {
        return 0;
    }

    repairCost =
        properties[propertyIndex].disasterRepairCost;

    if(policyType == basicPropertyInsurance)
    {
        compensation =
            repairCost * 80 / 100;
    }
    else if(policyType == comprehensiveInsurance)
    {
        compensation =
            repairCost;
    }
    else if(policyType == BusinessInterruptionInsurance)
    {
        compensation =
            repairCost +
            properties[propertyIndex].currentRent * 5;
    }
    else
    {
        compensation = 0;
    }

    return compensation;
}

int isDisasterCovered(int propertyIndex, int disaster)
{
    int policyType;

    if(properties[propertyIndex].isInsured == 0)
    {
        return 0;
    }

    policyType =
        properties[propertyIndex].insurancePolicyType;

    if(policyType == basicPropertyInsurance)
    {
        if(disaster == fire ||
           disaster == flood)
        {
            return 1;
        }
    }

    if(policyType == comprehensiveInsurance)
    {
        if(disaster == fire ||
           disaster == flood ||
           disaster == riot ||
           disaster == vandalism)
        {
            return 1;
        }
    }

    if(policyType == BusinessInterruptionInsurance)
    {
        /*
         * Business Interruption Insurance is intended
         * for properties containing hotels.
         */
        if(properties[propertyIndex].hotelCount > 0)
        {
            return 1;
        }
    }

    return 0;
}



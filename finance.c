#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "finance.h"
#include "players.h"
#include "events.h"

struct rate rates = {8, 15};

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
        {fire, flood, riot, buildingCollapse, electricalFailure, vandalism, earthquake},
        15,
        100
    }
};


//Loan Functions
int calculateMaximumLoan(int playerId)
{
    int maximumLoan = 0;
    int loanValue;

    players[playerId].obtainableMaximumLoan = 0;

    int c = 0;
    while(c < 22)
    {
        if(properties[c].hasOwner && properties[c].isMortgaged == 0 &&
           properties[c].isClosed == 0 && properties[c].owner == players[playerId].playerID)
        {
            loanValue = (properties[c].mortgagedValue * 75) / 100;
            maximumLoan += loanValue;
        }
        c++;
    }

    c = 0;
    while(c < 4)
    {
        if(railways[c].hasOwner && railways[c].isMortgaged == 0 && railways[c].owner == players[playerId].playerID)
        {
            loanValue = (railways[c].mortgageValue * 75) / 100;
            maximumLoan += loanValue;
        }

        c++;
    }

    c = 0;
    while(c < 2)
    {
        if(utilities[c].hasOwner && utilities[c].isMortgaged == 0 && utilities[c].owner == players[playerId].playerID)
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
        if(properties[i].hasOwner && properties[i].isMortgaged == 0 && properties[i].isClosed == 0 && 
           properties[i].isLoanLocked == 0 && properties[i].owner == players[playerID].playerID)
        {
            properties[i].isLoanLocked = 1;
        }
    }

    for(i = 0; i < 4; i++)
    {
        if(railways[i].hasOwner && railways[i].isMortgaged == 0 &&
           railways[i].isLoanLocked == 0 && railways[i].owner == players[playerID].playerID)
        {
            railways[i].isLoanLocked = 1;
        }
    }

    for(i = 0; i < 2; i++)
    {
        if(utilities[i].hasOwner && utilities[i].isMortgaged == 0 &&
           utilities[i].isLoanLocked == 0 && utilities[i].owner == players[playerID].playerID)
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
        printf("%s is not at the Bank. Cannot obtain a loan here.\n\n", players[playerID].name);
        return;
    }

    if(players[playerID].hasLoan == 1)
    {
        printf("%s already has an active loan.\n\n", players[playerID].name);

        return;
    }

    loanAmount = calculateMaximumLoan(playerID);

    if(loanAmount <= 0)
    {
        printf("%s does not have sufficient collateral for a loan.\n\n", players[playerID].name);
        return;
    }

    players[playerID].money += loanAmount;

    players[playerID].currentLoan = loanAmount;

    players[playerID].hasLoan = 1;

    players[playerID].loanRound = 0;

    players[playerID].loanInterestRate = rates.interestRate;

    players[playerID].obtainableMaximumLoan = 0;

    lockLoanCollateral(playerID);

    printf("%s has obtained a secured loan.\n\n", players[playerID].name);

    printf("Loan Amount : LKR %d\n", loanAmount);

    printf("Interest Rate : %d%%\n", rates.interestRate);

    printf("Duration : 20 rounds\n\n");
}

void updateLoanInterest(int playerID)
{
    int interestRate;

    if(players[playerID].hasLoan == 1)
    {
        interestRate = players[playerID].loanInterestRate;

        if(eventCardData[playerID].isActive[7] == 1)
        {
            interestRate -= 2;
        }

        if(eventCardData[playerID].isActive[8] == 1)
        {
            interestRate += 3;
        }

        if(interestRate < 0)
        {
            interestRate = 0;
        }

        players[playerID].currentLoan = players[playerID].currentLoan + (players[playerID].currentLoan * interestRate / 100);

        players[playerID].loanRound++;

        printf("%s loan interest accumulated.\n", players[playerID].name);

        printf("Interest Rate : %d%%\n", interestRate);

        printf("Outstanding Loan : LKR %d\n", players[playerID].currentLoan);

        printf("Loan Round : %d / 20\n\n", players[playerID].loanRound);
    }
}

void propertyForeclose(int playerID)
{
    int i;
    int j;
    int k;

    int foreclosedProperties[22];
    int foreclosedRailways[4];
    int foreclosedUtilities[2];

    int foreclosedPropertyCount = 0;
    int foreclosedRailwayCount = 0;
    int foreclosedUtilityCount = 0;


    if(players[playerID].hasLoan == 1 && players[playerID].loanRound >= 20)
    {
        printf("\n%s has defaulted on the loan.\n", players[playerID].name);


        for(i = 0; i < 22; i++)
        {
            if(properties[i].owner == players[playerID].playerID &&
               properties[i].isLoanLocked == 1)
            {
                foreclosedProperties[foreclosedPropertyCount] = i;
                foreclosedPropertyCount++;

                properties[i].hasOwner = 0;
                properties[i].owner = -1;
                properties[i].isLoanLocked = 0;
                properties[i].isMortgaged = 0;
                properties[i].houseCount = 0;
                properties[i].hotelCount = 0;
                properties[i].isInsured = 0;
                properties[i].isClosed = 0;


                for(j = 0; j < players[playerID].ownedPropertiesCount; j++)
                {
                    if(players[playerID].ownedProperties[j] == properties[i].squareNumber)
                    {
                        for(k = j; k < players[playerID].ownedPropertiesCount - 1; k++)
                        {
                            players[playerID].ownedProperties[k] = players[playerID].ownedProperties[k + 1];
                        }

                        players[playerID].ownedPropertiesCount--;

                        players[playerID].ownedProperties[players[playerID].ownedPropertiesCount] = -1;

                        break;
                    }
                }
            }
        }


        for(i = 0; i < 4; i++)
        {
            if(railways[i].owner == players[playerID].playerID && railways[i].isLoanLocked == 1)
            {
                foreclosedRailways[foreclosedRailwayCount] = i;
                foreclosedRailwayCount++;
                railways[i].hasOwner = 0;
                railways[i].owner = -1;
                railways[i].isLoanLocked = 0;
                railways[i].isMortgaged = 0;
                railways[i].currentRent = 250;

                for(j = 0; j < players[playerID].ownedRailwayCount; j++)
                {
                    if(players[playerID].ownedRailways[j] == railways[i].squareNumber)
                    {
                        for(k = j; k < players[playerID].ownedRailwayCount - 1; k++)
                        {
                            players[playerID].ownedRailways[k] = players[playerID].ownedRailways[k + 1];
                        }

                        players[playerID].ownedRailwayCount--;

                        players[playerID].ownedRailways[players[playerID].ownedRailwayCount] = -1;

                        break;
                    }
                }
            }
        }

        for(i = 0; i < 2; i++)
        {
            if(utilities[i].owner == players[playerID].playerID && utilities[i].isLoanLocked == 1)
            {
                foreclosedUtilities[foreclosedUtilityCount] = i;
                foreclosedUtilityCount++;

                utilities[i].hasOwner = 0;
                utilities[i].owner = -1;
                utilities[i].isLoanLocked = 0;
                utilities[i].isMortgaged = 0;
                utilities[i].currentRent = 0;


                for(j = 0; j < players[playerID].ownedUtilitiesCount; j++)
                {
                    if(players[playerID].ownedUtilities[j] == utilities[i].squareNumber)
                    {
                        for(k = j; k < players[playerID].ownedUtilitiesCount - 1; k++)
                        {
                            players[playerID].ownedUtilities[k] = players[playerID].ownedUtilities[k + 1];
                        }

                        players[playerID].ownedUtilitiesCount--;

                        players[playerID].ownedUtilities[players[playerID].ownedUtilitiesCount] = -1;

                        break;
                    }
                }
            }
        }

        players[playerID].currentLoan = 0;
        players[playerID].hasLoan = 0;
        players[playerID].loanRound = 0;
        players[playerID].loanInterestRate = 0;
        players[playerID].obtainableMaximumLoan = 0;


        printf("Collateral has been foreclosed.\n");
        printf("Outstanding debt has been cleared.\n\n");

        for(i = 0; i < foreclosedPropertyCount; i++)
        {
            printf("Foreclosed property is entering auction.\n");
            auctionProperty(foreclosedProperties[i]);
        }


        for(i = 0; i < foreclosedRailwayCount; i++)
        {
            printf("Foreclosed railway is entering auction.\n");
            auctionRailway(foreclosedRailways[i]);
        }


        for(i = 0; i < foreclosedUtilityCount; i++)
        {
            printf("Foreclosed utility is entering auction.\n");
            auctionUtility(foreclosedUtilities[i]);
        }


        if(players[playerID].money <= 0 &&
           players[playerID].ownedPropertiesCount == 0 &&
           players[playerID].ownedRailwayCount == 0 &&
           players[playerID].ownedUtilitiesCount == 0)
        {
            printf("%s has no remaining assets after foreclosure.\n", players[playerID].name);

            printf("%s has been declared bankrupt.\n\n", players[playerID].name);
            players[playerID].isBankrupt = 1;
        }
    }
}

void repayFullLoan(int playerID)
{
    if(board[players[playerID].currentPosition].type != Bank)
    {
        printf("%s is not at the Bank.\n\n",players[playerID].name);

        return;
    }

    if(players[playerID].hasLoan == 0)
    {
        printf("%s does not have an active loan.\n\n", players[playerID].name);

        return;
    }

    if(players[playerID].money < players[playerID].currentLoan)
    {
        printf("%s does not have enough money to repay the full loan.\n\n", players[playerID].name);

        return;
    }

    players[playerID].money -= players[playerID].currentLoan;

    printf("%s repaid the full loan of LKR %d.\n", players[playerID].name, players[playerID].currentLoan);

    players[playerID].currentLoan = 0;
    players[playerID].hasLoan = 0;
    players[playerID].loanRound = 0;
    players[playerID].loanInterestRate = 0;
    players[playerID].obtainableMaximumLoan = 0;

    unlockLoanCollateral(playerID);

    printf("%s has fully repaid the loan.\n", players[playerID].name);

    printf("Loan collateral has been unlocked.\n\n");
}

void repayPartofLoan(int playerID, int amount)
{
    if(board[players[playerID].currentPosition].type != Bank)
    {
        printf("%s is not at the Bank.\n\n",players[playerID].name);
        return;
    }

    if(players[playerID].hasLoan == 0)
    {
        printf("%s does not have an active loan.\n\n",players[playerID].name);
        return;
    }

    if(amount <= 0)
    {
        printf("Invalid repayment amount.\n\n");
        return;
    }

    if(amount > players[playerID].money)
    {
        printf("%s does not have enough money to repay LKR %d.\n\n", players[playerID].name, amount);

        return;
    }

    if(amount > players[playerID].currentLoan)
    {
        amount = players[playerID].currentLoan;
    }

    players[playerID].money -= amount;

    players[playerID].currentLoan -= amount;

    printf("%s paid LKR %d of the loan.\n", players[playerID].name, amount);

    printf("Outstanding Loan : LKR %d\n\n", players[playerID].currentLoan);

    if(players[playerID].currentLoan == 0)
    {
        players[playerID].hasLoan = 0;
        players[playerID].loanRound = 0;
        players[playerID].loanInterestRate = 0;
        players[playerID].obtainableMaximumLoan = 0;

        unlockLoanCollateral(playerID);

        printf("%s has fully repaid the loan.\n",players[playerID].name);

        printf("Loan collateral has been unlocked.\n\n");
    }
}

void increaseLoan(int playerID, int amount)
{
    int maximumLoan;
    int maximumAdditionalLoan;

    if(board[players[playerID].currentPosition].type != Bank)
    {
        printf("%s is not at the Bank.\n\n", players[playerID].name);
        return;
    }

    if(players[playerID].hasLoan == 0)
    {
        printf("%s does not have an active loan.\n\n", players[playerID].name);
        return;
    }

    if(amount <= 0)
    {
        printf("Invalid loan increase amount.\n\n");
        return;
    }

    maximumLoan = calculateMaximumLoan(playerID);
    maximumAdditionalLoan = maximumLoan - players[playerID].currentLoan;

    if(maximumAdditionalLoan <= 0)
    {
        printf("%s cannot increase the loan.\n", players[playerID].name);

        printf("Current Loan : LKR %d\n", players[playerID].currentLoan);

        printf("Maximum Loan : LKR %d\n\n",maximumLoan);

        return;
    }

    if(amount > maximumAdditionalLoan)
    {
        printf("%s can only increase the loan by LKR %d.\n", players[playerID].name, maximumAdditionalLoan);
        amount = maximumAdditionalLoan;
    }

    players[playerID].money += amount;
    players[playerID].currentLoan += amount;
    players[playerID].obtainableMaximumLoan = 0;

    lockLoanCollateral(playerID);

    printf("%s increased the loan by LKR %d.\n", players[playerID].name, amount);

    printf("Total Outstanding Loan : LKR %d\n", players[playerID].currentLoan);

    printf("Interest Rate : %d%%\n", players[playerID].loanInterestRate);

    printf("Loan Round : %d / 20\n", players[playerID].loanRound);

    printf("Remaining Cash : LKR %d\n\n", players[playerID].money);
}



//insurance functions
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

    //no hotel means cant get business interruption insurance
    if(policyType == BusinessInterruptionInsurance && properties[propertyIndex].hotelCount == 0)
    {
        return 0;
    }

    premium = properties[propertyIndex].currentPrice * insurance[policyType].installment_percentage / 100;

    if(gameInfo.currentGovernmentRegulation == 7)
    {
        premium = premium * 85 / 100;
    }

    if(eventCardData[playerID].isActive[15] == 1)
    {
        premium = premium * 80 / 100;
    }

    if(players[playerID].money < premium)
    {
        printf("%s does not have enough money to purchase insurance for %s.\n\n", players[playerID].name, properties[propertyIndex].name);
        return 0;
    }

    players[playerID].money -= premium;
    properties[propertyIndex].isInsured = 1;
    properties[propertyIndex].insurancePolicyType =policyType;
    properties[propertyIndex].insuranceExpiryRound = gameInfo.gameRound + 20;

    printf("\nInsurance Purchased\n");

    printf("%s purchased insurance for %s.\n", players[playerID].name, properties[propertyIndex].name);

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
    printf("Expiry Round : %d\n\n", properties[propertyIndex].insuranceExpiryRound);
    return 1;
}

void updateInsurancePolicies()
{   
    //assume that insuarance updates with game rounds
    int i;
    int remainingRounds;

    for(i = 0; i < 22; i++)
    {
        if(properties[i].isInsured == 0)
        {
            continue;
        }

        remainingRounds = properties[i].insuranceExpiryRound - gameInfo.gameRound;

        if(remainingRounds == 3)
        {
            printf("\nInsurance Expiry Warning\n");
            printf("Insurance policy on %s expires in 3 rounds.\n\n", properties[i].name);
        }

        if(gameInfo.gameRound >= properties[i].insuranceExpiryRound)
        {
            printf("\nInsurance Expired\n");
            printf("Insurance policy on %s has expired.\n\n", properties[i].name);

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

    policyType = properties[propertyIndex].insurancePolicyType;

    if(isDisasterCovered(propertyIndex, disaster) == 0)
    {
        return 0;
    }

    repairCost = properties[propertyIndex].disasterRepairCost;

    if(policyType == basicPropertyInsurance)
    {
        compensation = repairCost * 80 / 100;
    }
    
    else if(policyType == comprehensiveInsurance)
    {
        compensation = repairCost;
    }

    else if(policyType == BusinessInterruptionInsurance)
    {
        compensation = repairCost +  properties[propertyIndex].currentRent * 5;
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

    policyType = properties[propertyIndex].insurancePolicyType;

    if(policyType == basicPropertyInsurance)
    {
        if(disaster == fire || disaster == flood)
        {
            return 1;
        }
    }

    if(policyType == comprehensiveInsurance)
    {
        if(disaster == fire || disaster == flood || disaster == riot || disaster == vandalism)
        {
            return 1;
        }
    }

    if(policyType == BusinessInterruptionInsurance)
    {
        if(properties[propertyIndex].hotelCount > 0)
        {
            return 1;
        }
    }

    return 0;
}

int claimInsurance(int propertyIndex)
{
    int owner;
    int repairCost;
    int compensation = 0;

    owner = properties[propertyIndex].owner;
    repairCost = properties[propertyIndex].disasterRepairCost;

    if(properties[propertyIndex].isInsured == 0)
    {
        printf("Property is not insured.\n");
        printf("No insurance compensation received.\n");

        return 0;
    }

    switch(properties[propertyIndex].insurancePolicyType)
    {
        case basicPropertyInsurance:

            if(properties[propertyIndex].disasterType == fire || properties[propertyIndex].disasterType == flood)
            {
                compensation = repairCost * 80 / 100;

                printf("Insurance Claim Approved.\n");
                printf("Compensation : LKR %d\n", compensation);

                players[owner].money += compensation;

                return compensation;
            }

            break;

        case comprehensiveInsurance:

            if(properties[propertyIndex].disasterType == fire ||
               properties[propertyIndex].disasterType == flood ||
               properties[propertyIndex].disasterType == riot ||
               properties[propertyIndex].disasterType == vandalism ||
               properties[propertyIndex].disasterType == earthquake)
            {
                compensation = repairCost;

                printf("Insurance Claim Approved.\n");
                printf("Compensation : LKR %d\n", compensation);

                players[owner].money += compensation;

                return compensation;
            }

            break;

 
        case BusinessInterruptionInsurance:


            if(properties[propertyIndex].hotelCount > 0)
            {
                compensation = repairCost;

                printf("Insurance Claim Approved.\n");
                printf("Repair Compensation : LKR %d\n",compensation);

                players[owner].money += compensation;

                return compensation;
            }

            break;
    }

    printf("Insurance Claim Rejected.\n");
    printf("Disaster is not covered by the insurance policy.\n");

    return 0;
}


//bankrupt
 
void playerBankrupt(int playerID, int *bankruptedPlayerCount) 
{ 
    int i; 
    int j;   
    int totalAssets = 0; 
    int totalLiabilities = 0; 
    int propertyIndex; 
 
    totalAssets = players[playerID].money; 
 
    for(i = 0; i < players[playerID].ownedPropertiesCount; i++) 
    { 
        propertyIndex = -1; 
 
        for(j = 0; j < 22; j++) 
        { 
            if(properties[j].squareNumber == players[playerID].ownedProperties[i]) 
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
 
    for(i = 0; i < 4; i++) 
    { 
        if(railways[i].owner == players[playerID].playerID) 
        { 
            totalAssets += railways[i].currentPrice; 
        } 
    } 
 
    for(i = 0; i < 2; i++) 
    { 
        if(utilities[i].owner == players[playerID].playerID) 
        { 
            totalAssets += utilities[i].currentPrice; 
        } 
    } 
 
    totalLiabilities = players[playerID].currentLoan + players[playerID].luxuryPropertyTaxDue;
    for(i = 0; i < 40; i++) 
    { 
        totalLiabilities += players[playerID].paymentDebt[i]; 
    } 
 
    if(totalLiabilities <= totalAssets || players[playerID].isBankrupt) 
    { 
        return; 
    } 
 
    printf("%s has been declared bankrupt.\n", players[playerID].name); 
 
    printf("Remaining assets transferred to the Bank.\n\n"); 
 
    players[playerID].isBankrupt = 1; 
 
    for(i = 0; i < players[playerID].ownedPropertiesCount; i++) 
    { 
        propertyIndex = -1; 
 
        for(j = 0; j < 22; j++) 
        { 
            if(properties[j].squareNumber == players[playerID].ownedProperties[i]) 
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
            properties[propertyIndex].isInsured = 0; 
            properties[propertyIndex].houseCount = 0; 
            properties[propertyIndex].hotelCount = 0; 
        } 
 
        players[playerID].ownedProperties[i] = -1; 
    } 
 
    players[playerID].ownedPropertiesCount = 0; 
 
    for(i = 0; i < 4; i++) 
    { 
        if(railways[i].owner == players[playerID].playerID) 
        { 
            railways[i].owner = -1; 
            railways[i].hasOwner = 0; 
 
            railways[i].isMortgaged = 0; 
            railways[i].isLoanLocked = 0; 
 
            railways[i].currentRent = railways[i].baseRent; 
        } 
 
        players[playerID].ownedRailways[i] = -1; 
    } 
 
    players[playerID].ownedRailwayCount = 0; 
 
    for(i = 0; i < 2; i++) 
    { 
        if(utilities[i].owner == players[playerID].playerID) 
        { 
            utilities[i].owner = -1; 
            utilities[i].hasOwner = 0; 
            utilities[i].isMortgaged = 0; 
            utilities[i].isLoanLocked = 0; 
            utilities[i].currentRent = utilities[i].baseRent; 
        } 
 
        players[playerID].ownedUtilities[i] = -1; 
    } 
 
    players[playerID].ownedUtilitiesCount = 0; 
 
    players[playerID].hasLoan = 0; 
    players[playerID].currentLoan = 0; 
    players[playerID].loanRound = 0; 
    players[playerID].loanInterestRate = 0; 
    players[playerID].obtainableMaximumLoan = 0; 
 
    for(i = 0; i < 40; i++) 
    { 
        players[playerID].paymentDebt[i] = 0; 
    } 
 
    players[playerID].money = 0; 
 
    (*bankruptedPlayerCount)++; 
}


//tax functions

void payTax(int playerSquare, int k) 
{   
    //assuemed that income tax affected only for railway , utility and property rent and money each passing go and money earning through events
    int tax; 
    int totalDue;
    int paidAmount;
 
    if(playerSquare == 4) 
    { 
        if(players[k].taxableMoney <= 0) 
        { 
            printf("%s has no taxable income. No tax paid.\n\n",players[k].name); 
            return; 
        } 
 
        tax = players[k].taxableMoney * rates.incomeTaxRate / 100; 

        totalDue = players[k].paymentDebt[4] + tax;
 
        printf("%s must pay Income Tax : LKR %d\n", players[k].name, totalDue); 
 
        if(players[k].money >= totalDue) 
        { 
            players[k].money -= totalDue; 
            players[k].taxableMoney = 0; 
            players[k].paymentDebt[4] = 0;
            printf("Paid Tax : LKR %d\n\n", totalDue); 
        } 
        else 
        { 
            printf("%s does not have enough money to pay the tax.\n", players[k].name); 

            paidAmount = players[k].money;

            players[k].money = 0; 
            players[k].taxableMoney = 0; 
            players[k].paymentDebt[4] = totalDue - paidAmount;

            printf("Paid Tax : LKR %d\n", paidAmount); 
            printf("Remaining Tax Debt : LKR %d\n\n", players[k].paymentDebt[4]);
        } 
    } 
}

void communityDevelopmentFund(int playerID) 
{    
    printf("%s landed on Community Development Fund.\n",players[playerID].name); 
 
    int i; 
    int totalAssets = 0; 
    int tax; 
    int totalDue;
    int paidAmount;
 
    for(i = 0; i < 22; i++) 
    { 
        if(properties[i].hasOwner && 
           properties[i].owner == players[playerID].playerID) 
        { 
            totalAssets += properties[i].currentPrice; 
        } 
    } 
 
    for(i = 0; i < 4; i++) 
    { 
        if(railways[i].hasOwner && railways[i].owner == players[playerID].playerID) 
        { 
            totalAssets += railways[i].currentPrice; 
        } 
    } 
 
    for(i = 0; i < 2; i++) 
    { 
        if(utilities[i].hasOwner && utilities[i].owner == players[playerID].playerID) 
        { 
            totalAssets += utilities[i].currentPrice; 
        } 
    } 
 
    totalAssets += players[playerID].money; 
    tax = totalAssets * 10 / 100; 
 
    totalDue = players[playerID].paymentDebt[2] + tax;

    if(players[playerID].money >= totalDue) 
    { 
        players[playerID].money -= totalDue; 
        players[playerID].paymentDebt[2] = 0;

        printf("Total Property Assets : LKR %d\n",totalAssets); 
        printf("Community Development Fund Tax : LKR %d\n\n",totalDue); 
    } 
    else 
    { 
        printf("%s does not have enough money to pay the Community Development Fund.\n", players[playerID].name); 
 
        printf("Available Cash : LKR %d\n", players[playerID].money); 
 
        printf("Required Tax : LKR %d\n",totalDue); 
 
        paidAmount = players[playerID].money;

        players[playerID].money = 0; 
        players[playerID].paymentDebt[2] = totalDue - paidAmount;

        printf("Paid Tax : LKR %d\n", paidAmount);
        printf("Remaining Tax Debt : LKR %d\n\n", players[playerID].paymentDebt[2]);
    } 
}


//deprication and renovation functions

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
        properties[propertyIndex].currentPrice = properties[propertyIndex].currentPrice * 100 / (100 - properties[propertyIndex].depreciationPercent);
    }

    properties[propertyIndex].propertyAge = 0;
    properties[propertyIndex].depreciationPercent = 0;

    printf("%s renovated %s for LKR %d.\n",players[playerID].name,properties[propertyIndex].name,renovationCost);

    printf("Property depreciation restored.\n");
}
}

int calculateAverageBuildingCondition(int propertyIndex)
{   
    //Assumed that the  depreciation is calculated as average of all the building conditions in a property.
    int i;
    int totalCondition = 0;
    int buildingCount = 0;

    if(properties[propertyIndex].hotelCount > 0)
    {
        return properties[propertyIndex].buildingCondition[0];
    }

    for(i = 0; i < properties[propertyIndex].houseCount; i++)
    {
        totalCondition +=properties[propertyIndex].buildingCondition[i];
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
        properties[i].propertyAge++;

        if(properties[i].propertyAge > 50)
        {
            if((properties[i].propertyAge - 50) % 5 == 0)
            {
                oldDepreciation = properties[i].depreciationPercent;

                if(oldDepreciation < 30)
                {
                    newDepreciation = oldDepreciation + 1;

                    if(newDepreciation > 30)
                    {
                        newDepreciation = 30;
                    }

                    properties[i].currentPrice = properties[i].currentPrice * (100 - newDepreciation) / (100 - oldDepreciation);

                    properties[i].depreciationPercent = newDepreciation;

                    printf("\nProperty Depreciation\n");

                    printf("%s has depreciated by %d%%.\n", properties[i].name ,newDepreciation);

                    printf("Current Value : LKR %d\n", properties[i].currentPrice);
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

        for(j = 0; j < properties[i].houseCount; j++)
        {
            if(properties[i].buildingCondition[j] >= 100)
            {
                continue;
            }

            if(!shouldMaintainBuilding(
                   playerID,
                   properties[i].buildingCondition[j]))
            {
                continue;
            }

            maintenanceCost = properties[i].houseConstructionCost * 5 / 100;

            if(properties[i].isStructurallyDamaged)
            {
                maintenanceCost = maintenanceCost * 150 / 100;
            }

            if(players[playerID].money >= maintenanceCost)
            {
                players[playerID].money -= maintenanceCost;

                properties[i].buildingCondition[j] = 100;

                printf("%s maintained a house on %s.\n", players[playerID].name,properties[i].name);

                printf("Maintenance Cost : LKR %d\n", maintenanceCost);
            }
        }

        if(properties[i].hotelCount > 0)
        {
            if(properties[i].buildingCondition[0] < 100)
            {
                if(shouldMaintainBuilding( playerID, properties[i].buildingCondition[0]))
                {
                    maintenanceCost = properties[i].hotelConstructionCost * 8 / 100;
                    if(properties[i].isStructurallyDamaged)
                    {
                        maintenanceCost = maintenanceCost * 150 / 100;
                    }

                    if(players[playerID].money >= maintenanceCost)
                    {
                        players[playerID].money -= maintenanceCost;

                        properties[i].buildingCondition[0] = 100;

                        printf("%s maintained the hotel on %s.\n", players[playerID].name, properties[i].name);

                        printf("Maintenance Cost : LKR %d\n", maintenanceCost);
                    }
                }
            }
        }
        averageCondition = calculateAverageBuildingCondition(i);

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
        //not mentioned exact persentage there fore assumed 75% for aggressive investor to maintain the building
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

            if(condition < 85)
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
        if(properties[i].owner == -1)
        {
            continue;
        }

        if(properties[i].houseCount == 0 && properties[i].hotelCount == 0)
        {
            properties[i].maintenanceIgnoredRounds = 0;
            continue;
        }

        averageCondition = calculateAverageBuildingCondition(i);

        if(averageCondition == 100)
        {
            properties[i].maintenanceIgnoredRounds = 0;
        }
        else
        {

            properties[i].maintenanceIgnoredRounds++;
        }


        if(properties[i].maintenanceIgnoredRounds >= 21 && properties[i].isStructurallyDamaged == 0)
        {
            properties[i].isStructurallyDamaged = 1;

            properties[i].currentPrice = properties[i].currentPrice * 85 / 100;

            printf("\nSTRUCTURAL DAMAGE\n");

            printf("%s has suffered structural damage.\n", properties[i].name);

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
    if(properties[propertyIndex].hotelCount > 0)
    {
        replacementValue =
            properties[propertyIndex].hotelConstructionCost;
    }
    else
    {
        replacementValue = properties[propertyIndex].houseConstructionCost * properties[propertyIndex].houseCount;
    }

    renovationCost = replacementValue * 25 / 100;

    if(players[playerID].money < renovationCost)
    {
        return;
    }

    players[playerID].money -= renovationCost;

    properties[propertyIndex].currentPrice = properties[propertyIndex].currentPrice * 100 / 85;

    properties[propertyIndex].isStructurallyDamaged = 0;

    properties[propertyIndex].maintenanceIgnoredRounds = 0;

    for(i = 0; i < properties[propertyIndex].houseCount; i++)
    {
        properties[propertyIndex].buildingCondition[i] = 100;
    }

    if(properties[propertyIndex].hotelCount > 0)
    {
        properties[propertyIndex].buildingCondition[0] = 100;
    }

    printf("\nStructural Renovation\n");

    printf("%s renovated %s.\n", players[playerID].name, properties[propertyIndex].name);

    printf("Renovation Cost : LKR %d\n", renovationCost);

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


//net worth calculation function

int calculateNetWorth(int playerID)
{
    int netWorth = 0;
    int propertyValue = 0;
    int buildingValue = 0;
    int railwayValue = 0;
    int utilityValue = 0;
    int propertyIndex;
    int totalPaymentDebt = 0;
    int i;

    netWorth = players[playerID].money;

    for(i = 0; i < 22; i++)
    {
        if(properties[i].owner == players[playerID].playerID)
        {
            propertyValue += properties[i].currentPrice;

            if(properties[i].houseCount > 0)
            {
                buildingValue += properties[i].houseCount * properties[i].houseConstructionCost;
            }

            if(properties[i].hotelCount > 0)
            {
                buildingValue += properties[i].hotelCount * properties[i].hotelConstructionCost;
            }
        }
    }

    for(i = 0; i < 4; i++)
    {
        if(railways[i].owner == players[playerID].playerID)
        {
            railwayValue += railways[i].currentPrice;
        }
    }

    for(i = 0; i < 2; i++)
    {
        if(utilities[i].owner == players[playerID].playerID)
        {
            utilityValue += utilities[i].currentPrice;
        }
    }

    for(i = 0; i < 40; i++)
    {
        totalPaymentDebt += players[playerID].paymentDebt[i];
    }

    netWorth += propertyValue;
    netWorth += buildingValue;
    netWorth += railwayValue;
    netWorth += utilityValue;

    netWorth -= players[playerID].currentLoan;
    netWorth -= totalPaymentDebt;
    netWorth -= players[playerID].luxuryPropertyTaxDue;
    netWorth -= players[playerID].taxableMoney * rates.incomeTaxRate / 100.0;

    return netWorth;
}




//disaster functions
void happenDisaster()
{
    int disaster;

    if(gameInfo.currentEconomicEvent == 3)
    {   
        //this part is used to  increase flood disaster probability to 40%
        //under economic event 3 : heavy Monsoon
        int randomNumber = rand() % 100;

        if(randomNumber < 40)
        {
            disaster = flood;
        }
        else if(randomNumber < 55)
        {
            disaster = fire;
        }
        else if(randomNumber < 70)
        {
            disaster = riot;
        }
        else if(randomNumber < 85)
        {
            disaster = buildingCollapse;
        }
        else
        {
            disaster = electricalFailure;
        }
    }

    else if(gameInfo.currentEconomicEvent ==8)
    {
        //this part is used to immcrease riot disaster probability to 40%
        //under economic event 8 : political unrest
        int randomNumber = rand() % 100;

        if(randomNumber < 40)
        {
            disaster = riot;
        }
        else if(randomNumber < 55)
        {
            disaster = fire;
        }
        else if(randomNumber < 70)
        {
            disaster = flood;
        }
        else if(randomNumber < 85)
        {
            disaster = buildingCollapse;
        }
        else
        {
            disaster = electricalFailure;
        }
    }

    else
    {
        disaster = rand() % 5;
    }
    int randomPropertyIndex;
    int developedPropertyCount = 0;
    int i;

    for(i = 0; i < 22; i++)
    {
        if(properties[i].houseCount > 0 || properties[i].hotelCount > 0)
        {
            developedPropertyCount++;
        }
    }

    if(developedPropertyCount == 0)
    {
        printf("\nNo developed property is available for a disaster.\n\n");
        return;
    }

    randomPropertyIndex = rand() % 22;

    while(properties[randomPropertyIndex].houseCount == 0 &&
          properties[randomPropertyIndex].hotelCount == 0)
    {
        randomPropertyIndex = rand() % 22;
    }
    properties[randomPropertyIndex].isDisasterDamaged = 1;
    properties[randomPropertyIndex].disasterType = disaster;
    properties[randomPropertyIndex].disasterRepairCost = properties[randomPropertyIndex].currentPrice * 10 / 100;
    //assumed that as 10% of the current property price is the repair cost for disaster damage
}

void repairDisasterDamagedProperties(int playerID)
{
    int i;

    for(i = 0; i < 22; i++)
    {
        if(properties[i].owner == players[playerID].playerID && properties[i].isDisasterDamaged == 1)
        {
            if(players[playerID].money >= properties[i].disasterRepairCost)
            {
                players[playerID].money -= properties[i].disasterRepairCost;

                printf("%s repaired %s.\n",players[playerID].name,properties[i].name);

                printf("Repair Cost : LKR %d\n", properties[i].disasterRepairCost);

                properties[i].isDisasterDamaged = 0;
                properties[i].disasterType = -1;
                properties[i].disasterRepairCost = 0;

                printf("Property is no longer damaged.\n");
            }
        }
    }
}

void processDisasterRepairs(void)
{
    int i;
    int owner;
    int repairCost;
    int j;

    for(i = 0; i < 22; i++)
    {
        if(properties[i].isDisasterDamaged == 0)
        {
            continue;
        }

        owner = properties[i].owner;

        if(owner < 0 || owner >= 4)
        {
            continue;
        }

        if(players[owner].isBankrupt)
        {
            continue;
        }

        repairCost =
            properties[i].disasterRepairCost;

        /*
         * Automatically repair when the owner
         * has sufficient funds.
         */
        if(players[owner].money >= repairCost)
        {
            players[owner].money -= repairCost;

            properties[i].isDisasterDamaged = 0;

            properties[i].disasterRepairCost = 0;

            properties[i].disasterType = -1;

            /*
             * Restore building condition.
             */
            for(j = 0; j < properties[i].houseCount; j++)
            {
                properties[i].buildingCondition[j] = 100;
            }

            if(properties[i].hotelCount > 0)
            {
                properties[i].buildingCondition[0] = 100;
            }

            printf("\nDisaster Repair\n");

            printf("%s repaired %s.\n",
                   players[owner].name,
                   properties[i].name);

            printf("Repair Cost : LKR %d\n\n",
                   repairCost);
        }
    }
}



//inflation functions

void propertyInflation(int randomPercentage)
{
    int i = 0;

    while(i < 22)
    {
        properties[i].currentPrice = properties[i].currentPrice * (100 + randomPercentage) / 100;

        properties[i].houseConstructionCost = properties[i].houseConstructionCost * (100 + randomPercentage) / 100;

        properties[i].hotelConstructionCost = properties[i].hotelConstructionCost * (100 + randomPercentage) / 100;

        properties[i].currentRent = properties[i].currentRent * (100 + randomPercentage) / 100;

        properties[i].repairCost = properties[i].repairCost * (100 + randomPercentage) / 100;

        i++;
    }

    printf("Property prices, building costs, rent and repair costs have been updated due to inflation.\n");
}

void insuaranceInflation(int randomPercentage)
{
    int i = 0;

    while(i < 3)
    {
        insurance[i].insurancePremium = insurance[i].insurancePremium * (100 + randomPercentage) / 100;

        i++;
    }

    printf("Insurance premiums have been updated due to inflation.\n");
}

void loanInflation(int randomPercentage)
{
    rates.interestRate = rates.interestRate * (100 + randomPercentage) / 100;
    printf("Loan interest rate has been updated due to inflation.\n");
}

void inflation(int gameRound)
{
    int random[6] = {-3, 0, 2, 5, 8, 12};
    int randomPercentage;

    if(gameRound % 10 == 0)
    {
        randomPercentage = random[rand() % 6];

        printf("\nInflation: %d%%\n", randomPercentage);

        propertyInflation(randomPercentage);
        insuaranceInflation(randomPercentage);
        loanInflation(randomPercentage);
    }
}


//auction functions

void auctionProperty(int propertyIndex)
{
    int marketValue;
    int openingBid;
    int currentBid;
    int highestBidder;
    int activePlayers[4];

    int i;
    int activeCount;
    int bidMade;
    int bid;

    marketValue = properties[propertyIndex].currentPrice;

    openingBid = properties[propertyIndex].auctionStartingPrice;


    openingBid =(openingBid / 250) * 250;

    if(openingBid < 250)
    {
        openingBid = 250;
    }


    currentBid = openingBid - 250;

    highestBidder = -1;

    for(i = 0; i < 4; i++)
    {
        if(players[i].isBankrupt == 0)
        {
            activePlayers[i] = 1;
        }
        else
        {
            activePlayers[i] = 0;
        }
    }

    printf("\n========================================\n");
    printf("Auction Started\n");
    printf("Property : %s\n", properties[propertyIndex].name);

    printf("Market Value : LKR %d\n", marketValue);

    printf("Opening Bid : LKR %d\n", openingBid);

    printf("========================================\n\n");


    while(1)
    {
        activeCount = 0;
        bidMade = 0;

        for(i = 0; i < 4; i++)
        {
            if(activePlayers[i] == 1)
            {
                activeCount++;
            }
        }


        if(activeCount == 0)
        {
            break;
        }

        for(i = 0; i < 4; i++)
        {
            if(activePlayers[i] == 1)
            {
                bid = 0;

                switch(players[i].playerID)
                {
                    case aggresiveInvestor:

                        bid = aggressiveAuctionDecision( i, propertyIndex, currentBid);

                        break;


                    case conservativeBanker:

                        bid = conservativeAuctionDecision( i, propertyIndex, currentBid );

                        break;


                    case riskTaker:

                        bid = riskTakerAuctionDecision( i, propertyIndex, currentBid );

                        break;


                    case opportunisticTrader:

                        bid = opportunisticAuctionDecision( i, propertyIndex,currentBid );

                        break;
                }

                if(bid > currentBid && bid <= players[i].money)
                {
                    currentBid = bid;

                    highestBidder = i;

                    bidMade = 1;

                    printf("%s bids LKR %d\n", players[i].name, currentBid);
                }

                else
                {
                    activePlayers[i] = 0;

                    printf("%s withdraws from the auction.\n", players[i].name);
                }
            }
        }

        if(bidMade == 0)
        {
            break;
        }

        activeCount = 0;

        for(i = 0; i < 4; i++)
        {
            if(activePlayers[i] == 1)
            {
                activeCount++;
            }
        }


        if(activeCount == 1 &&
           highestBidder != -1)
        {
            break;
        }
    }

    if(highestBidder == -1)
    {
        printf("\nNo player placed a bid.\n");

        printf("%s remains with the Bank.\n\n",
               properties[propertyIndex].name);

        return;
    }
    if(currentBid <= players[highestBidder].money)
    {
        players[highestBidder].money -= currentBid;

    }
    else
    {
        printf("Auction payment failed because of insufficient funds.\n");
        return;
    }

    players[highestBidder].money -= currentBid;


    properties[propertyIndex].hasOwner = 1;

    properties[propertyIndex].owner = players[highestBidder].playerID;


    if(players[highestBidder].ownedPropertiesCount < 22)
    {
        players[highestBidder].ownedProperties[players[highestBidder].ownedPropertiesCount] = properties[propertyIndex].squareNumber;

        players[highestBidder].ownedPropertiesCount++;
    }


    printf("\n========================================\n");

    printf("Auction Result\n");

    printf("Winner : %s\n", players[highestBidder].name);

    printf("Property : %s\n", properties[propertyIndex].name);

    printf("Winning Bid : LKR %d\n", currentBid);

    printf("Remaining Balance : LKR %d\n", players[highestBidder].money);

    printf("========================================\n\n");
}

void auctionRailway(int railwayIndex)
{
    int marketValue;
    int openingBid;
    int currentBid;
    int highestBidder;
    int activePlayers[4];

    int i;
    int activeCount;
    int bidMade;
    int bid;

    marketValue = railways[railwayIndex].currentPrice;

    openingBid = railways[railwayIndex].auctionStartingPrice;

    openingBid = (openingBid / 250) * 250;

    if(openingBid < 250)
    {
        openingBid = 250;
    }

    currentBid = openingBid - 250;

    highestBidder = -1;

    for(i = 0; i < 4; i++)
    {
        if(players[i].isBankrupt == 0)
        {
            activePlayers[i] = 1;
        }
        else
        {
            activePlayers[i] = 0;
        }
    }

    printf("\n========================================\n");
    printf("Auction Started\n");
    printf("Railway : %s\n", railways[railwayIndex].name);

    printf("Market Value : LKR %d\n", marketValue);

    printf("Opening Bid : LKR %d\n", openingBid);

    printf("========================================\n\n");

    while(1)
    {
        activeCount = 0;
        bidMade = 0;

        for(i = 0; i < 4; i++)
        {
            if(activePlayers[i] == 1)
            {
                activeCount++;
            }
        }

        if(activeCount == 0)
        {
            break;
        }

        for(i = 0; i < 4; i++)
        {
            if(activePlayers[i] == 1)
            {
                bid = 0;

                switch(players[i].playerID)
                {
                    case aggresiveInvestor:

                        bid = aggressiveRailwayAuctionDecision(
                                  i,
                                  railwayIndex,
                                  currentBid);

                        break;

                    case conservativeBanker:

                        bid = conservativeRailwayAuctionDecision(
                                  i,
                                  railwayIndex,
                                  currentBid);

                        break;

                    case riskTaker:

                        bid = riskTakerRailwayAuctionDecision(
                                  i,
                                  railwayIndex,
                                  currentBid);

                        break;

                    case opportunisticTrader:

                        bid = opportunisticRailwayAuctionDecision(
                                  i,
                                  railwayIndex,
                                  currentBid);

                        break;
                }

                if(bid > currentBid && bid <= players[i].money)
                {
                    currentBid = bid;

                    highestBidder = i;

                    bidMade = 1;

                    printf("%s bids LKR %d\n",
                           players[i].name,
                           currentBid);
                }

                else
                {
                    activePlayers[i] = 0;

                    printf("%s withdraws from the auction.\n",
                           players[i].name);
                }
            }
        }

        if(bidMade == 0)
        {
            break;
        }

        activeCount = 0;

        for(i = 0; i < 4; i++)
        {
            if(activePlayers[i] == 1)
            {
                activeCount++;
            }
        }

        if(activeCount == 1 &&
           highestBidder != -1)
        {
            break;
        }
    }

    if(highestBidder == -1)
    {
        printf("\nNo player placed a bid.\n");

        printf("%s remains with the Bank.\n\n",
               railways[railwayIndex].name);

        return;
    }

    if(currentBid <= players[highestBidder].money)
    {
        players[highestBidder].money -= currentBid;
    }
    else
    {
        printf("Auction payment failed because of insufficient funds.\n");
        return;
    }

    railways[railwayIndex].hasOwner = 1;

    railways[railwayIndex].owner =
        players[highestBidder].playerID;

    if(players[highestBidder].ownedRailwayCount < 4)
    {
        players[highestBidder].ownedRailways[
            players[highestBidder].ownedRailwayCount] =
            railways[railwayIndex].squareNumber;

        players[highestBidder].ownedRailwayCount++;
    }

    printf("\n========================================\n");

    printf("Auction Result\n");

    printf("Winner : %s\n", players[highestBidder].name);

    printf("Railway : %s\n", railways[railwayIndex].name);

    printf("Winning Bid : LKR %d\n", currentBid);

    printf("Remaining Balance : LKR %d\n",
           players[highestBidder].money);

    printf("========================================\n\n");
}

void auctionUtility(int utilityIndex)
{
    int marketValue;
    int openingBid;
    int currentBid;
    int highestBidder;
    int activePlayers[4];

    int i;
    int activeCount;
    int bidMade;
    int bid;

    marketValue = utilities[utilityIndex].currentPrice;

    openingBid = utilities[utilityIndex].auctionStartingPrice;

    openingBid = (openingBid / 250) * 250;

    if(openingBid < 250)
    {
        openingBid = 250;
    }

    currentBid = openingBid - 250;

    highestBidder = -1;

    for(i = 0; i < 4; i++)
    {
        if(players[i].isBankrupt == 0)
        {
            activePlayers[i] = 1;
        }
        else
        {
            activePlayers[i] = 0;
        }
    }

    printf("\n========================================\n");
    printf("Auction Started\n");
    printf("Utility : %s\n", utilities[utilityIndex].name);

    printf("Market Value : LKR %d\n", marketValue);

    printf("Opening Bid : LKR %d\n", openingBid);

    printf("========================================\n\n");

    while(1)
    {
        activeCount = 0;
        bidMade = 0;

        for(i = 0; i < 4; i++)
        {
            if(activePlayers[i] == 1)
            {
                activeCount++;
            }
        }

        if(activeCount == 0)
        {
            break;
        }

        for(i = 0; i < 4; i++)
        {
            if(activePlayers[i] == 1)
            {
                bid = 0;

                switch(players[i].playerID)
                {
                    case aggresiveInvestor:

                        bid = aggressiveUtilityAuctionDecision( i, utilityIndex, currentBid);

                        break;

                    case conservativeBanker:

                        bid = conservativeUtilityAuctionDecision( i, utilityIndex, currentBid);

                        break;

                    case riskTaker:

                        bid = riskTakerUtilityAuctionDecision( i, utilityIndex, currentBid);

                        break;

                    case opportunisticTrader:

                        bid = opportunisticUtilityAuctionDecision( i, utilityIndex, currentBid);

                        break;
                }

                if(bid > currentBid && bid <= players[i].money)
                {
                    currentBid = bid;

                    highestBidder = i;

                    bidMade = 1;

                    printf("%s bids LKR %d\n", players[i].name, currentBid);
                }

                else
                {
                    activePlayers[i] = 0;

                    printf("%s withdraws from the auction.\n", players[i].name);
                }
            }
        }

        if(bidMade == 0)
        {
            break;
        }

        activeCount = 0;

        for(i = 0; i < 4; i++)
        {
            if(activePlayers[i] == 1)
            {
                activeCount++;
            }
        }

        if(activeCount == 1 &&
           highestBidder != -1)
        {
            break;
        }
    }

    if(highestBidder == -1)
    {
        printf("\nNo player placed a bid.\n");

        printf("%s remains with the Bank.\n\n", utilities[utilityIndex].name);

        return;
    }

    if(currentBid <= players[highestBidder].money)
    {
        players[highestBidder].money -= currentBid;
    }
    else
    {
        printf("Auction payment failed because of insufficient funds.\n");
        return;
    }

    utilities[utilityIndex].hasOwner = 1;

    utilities[utilityIndex].owner = players[highestBidder].playerID;

    if(players[highestBidder].ownedUtilitiesCount < 2)
    {
        players[highestBidder].ownedUtilities[  players[highestBidder].ownedUtilitiesCount] = utilities[utilityIndex].squareNumber;

        players[highestBidder].ownedUtilitiesCount++;
    }

    printf("\n========================================\n");

    printf("Auction Result\n");

    printf("Winner : %s\n", players[highestBidder].name);

    printf("Utility : %s\n", utilities[utilityIndex].name);

    printf("Winning Bid : LKR %d\n", currentBid);

    printf("Remaining Balance : LKR %d\n", players[highestBidder].money);

    printf("========================================\n\n");
}


//property buy and rent functions

void propertyBuyRent(int playerSquare, int k) 
{ 
    int l = 0; 
    int averageCondition; 
    int rentPercentage; 
    int actualRent; 
    int totalDue;
    int paidAmount;
     
    while(l < 22) 
    { 
        if(playerSquare == properties[l].squareNumber) 
        { 
            if(properties[l].isClosed == 1) 
            { 
                printf("%s is currently closed due to Political Rally.\n", properties[l].name); 
 
                printf("No property operation can be performed.\n\n"); 
 
                break; 
            } 
 
            if(properties[l].hasOwner == 0) 
            { 
                if(playerPurchaseDecision(k, l)) 
                { 
                    if(gameInfo.currentGovernmentRegulation == 8 &&
                    countUndevelopedProperties(k) >= 3)
                    {
                        printf("%s is purchasing an additional undeveloped property under the Anti-Speculation Act.\n", players[k].name);

                        printf("%s must develop %s within 5 rounds.\n\n", players[k].name, properties[l].name);

                        properties[l].undevelopedPurchaseRound  = gameInfo.gameRound;
                    }
 
                    properties[l].hasOwner = 1; 
                    properties[l].owner = players[k].playerID; 
                    players[k].money -= properties[l].currentPrice; 
                    players[k].ownedProperties[players[k].ownedPropertiesCount] = properties[l].squareNumber; 
                    players[k].ownedPropertiesCount++; 
 
                    printf("%s purchased %s for LKR %d.\n",players[k].name,properties[l].name,properties[l].currentPrice); 
                    printf("Remaining Balance : LKR %d.\n\n",players[k].money); 
                } 
 
                else 
                { 
                    printf("%s declined to purchase %s.\n",players[k].name, properties[l].name); 
                    printf("Property enters auction.\n\n"); 
                    auctionProperty(l); 
                } 
            } 
 
            else 
            { 
                if(properties[l].owner != players[k].playerID) 
                {    
                    if(properties[l].isDisasterDamaged == 1) 
                    { 
                        printf("%s is disaster damaged. No rent can be collected.\n\n", properties[l].name); 
                    } 
                    else 
                    { 
                        printf("%s is already owned.\n",properties[l].name); 
 
                        printf("%s landed on %s.\n",players[k].name,properties[l].name); 
 
                        averageCondition = calculateAverageBuildingCondition(l);

                        rentPercentage = getConditionRentPercentage(averageCondition);

                        actualRent = properties[l].currentRent * rentPercentage / 100;
                        
                        if(eventCardData[k].isActive[0] == 1 && properties[l].hotelCount > 0)
                            {
                                actualRent = actualRent * 2;
                            }
                        if(eventCardData[k].isActive[13] == 1 && properties[l].hotelCount > 0)
                            {
                                actualRent = actualRent * 150 / 100;
                            }
                    } 
 
                    if(properties[l].isStructurallyDamaged) 
                    { 
                        actualRent = actualRent * 75 / 100; 
                    } 
 
 
                    printf("Average Building Condition : %d%%\n", averageCondition); 
 
                    printf("Rent Collection : %d%%\n", rentPercentage); 
 
                    if(properties[l].isStructurallyDamaged) 
                    { 
                        printf("Structural Damage : Rent reduced by 25%%\n"); 
                    } 
                     
                    totalDue = players[k].paymentDebt[properties[l].squareNumber] + actualRent;

                    if(players[k].money >= totalDue) 
                    {    
                        printf("Rent paid : LKR %d.\n", totalDue); 
                        printf("Owner : %s.\n\n", players[properties[l].owner].name); 

                        players[k].money -= totalDue; 
                        players[properties[l].owner].money += totalDue; 
                        players[properties[l].owner].taxableMoney += totalDue; 
                        players[k].paymentDebt[properties[l].squareNumber] = 0;
                    } 
                    else 
                    { 
                        printf("%s does not have enough money to pay the rent.\n", players[k].name); 
 
                        printf("Available Cash : LKR %d\n",players[k].money); 
 
                        printf("Required Rent : LKR %d\n",totalDue); 

                        paidAmount = players[k].money;
 
                        players[properties[l].owner].money += paidAmount; 
                        players[properties[l].owner].taxableMoney += paidAmount; 

                        players[k].paymentDebt[properties[l].squareNumber] = totalDue - paidAmount;
                        players[k].money = 0; 
 
                        //playerBankrupt(k, &gameInfo.bankruptedPlayerCount); 
                    }     
                } 
 
                else 
                { 
                    printf("%s landed on their own property %s. No rent paid.\n\n",players[k].name,properties[l].name); 
                } 
            } 
 
            break; 
        } 
 
        l++; 
    } 
}

void railwayBuyRent(int playerSquare, int k)
{
    int l = 0;
    int totalDue;
    int paidAmount;

    while(l < 4)
    {
        if(playerSquare == railways[l].squareNumber)
        {
            if(railways[l].hasOwner == 0)
            {
                if(railwayPurchaseDecision(k, l))
                {
                    railways[l].hasOwner = 1;
                    railways[l].owner = players[k].playerID;
                    players[k].money -= railways[l].currentPrice;
                    players[k].ownedRailways[players[k].ownedRailwayCount] =railways[l].squareNumber;
                    players[k].ownedRailwayCount++;

                    printf("%s purchased %s for LKR %d.\n\n",players[k].name,railways[l].name,railways[l].currentPrice);

                    if(players[k].ownedRailwayCount == 1)
                    {
                        printf("%s owns 1 railway! \n\n",players[k].name);

                        for(int i = 0; i < 4; i++)
                        {
                            if(railways[i].owner == players[k].playerID)
                            {
                                railways[i].currentRent = 250;

                                if(gameInfo.currentGovernmentRegulation == 5)
                                {
                                    railways[i].currentRent = railways[i].currentRent * 125 / 100;
                                }

                                printf("Base rent of %s is LKR %d \n\n",railways[i].name,railways[i].currentRent);
                            }
                        }
                    }

                    else if(players[k].ownedRailwayCount == 2)
                    {
                        printf("%s owns 2 railways! \n\n",players[k].name);

                        for(int i = 0; i < 4; i++)
                        {
                            if(railways[i].owner == players[k].playerID)
                            {
                                railways[i].currentRent = 500;

                                if(gameInfo.currentGovernmentRegulation == 5)
                                {
                                    railways[i].currentRent = railways[i].currentRent * 125 / 100;
                                }

                                printf("Base rent of %s is LKR %d \n",railways[i].name,railways[i].currentRent);
                            }
                        }

                        printf("\n");
                    }

                    else if(players[k].ownedRailwayCount == 3)
                    {
                        printf("%s owns 3 railways! \n\n",players[k].name);

                        for(int i = 0; i < 4; i++)
                        {
                            if(railways[i].owner == players[k].playerID)
                            {
                                railways[i].currentRent = 1000;

                                if(gameInfo.currentGovernmentRegulation == 5)
                                {
                                    railways[i].currentRent = railways[i].currentRent * 125 / 100;
                                }

                                printf("Base rent of %s is LKR %d \n", railways[i].name, railways[i].currentRent);
                            }
                        }

                        printf("\n");
                    }

                    else if(players[k].ownedRailwayCount == 4)
                    {
                        printf("%s owns all 4 railways! \n\n",players[k].name);

                        for(int i = 0; i < 4; i++)
                        {
                            if(railways[i].owner == players[k].playerID)
                            {
                                railways[i].currentRent = 2000;

                                if(gameInfo.currentGovernmentRegulation == 5)
                                {
                                    railways[i].currentRent = railways[i].currentRent * 125 / 100;
                                }
                                printf("Base rent of %s is LKR %d \n", railways[i].name, railways[i].currentRent);
                            }
                        }

                        printf("\n");
                    }
                }
                else
                {
                    printf("%s declined to purchase %s.\n\n", players[k].name, railways[l].name);
                    printf("Railway enters auction.\n\n");
                    auctionRailway(l);
                }
            }

            else
            {
                if(railways[l].owner != players[k].playerID)
                {
                    printf("%s is already owned.\n", railways[l].name);

                    printf("%s landed on %s \n", players[k].name, railways[l].name);

                    totalDue = players[k].paymentDebt[railways[l].squareNumber] + railways[l].currentRent;

                    if(eventCardData[k].isActive[1] == 1)
                    {
                        totalDue = totalDue * 2;
                    }

                    if(players[k].money >= totalDue)
                    {
                        printf("Rent paid : %d \n", totalDue);
                        printf("Owner : %s \n\n",players[railways[l].owner].name);

                        players[k].money -= totalDue;
                        players[railways[l].owner].money += totalDue;
                        players[railways[l].owner].taxableMoney += totalDue;
                        players[k].paymentDebt[railways[l].squareNumber] = 0;
                    }
                    else
                    {
                        printf("%s does not have enough money to pay the railway rent.\n",
                            players[k].name);

                        printf("Available Cash : LKR %d\n", players[k].money);
                        printf("Required Rent : LKR %d\n", totalDue);

                        paidAmount = players[k].money;

                        players[railways[l].owner].money += paidAmount;
                        players[railways[l].owner].taxableMoney += paidAmount;

                        players[k].paymentDebt[railways[l].squareNumber] = totalDue - paidAmount;
                        players[k].money = 0;

                    }
                }
                else
                {
                    printf("%s landed on their own railway %s. No rent paid.\n\n",players[k].name, railways[l].name);
                }
            }

            break;
        }

        l++;
    }
}

void utilityBuyRent(int playerSquare, int k)
{
    int l = 0;
    int totalDue;
    int paidAmount;
    int actualRent;

    while(l < 2)
    {
        if(playerSquare == utilities[l].squareNumber)
        {
            if(utilities[l].hasOwner == 0)
            {
                if(utilityPurchaseDecision(k, l))
                {
                    utilities[l].hasOwner = 1;
                    utilities[l].owner = players[k].playerID;
                    players[k].money -= utilities[l].currentPrice;
                    players[k].ownedUtilities[players[k].ownedUtilitiesCount] = utilities[l].squareNumber;
                    players[k].ownedUtilitiesCount++;

                    printf("%s purchased %s for LKR %d.\n\n",players[k].name,utilities[l].name,utilities[l].currentPrice);
                }

                else
                {
                    printf("%s declined to purchase %s.\n\n",players[k].name,utilities[l].name);
                    printf("Utility enters auction.\n\n");
                    auctionUtility(l);
                }
            }

            else
            {
                if(utilities[0].hasOwner && utilities[1].hasOwner && utilities[0].owner == utilities[1].owner)
                {
                    utilities[l].currentRent = 10 * (players[k].lastRoll1 + players[k].lastRoll2);
                }

                else
                {
                    utilities[l].currentRent = 4 * (players[k].lastRoll1 + players[k].lastRoll2);
                }

                actualRent = utilities[l].currentRent;

                if(gameInfo.currentGovernmentRegulation == 6)
                {
                    actualRent = actualRent * 120 / 100;
                }

                if(eventCardData[k].isActive[10] == 1)
                {
                    actualRent = actualRent * 50 / 100;
                }

                if(utilities[l].owner != players[k].playerID)
                {
                    printf("%s is already owned.\n",utilities[l].name);

                    printf("%s landed on %s \n",players[k].name,utilities[l].name);

                    totalDue = players[k].paymentDebt[utilities[l].squareNumber] + actualRent;

                    if(players[k].money >= totalDue)
                    {   
                        printf("Rent paid : %d \n",totalDue);
                        printf("Owner : %s \n\n",players[utilities[l].owner].name);

                        players[k].money -= totalDue;
                        players[utilities[l].owner].money += totalDue;
                        players[utilities[l].owner].taxableMoney += totalDue;
                        players[k].paymentDebt[utilities[l].squareNumber] = 0;
                    }
                    else
                    {
                        printf("%s does not have enough money to pay the utility rent.\n",players[k].name);

                        printf("Available Cash : LKR %d\n",players[k].money);
                        printf("Required Rent : LKR %d\n",totalDue);

                        paidAmount = players[k].money;

                        players[utilities[l].owner].money += paidAmount;
                        players[utilities[l].owner].taxableMoney += paidAmount;

                        players[k].paymentDebt[utilities[l].squareNumber] = totalDue - paidAmount;
                        players[k].money = 0;

                    }
                }
                else
                {
                    printf("%s landed on their own utility %s. No rent paid.\n\n",players[k].name,utilities[l].name);
                }
            }

            break;
        }

        l++;
    }
}


//constructing houses and hotels functions

int constructHouse(int k, int propertyIndex)
{   
    int constructionCost;

    if(eventCardData[k].isActive[14] == 1)
    {
        printf("Labour Strike is active. Construction is suspended for 2 rounds.\n");
        return 0;
    }

    constructionCost = properties[propertyIndex].houseConstructionCost;

    if(eventCardData[k].isActive[6] == 1)
    {
        constructionCost = constructionCost * 70 / 100;
    }

    if(eventCardData[k].isActive[17] == 1)
    {
        constructionCost = constructionCost * 110 / 100;
    }
    if(properties[propertyIndex].isClosed == 1)
    {
        printf("%s is closed for business. Cannot construct house.\n", properties[propertyIndex].name);
        return 0;
    }

    if(players[k].money < constructionCost)
    {
        return 0;
    }

    if(properties[propertyIndex].houseCount >= 4)
    {
        return 0;
    }

    players[k].money -= constructionCost;

    properties[propertyIndex].houseCount++;

    properties[propertyIndex].buildingCondition[properties[propertyIndex].houseCount - 1] = 100;

    switch(properties[propertyIndex].houseCount)
    {
        case 1:
            properties[propertyIndex].currentRent = properties[propertyIndex].currentRent * 2;

            printf("Rent of %s is increased to LKR %d\n", properties[propertyIndex].name,properties[propertyIndex].currentRent);
                    
            break;


        case 2:
            properties[propertyIndex].currentRent = properties[propertyIndex].currentRent * 3 / 2;

            printf("Rent of %s is increased to LKR %d\n", properties[propertyIndex].name, properties[propertyIndex].currentRent);
            break;


        case 3:
            properties[propertyIndex].currentRent = properties[propertyIndex].currentRent * 5 / 3;

            printf("Rent of %s is increased to LKR %d\n", properties[propertyIndex].name, properties[propertyIndex].currentRent);
            break;


        case 4:
            properties[propertyIndex].currentRent = properties[propertyIndex].currentRent * 7 / 5;

            printf("Rent of %s is increased to LKR %d\n", properties[propertyIndex].name, properties[propertyIndex].currentRent);
            break;
    }

    printf("%s constructed one house on %s.\n", players[k].name, properties[propertyIndex].name);

    printf("Construction Cost : LKR %d\n", properties[propertyIndex].houseConstructionCost);

    printf("Houses : %d\n", properties[propertyIndex].houseCount);

    return 1;
}

int constructHotel(int k, int propertyIndex)
{   

    if(eventCardData[k].isActive[14] == 1)
    {
        printf("Labour Strike is active. Construction is suspended for 2 rounds.\n");
        return 0;
    }

    if(properties[propertyIndex].isClosed == 1)
    {   
        printf("%s is closed for business. Cannot construct hotel.\n", properties[propertyIndex].name);
        return 0;
    }

    if(players[k].money < properties[propertyIndex].hotelConstructionCost)
    {
        return 0;
    }

    if(properties[propertyIndex].houseCount != 4)
    {
        return 0;
    }

    if(properties[propertyIndex].hotelCount >= 1)
    {
        return 0;
    }

    players[k].money -= properties[propertyIndex].hotelConstructionCost;

    properties[propertyIndex].houseCount = 0;
    properties[propertyIndex].hotelCount = 1;
    properties[propertyIndex].buildingCondition[0] = 100;

    properties[propertyIndex].currentRent = properties[propertyIndex].currentRent * 10 / 7;

    printf("%s constructed a hotel on %s.\n", players[k].name, properties[propertyIndex].name);

    printf("Construction Cost : LKR %d\n", properties[propertyIndex].hotelConstructionCost);

    printf("Hotel Count : %d\n", properties[propertyIndex].hotelCount);

    printf("Rent of %s is increased to LKR %d\n", properties[propertyIndex].name, properties[propertyIndex].currentRent);

    return 1;
}
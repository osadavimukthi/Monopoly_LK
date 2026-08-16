#include <stdio.h>
#include "game.h"
#include "types.h"
#include "players.h"
#include "board.h"
#include "finance.h"

#define INITIALCASH 30000

struct player players[4] =
{
    {
        .playerID = aggresiveInvestor,
        .name = "Aggressive Investor",
        .priority = 0,
        .oldPosition = 0,
        .currentPosition = 0,
        .money = INITIALCASH,
        .taxableMoney = 0,
        .ownedProperties = {-1},
        .ownedPropertiesCount = 0,
        .isInJail = 0,
        .jailTurnCount = 0,
        .isBankrupt = 0,
        .ownedRailways = {-1},
        .ownedRailwayCount = 0,
        .ownedUtilities = {-1},
        .ownedUtilitiesCount = 0,
        .hasLoan = 0,
        .lastRoll1 = 0,
        .lastRoll2 = 0,
        .playerRound = 0,
        .playerTurn = 0,
        .obtainableMaximumLoan = 0,
        .currentLoan = 0,
        .loanRound = 0,
        .loanInterestRate = 0,
        .paymentDebt = {0},
        .luxuryPropertyTaxDebt = 0,
        .luxuryPropertyTaxDue = 0
    },

    {
        .playerID = conservativeBanker,
        .name = "Conservative Banker",
        .priority = 0,
        .oldPosition = 0,
        .currentPosition = 0,
        .money = INITIALCASH,
        .taxableMoney = 0,
        .ownedProperties = {-1},
        .ownedPropertiesCount = 0,
        .isInJail = 0,
        .jailTurnCount = 0,
        .isBankrupt = 0,
        .ownedRailways = {-1},
        .ownedRailwayCount = 0,
        .ownedUtilities = {-1},
        .ownedUtilitiesCount = 0,
        .hasLoan = 0,
        .lastRoll1 = 0,
        .lastRoll2 = 0,
        .playerRound = 0,
        .playerTurn = 0,
        .obtainableMaximumLoan = 0,
        .currentLoan = 0,
        .loanRound = 0,
        .loanInterestRate = 0,
        .paymentDebt = {0},
        .luxuryPropertyTaxDebt = 0,
        .luxuryPropertyTaxDue = 0
    },

    {
        .playerID = riskTaker,
        .name = "Risk Taker",
        .priority = 0,
        .oldPosition = 0,
        .currentPosition = 0,
        .money = INITIALCASH,
        .taxableMoney = 0,
        .ownedProperties = {-1},
        .ownedPropertiesCount = 0,
        .isInJail = 0,
        .jailTurnCount = 0,
        .isBankrupt = 0,
        .ownedRailways = {-1},
        .ownedRailwayCount = 0,
        .ownedUtilities = {-1},
        .ownedUtilitiesCount = 0,
        .hasLoan = 0,
        .lastRoll1 = 0,
        .lastRoll2 = 0,
        .playerRound = 0,
        .playerTurn = 0,
        .obtainableMaximumLoan = 0,
        .currentLoan = 0,
        .loanRound = 0,
        .loanInterestRate = 0,
        .paymentDebt = {0},
        .luxuryPropertyTaxDebt = 0,
        .luxuryPropertyTaxDue = 0
    },

    {
        .playerID = opportunisticTrader,
        .name = "Opportunistic Trader",
        .priority = 0,
        .oldPosition = 0,
        .currentPosition = 0,
        .money = INITIALCASH,
        .taxableMoney = 0,
        .ownedProperties = {-1},
        .ownedPropertiesCount = 0,
        .isInJail = 0,
        .jailTurnCount = 0,
        .isBankrupt = 0,
        .ownedRailways = {-1},
        .ownedRailwayCount = 0,
        .ownedUtilities = {-1},
        .ownedUtilitiesCount = 0,
        .hasLoan = 0,
        .lastRoll1 = 0,
        .lastRoll2 = 0,
        .playerRound = 0,
        .playerTurn = 0,
        .obtainableMaximumLoan = 0,
        .currentLoan = 0,
        .loanRound = 0,
        .loanInterestRate = 0,
        .paymentDebt = {0},
        .luxuryPropertyTaxDebt = 0,
        .luxuryPropertyTaxDue = 0
    }
};


//property purchase decision based on player type

int playerPurchaseDecision(int k, int propertyIndex)
{
    switch(players[k].playerID)
    {
        case aggresiveInvestor:

            return aggressivePurchaseDecision(k, propertyIndex);


        case conservativeBanker:

            return conservativePurchaseDecision(k, propertyIndex);


        case riskTaker:

            return riskTakerPurchaseDecision(k, propertyIndex);


        case opportunisticTrader:

            return opportunisticPurchaseDecision(k, propertyIndex);
    }

    return 0;
}


int aggressivePurchaseDecision(int k, int propertyIndex)
{
    int remainingMoney;

    remainingMoney =
        players[k].money -
        properties[propertyIndex].currentPrice;

    if(remainingMoney >= properties[propertyIndex].currentRent)
    {
        return 1;
    }

    return 0;
}


int conservativePurchaseDecision(int k, int propertyIndex)
{
    int remainingMoney;

    remainingMoney =
        players[k].money -
        properties[propertyIndex].currentPrice;

    if(remainingMoney >= players[k].money / 2)
    {
        return 1;
    }

    return 0;
}


int riskTakerPurchaseDecision(int k, int propertyIndex)
{


    if(players[k].money >= properties[propertyIndex].currentPrice)
    {
        return 1;
    }

    return 0;
}


int opportunisticPurchaseDecision(int k, int propertyIndex)
{
    int projectedAppreciation;
    int constructionCost;

    projectedAppreciation = properties[propertyIndex].basePurchasePrice - properties[propertyIndex].currentPrice;

    constructionCost = properties[propertyIndex].houseConstructionCost;

    if(projectedAppreciation > constructionCost)
    {
        if(players[k].money >= properties[propertyIndex].currentPrice)
        {
            return 1;
        }
    }

    return 0;
}


//utility and railway purchase decision 

int railwayPurchaseDecision(int k, int railwayIndex)
{
    int remainingMoney;

    remainingMoney = players[k].money - railways[railwayIndex].currentPrice;

    switch(players[k].playerID)
    {
        case aggresiveInvestor:

            if(remainingMoney >= railways[railwayIndex].currentRent)
            {
                return 1;
            }

            break;


        case conservativeBanker:

            if(remainingMoney >= players[k].money / 2)
            {
                return 1;
            }

            break;


        case riskTaker:

            if(players[k].money >= railways[railwayIndex].currentPrice)
            {
                return 1;
            }

            break;


        case opportunisticTrader:

            if(players[k].money >= railways[railwayIndex].currentPrice)
            {
                if(railways[railwayIndex].currentPrice <= railways[railwayIndex].basePurchasePrice)
                {
                    return 1;
                }
            }

            break;
    }

    return 0;
}

int utilityPurchaseDecision(int k, int utilityIndex)
{
    int remainingMoney;

    remainingMoney = players[k].money - utilities[utilityIndex].currentPrice;

    switch(players[k].playerID)
    {
        case aggresiveInvestor:

            if(remainingMoney >= utilities[utilityIndex].currentRent)
            {
                return 1;
            }

            break;


        case conservativeBanker:

            if(remainingMoney >= players[k].money / 2)
            {
                return 1;
            }

            break;


        case riskTaker:

            if(players[k].money >= utilities[utilityIndex].currentPrice)
            {
                return 1;
            }

            break;


        case opportunisticTrader:

            if(players[k].money >= utilities[utilityIndex].currentPrice)
            {
                if(utilities[utilityIndex].currentPrice <= utilities[utilityIndex].basePurchasePrice)
                {
                    return 1;
                }
            }

            break;
    }

    return 0;
}


//utility auction decision

int aggressiveUtilityAuctionDecision(int playerID, int utilityIndex, int currentBid)
{
    int maximumBid;
    int nextBid;

    maximumBid = (utilities[utilityIndex].currentPrice * 120) / 100;

    nextBid = currentBid + 250;

    if(nextBid <= maximumBid && nextBid <= players[playerID].money)
    {
        return nextBid;
    }

    return 0;
}


int conservativeUtilityAuctionDecision(int playerID, int utilityIndex, int currentBid)
{
    int maximumBid;
    int nextBid;

    maximumBid = utilities[utilityIndex].currentPrice;

    nextBid = currentBid + 250;

    if(nextBid <= maximumBid && nextBid <= players[playerID].money)
    {
        return nextBid;
    }

    return 0;
}


int riskTakerUtilityAuctionDecision(int playerID, int utilityIndex, int currentBid)
{
    int nextBid;

    nextBid = currentBid + 250;

    if(nextBid <= players[playerID].money)
    {
        return nextBid;
    }

    return 0;
}


int opportunisticUtilityAuctionDecision(int playerID, int utilityIndex, int currentBid)
{
    int maximumBid;
    int nextBid;

    maximumBid = (utilities[utilityIndex].currentPrice * 80) / 100;

    nextBid = currentBid + 250;

    if(nextBid <= maximumBid && nextBid <= players[playerID].money)
    {
        return nextBid;
    }

    return 0;
}


//railway auction decision


int aggressiveRailwayAuctionDecision(int playerID, int railwayIndex, int currentBid)
{
    int maximumBid;
    int nextBid;


    maximumBid = (railways[railwayIndex].currentPrice * 120) / 100;

    nextBid = currentBid + 250;

    if(nextBid <= maximumBid && nextBid <= players[playerID].money)
    {
        return nextBid;
    }

    return 0;
}

int conservativeRailwayAuctionDecision(int playerID, int railwayIndex, int currentBid)
{
    int maximumBid;
    int nextBid;
    maximumBid = railways[railwayIndex].currentPrice;

    nextBid = currentBid + 250;

    if(nextBid <= maximumBid && nextBid <= players[playerID].money)
    {
        return nextBid;
    }

    return 0;
}

int riskTakerRailwayAuctionDecision(int playerID, int railwayIndex, int currentBid)
{
    int nextBid;

    nextBid = currentBid + 250;

    if(nextBid <= players[playerID].money)
    {
        return nextBid;
    }

    return 0;
}

int opportunisticRailwayAuctionDecision(int playerID, int railwayIndex, int currentBid)
{
    int maximumBid;
    int nextBid;

    maximumBid = (railways[railwayIndex].currentPrice * 80) / 100;

    nextBid = currentBid + 250;

    if(nextBid <= maximumBid && nextBid <= players[playerID].money)
    {
        return nextBid;
    }

    return 0;
}


//proprtty auction decision 


int aggressiveAuctionDecision(int playerID, int propertyIndex, int currentBid)
{
    int maximumBid;
    int nextBid;

    maximumBid = (properties[propertyIndex].currentPrice * 120) / 100;

    nextBid = currentBid + 250;

    if(nextBid <= maximumBid && nextBid <= players[playerID].money)
    {
        return nextBid;
    }

    return 0;
}

int conservativeAuctionDecision(int playerID, int propertyIndex, int currentBid)
{
    int maximumBid;
    int nextBid;

    maximumBid = properties[propertyIndex].currentPrice;

    nextBid = currentBid + 250;

    if(nextBid <= maximumBid && nextBid <= players[playerID].money)
    {
        return nextBid;
    }

    return 0;
}

int riskTakerAuctionDecision(int playerID, int propertyIndex, int currentBid)
{
    int nextBid;

    nextBid = currentBid + 250;

    if(nextBid <= players[playerID].money)
    {
        return nextBid;
    }

    return 0;
}

int opportunisticAuctionDecision(int playerID, int propertyIndex, int currentBid)
{
    int maximumBid;
    int nextBid;

    maximumBid = (properties[propertyIndex].currentPrice * 80) / 100;

    nextBid = currentBid + 250;

    if(nextBid <= maximumBid && nextBid <= players[playerID].money)
    {
        return nextBid;
    }

    return 0;
}


//construction decision based on player type

int buildHouses(int k, int group, int reservePercent)
{
    int i;
    int propertyIndex;
    int constructed = 0;
    int reserveMoney;
    int minimumHouseCount;

    reserveMoney = players[k].money * reservePercent / 100;

    while(1)
    {
        propertyIndex = -1;
        minimumHouseCount = 4;

        for(i = 0; i < 22; i++)
        {
            if(properties[i].colorGroup == group && properties[i].owner == players[k].playerID &&
               properties[i].houseCount < 4 && properties[i].hotelCount == 0)
            {
                if(properties[i].houseCount < minimumHouseCount)
                {
                    minimumHouseCount = properties[i].houseCount;
                }
            }
        }

        if(minimumHouseCount == 4)
        {
            break;
        }

        for(i = 0; i < 22; i++)
        {
            if(properties[i].colorGroup == group && properties[i].owner == players[k].playerID &&
               properties[i].houseCount == minimumHouseCount && properties[i].houseCount < 4 && properties[i].hotelCount == 0)
            {
                if(players[k].money - properties[i].houseConstructionCost >= reserveMoney)
                {
                    propertyIndex = i;
                    break;
                }
            }
        }

        if(propertyIndex == -1)
        {
            break;
        }

        if(!constructHouse(k, propertyIndex))
        {
            break;
        }

        constructed++;

        printf("%s constructed one house on %s.\n", players[k].name, properties[propertyIndex].name);

        printf("Construction Cost : LKR %d\n", properties[propertyIndex].houseConstructionCost);

        printf("Houses : %d\n", properties[propertyIndex].houseCount);

        printf("Remaining Balance : LKR %d\n\n", players[k].money);
    }

    return constructed;
}
 
int aggressiveConstruction(int k)
{
    int i;
    int j;
    int group;
    int constructed = 0;


    for(i = 0; i < 8; i++)
    {
        if(monopolies[i].hasOwner == 1 && monopolies[i].owner == players[k].playerID)
        {
            group = monopolies[i].monopolyColor;

            printf("%s has monopoly of Group %d.\n", players[k].name, group);

            constructed += buildHouses(k, group, 0);

            for(j = 0; j < 22; j++)
            {
                if(properties[j].colorGroup == group && properties[j].owner == players[k].playerID &&
                   properties[j].houseCount == 4 && properties[j].hotelCount == 0)
                {
                    if(constructHotel(k, j))
                    {
                        printf("%s upgraded %s to a HOTEL.\n", players[k].name, properties[j].name);

                        printf("Remaining Balance : LKR %d\n\n", players[k].money);
                    }
                }
            }
        }
    }

    if(constructed == 0)
    {
        printf("%s did not construct any houses.\n\n", players[k].name);
    }
    else
    {
        printf("%s constructed %d house(s) in total.\n\n", players[k].name, constructed);
    }

    return constructed;
}

int conservativeConstruction(int k)
{
    int i;
    int group;
    int constructed = 0;


    for(i = 0; i < 8; i++)
    {
        if(monopolies[i].hasOwner == 1 &&
           monopolies[i].owner == players[k].playerID)
        {
            group = monopolies[i].monopolyColor;

            printf("%s has monopoly of Group %d.\n",  players[k].name, group);

            constructed += buildHouses(k, group, 60);

            if(players[k].hasLoan == 0)
            {
                int j;

                for(j = 0; j < 22; j++)
                {
                    if(properties[j].colorGroup == group && properties[j].owner == players[k].playerID && properties[j].houseCount == 4 && properties[j].hotelCount == 0)
                    {
                        if(constructHotel(k, j))
                        {
                            printf("%s upgraded %s to a HOTEL.\n", players[k].name, properties[j].name);

                            printf("Remaining Balance : LKR %d\n\n", players[k].money);
                        }
                    }
                }
            }
        }
    }

    if(constructed == 0)
    {
        printf("%s did not construct any houses.\n\n", players[k].name);
    }
    else
    {
        printf("%s constructed %d house(s) in total.\n\n", players[k].name, constructed);
    }
    return constructed;
}

int riskTakerConstruction(int k)
{
    int i;
    int j;
    int group;
    int constructed = 0;

    for(i = 0; i < 8; i++)
    {
        if(monopolies[i].hasOwner == 1 && monopolies[i].owner == players[k].playerID)
        {
            group = monopolies[i].monopolyColor;

            printf("%s has monopoly of Group %d.\n", players[k].name, group);

            constructed += buildHouses(k, group, 0);

            for(j = 0; j < 22; j++)
            {
                if(properties[j].colorGroup == group && properties[j].owner == players[k].playerID &&
                   properties[j].houseCount == 4 &&properties[j].hotelCount == 0)
                {
                    if(constructHotel(k, j))
                    {
                        printf("%s upgraded %s to a HOTEL.\n", players[k].name, properties[j].name);

                        printf("Remaining Balance : LKR %d\n\n", players[k].money);
                    }
                }
            }
        }
    }

    if(constructed == 0)
    {
        printf("%s did not construct any houses.\n\n", players[k].name);
    }

    else
    {
        printf("%s constructed %d house(s) in total.\n\n", players[k].name, constructed);
    }
    return constructed;
}

int opportunisticConstruction(int k)
{
    int i;
    int j;
    int group;
    int constructed = 0;


    for(i = 0; i < 8; i++)
    {

        if(monopolies[i].hasOwner == 1 && monopolies[i].owner == players[k].playerID)
        {
            group = monopolies[i].monopolyColor;

            printf("%s has monopoly of Group %d.\n", players[k].name, group);

            constructed += buildHouses(k, group, 30);

            for(j = 0; j < 22; j++)
            {
                if(properties[j].colorGroup == group && properties[j].owner == players[k].playerID &&
                   properties[j].houseCount == 4 && properties[j].hotelCount == 0)
                {
                    if(constructHotel(k, j))
                    {
                        printf("%s upgraded %s to a HOTEL.\n", players[k].name, properties[j].name);

                        printf("Remaining Balance : LKR %d\n\n", players[k].money);
                    }
                }
            }
        }
    }

    if(constructed == 0)
    {
        printf("%s did not construct any houses.\n\n", players[k].name);
    }
    else
    {
        printf("%s constructed %d house(s) in total.\n\n", players[k].name, constructed);
    }

    return constructed;
}

int playerConstruction(int k)
{
    switch(players[k].playerID)
    {
        case aggresiveInvestor:
            return aggressiveConstruction(k);

        case conservativeBanker:
            return conservativeConstruction(k);

        case riskTaker:
            return riskTakerConstruction(k);

        case opportunisticTrader:
            return opportunisticConstruction(k);
    }

    return 0;
}


//loan taking decitions

void manageLoan(int k)
{
    int maximumLoan;
    int additionalLoan;
    int rentalIncome = 0;

    maximumLoan = calculateMaximumLoan(k);

    for(int i = 0; i < 22; i++)
    {
        if(properties[i].owner == players[k].playerID)
        {
            rentalIncome += properties[i].currentRent;
        }
    }

    for(int i = 0; i < 4; i++)
    {
        if(railways[i].owner == players[k].playerID)
        {
            rentalIncome += railways[i].currentRent;
        }
    }

    for(int i = 0; i < 2; i++)
    {
        if(utilities[i].owner == players[k].playerID)
        {
            rentalIncome += utilities[i].currentRent;
        }
    }


    switch(players[k].playerID)
    {
        case aggresiveInvestor:

            if(players[k].hasLoan == 1)
            {
                if(players[k].money > players[k].currentLoan * 2)
                {
                    repayFullLoan(k);
                }
            }

            break;


        case conservativeBanker:

            if(players[k].hasLoan == 1)
            {
                if(players[k].money >= players[k].currentLoan)
                {
                    repayFullLoan(k);
                }
            }
            else
            {
                if(players[k].money <= 3000 &&  maximumLoan > 0)
                {
                    obtainLoan(k, players[k].currentPosition);
                }
            }
            break;


        case riskTaker:

            if(players[k].hasLoan == 0)
            {
                if(maximumLoan > 0)
                {
                    obtainLoan(k, players[k].currentPosition);
                }
            }
            else
            {
                additionalLoan = maximumLoan - players[k].currentLoan;

                if(additionalLoan > 0)
                {
                    increaseLoan(k, additionalLoan);
                }
            }

            break;


        case opportunisticTrader:

            if(players[k].hasLoan == 0)
            {
                if(maximumLoan > 0)
                {
                    if(rentalIncome > (maximumLoan * rates.interestRate / 100))
                    {
                        obtainLoan(k, players[k].currentPosition);
                    }
                }
            }
            else
            {
                additionalLoan =  maximumLoan - players[k].currentLoan;

                if(additionalLoan > 0)
                {
                    if(rentalIncome > (additionalLoan * rates.interestRate / 100))
                    {
                        increaseLoan(k, additionalLoan);
                    }
                }
            }

            break;
    }
}


//taking insuarance decisions

void manageInsurance(int playerID)
{
    int i;
    int policyType;

    for(i = 0; i < 22; i++)
    {
        if(properties[i].owner != players[playerID].playerID)
        {
            continue;
        }
        if(properties[i].houseCount == 0 && properties[i].hotelCount == 0)
        {
            continue;
        }

        if(players[playerID].playerID == aggresiveInvestor)
        {
            if(properties[i].hotelCount > 0)
            {
                policyType = comprehensiveInsurance;
            }
            else
            {
                policyType = basicPropertyInsurance;
            }
        }

        else if(players[playerID].playerID == conservativeBanker)
        {
            policyType = comprehensiveInsurance;
        }

        else if(players[playerID].playerID == riskTaker)
        {
            if(players[playerID].money >= 30000)
            {
                continue;
            }

            policyType = comprehensiveInsurance;
        }

        else
        {
            if(properties[i].currentPrice < 7000)
            {
                continue;
            }

            policyType = comprehensiveInsurance;
        }

        if(properties[i].isInsured)
        {
            continue;
        }

        if(purchaseInsurance(playerID,  i, policyType))
        {

            break;
        }
    }
}



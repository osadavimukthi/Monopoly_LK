#include <stdio.h>
#include "game.h"
#include "types.h"
#include "players.h"
#include "board.h"
#include "buyandrent.h"
#include "buildings.h"
#include "finance.h"

#define INITIALCASH 30000
struct player players[4] = {

    // playerID,             name,                    priority, oldPos, currPos, money,       taxableMoney, ownedProperties, ownedCount, isInJail, jailTurns, isBankrupt, ownedRailways, railwayCount, ownedUtilities, utilityCount, hasLoan, lastRoll1, lastRoll2, playerRound, playerTurn, obtainableMaximumLoan, currentLoan, loanRound, loanInterestRate

    {aggresiveInvestor,   "Aggressive Investor",   0,        0,      0,       INITIALCASH, 0,             {-1},             0,          0,        0,          0,          {-1},          0,             {-1},           0,              0,       0,         0,         0,           0,          0,                    0,           0,         0},

    {conservativeBanker,  "Conservative Banker",   0,        0,      0,       INITIALCASH, 0,             {-1},             0,          0,        0,          0,          {-1},          0,             {-1},           0,              0,       0,         0,         0,           0,          0,                    0,           0,         0},

    {riskTaker,           "Risk Taker",            0,        0,      0,       INITIALCASH, 0,             {-1},             0,          0,        0,          0,          {-1},          0,             {-1},           0,              0,       0,         0,         0,           0,          0,                    0,           0,         0},

    {opportunisticTrader, "Opportunistic Trader",  0,        0,      0,       INITIALCASH, 0,             {-1},             0,          0,        0,          0,          {-1},          0,             {-1},           0,              0,       0,         0,         0,           0,          0,                    0,           0,         0}
};

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

    /*
     * Aggressive Investor:
     * Purchases the property if enough money remains
     * to pay at least one future rent.
     */

    if(remainingMoney >= properties[propertyIndex].currentRent)
    {
        return 1;
    }

    return 0;
}


int conservativePurchaseDecision(int k, int propertyIndex)
{
    int remainingMoney;

    /*
     * Conservative Banker:
     * At least 50% of current cash must remain
     * after purchasing the property.
     */

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
    /*
     * Risk Taker:
     * Purchases every available property whenever
     * legally possible.
     */

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

    /*
     * Opportunistic Trader:
     * Purchases only when projected appreciation
     * exceeds construction costs.
     */

    projectedAppreciation =
        properties[propertyIndex].basePurchasePrice -
        properties[propertyIndex].currentPrice;

    constructionCost =
        properties[propertyIndex].houseConstructionCost;

    if(projectedAppreciation > constructionCost)
    {
        if(players[k].money >=
           properties[propertyIndex].currentPrice)
        {
            return 1;
        }
    }

    return 0;
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
        printf("%s is still in Jail. Turn %d of 3.\n", players[k].name, players[k].jailTurnCount);
    }
    else if(players[k].jailTurnCount == 2)
    {
        players[k].jailTurnCount++;
        printf("%s has served 3 turns in Jail and is now released.\n", players[k].name);
        players[k].isInJail = 0;
        players[k].jailTurnCount = 0;
    }
}

int buildHouses(int k, int group, int reservePercent)
{
    int i;
    int propertyIndex;
    int constructed = 0;
    int reserveMoney;
    int minimumHouseCount;

    /*
     * Keep a fixed percentage of the money
     * available when construction starts.
     */
    reserveMoney =
        players[k].money * reservePercent / 100;

    while(1)
    {
        propertyIndex = -1;
        minimumHouseCount = 4;

        /*
         * Find the minimum number of houses
         * currently present in the group.
         */
        for(i = 0; i < 22; i++)
        {
            if(properties[i].colorGroup == group &&
               properties[i].owner == players[k].playerID &&
               properties[i].houseCount < 4 &&
               properties[i].hotelCount == 0)
            {
                if(properties[i].houseCount <
                   minimumHouseCount)
                {
                    minimumHouseCount =
                        properties[i].houseCount;
                }
            }
        }

        /*
         * All properties have four houses.
         */
        if(minimumHouseCount == 4)
        {
            break;
        }

        /*
         * Find an affordable property among
         * the properties with the fewest houses.
         */
        for(i = 0; i < 22; i++)
        {
            if(properties[i].colorGroup == group &&
               properties[i].owner == players[k].playerID &&
               properties[i].houseCount ==
               minimumHouseCount &&
               properties[i].houseCount < 4 &&
               properties[i].hotelCount == 0)
            {
                if(players[k].money -
                   properties[i].houseConstructionCost >=
                   reserveMoney)
                {
                    propertyIndex = i;
                    break;
                }
            }
        }

        /*
         * No property with the minimum number
         * of houses can be constructed.
         */
        if(propertyIndex == -1)
        {
            break;
        }

        /*
         * Construct the house.
         */
        if(!constructHouse(k, propertyIndex))
        {
            break;
        }

        constructed++;

        printf("%s constructed one house on %s.\n",
               players[k].name,
               properties[propertyIndex].name);

        printf("Construction Cost : LKR %d\n",
               properties[propertyIndex].houseConstructionCost);

        printf("Houses : %d\n",
               properties[propertyIndex].houseCount);

        printf("Remaining Balance : LKR %d\n\n",
               players[k].money);
    }

    return constructed;
}
 
int aggressiveConstruction(int k)
{
    int i;
    int j;
    int group;
    int constructed = 0;

    printf("\n--- Aggressive Investor Construction ---\n");

    for(i = 0; i < 8; i++)
    {
        if(monopolies[i].hasOwner == 1 &&
           monopolies[i].owner == players[k].playerID)
        {
            group = monopolies[i].monopolyColor;

            printf("%s has monopoly of Group %d.\n",
                   players[k].name,
                   group);

            /*
             * Aggressive Investor:
             * Constructs the maximum possible
             * number of houses immediately.
             */
            constructed +=
                buildHouses(k, group, 0);

            /*
             * Converts houses into hotels as soon
             * as legally permitted.
             */
            for(j = 0; j < 22; j++)
            {
                if(properties[j].colorGroup == group &&
                   properties[j].owner == players[k].playerID &&
                   properties[j].houseCount == 4 &&
                   properties[j].hotelCount == 0)
                {
                    if(constructHotel(k, j))
                    {
                        printf("%s upgraded %s to a HOTEL.\n",
                               players[k].name,
                               properties[j].name);

                        printf("Remaining Balance : LKR %d\n\n",
                               players[k].money);
                    }
                }
            }
        }
    }

    if(constructed == 0)
    {
        printf("%s did not construct any houses.\n\n",
               players[k].name);
    }
    else
    {
        printf("%s constructed %d house(s) in total.\n\n",
               players[k].name,
               constructed);
    }

    return constructed;
}
int conservativeConstruction(int k)
{
    int i;
    int group;
    int constructed = 0;

    printf("\n--- Conservative Banker Construction ---\n");

    for(i = 0; i < 8; i++)
    {
        if(monopolies[i].hasOwner == 1 &&
           monopolies[i].owner == players[k].playerID)
        {
            group = monopolies[i].monopolyColor;

            printf("%s has monopoly of Group %d.\n",
                   players[k].name,
                   group);

            /*
             * Conservative Banker keeps a large
             * emergency cash reserve.
             */
            constructed +=
                buildHouses(k, group, 60);

            /*
             * Hotels are not allowed while a loan
             * is still outstanding.
             */
            if(players[k].hasLoan == 0)
            {
                int j;

                for(j = 0; j < 22; j++)
                {
                    if(properties[j].colorGroup == group &&
                       properties[j].owner == players[k].playerID &&
                       properties[j].houseCount == 4 &&
                       properties[j].hotelCount == 0)
                    {
                        if(constructHotel(k, j))
                        {
                            printf("%s upgraded %s to a HOTEL.\n",
                                   players[k].name,
                                   properties[j].name);

                            printf("Remaining Balance : LKR %d\n\n",
                                   players[k].money);
                        }
                    }
                }
            }
        }
    }

    if(constructed == 0)
    {
        printf("%s did not construct any houses.\n\n",
               players[k].name);
    }
    else
    {
        printf("%s constructed %d house(s) in total.\n\n",
               players[k].name,
               constructed);
    }

    return constructed;
}
int riskTakerConstruction(int k)
{
    int i;
    int j;
    int group;
    int constructed = 0;

    printf("\n--- Risk Taker Construction ---\n");

    for(i = 0; i < 8; i++)
    {
        if(monopolies[i].hasOwner == 1 &&
           monopolies[i].owner == players[k].playerID)
        {
            group = monopolies[i].monopolyColor;

            printf("%s has monopoly of Group %d.\n",
                   players[k].name,
                   group);

            /*
             * Risk Taker builds as much as possible.
             */
            constructed +=
                buildHouses(k, group, 0);

            /*
             * Risk Taker builds hotels as early
             * as legally possible.
             */
            for(j = 0; j < 22; j++)
            {
                if(properties[j].colorGroup == group &&
                   properties[j].owner == players[k].playerID &&
                   properties[j].houseCount == 4 &&
                   properties[j].hotelCount == 0)
                {
                    if(constructHotel(k, j))
                    {
                        printf("%s upgraded %s to a HOTEL.\n",
                               players[k].name,
                               properties[j].name);

                        printf("Remaining Balance : LKR %d\n\n",
                               players[k].money);
                    }
                }
            }
        }
    }

    if(constructed == 0)
    {
        printf("%s did not construct any houses.\n\n",
               players[k].name);
    }
    else
    {
        printf("%s constructed %d house(s) in total.\n\n",
               players[k].name,
               constructed);
    }

    return constructed;
}
int opportunisticConstruction(int k)
{
    int i;
    int j;
    int group;
    int constructed = 0;

    printf("\n--- Opportunistic Trader Construction ---\n");

    /*
     * Check every property group.
     */
    for(i = 0; i < 8; i++)
    {
        /*
         * Only construct if this player owns
         * the complete monopoly.
         */
        if(monopolies[i].hasOwner == 1 &&
           monopolies[i].owner == players[k].playerID)
        {
            group = monopolies[i].monopolyColor;

            printf("%s has monopoly of Group %d.\n",
                   players[k].name,
                   group);

            /*
             * Keep some money as a reserve.
             * Opportunistic Trader is less aggressive
             * than Risk Taker.
             */
            constructed +=
                buildHouses(k, group, 30);

            /*
             * Build hotels when all four houses
             * are available.
             */
            for(j = 0; j < 22; j++)
            {
                if(properties[j].colorGroup == group &&
                   properties[j].owner == players[k].playerID &&
                   properties[j].houseCount == 4 &&
                   properties[j].hotelCount == 0)
                {
                    if(constructHotel(k, j))
                    {
                        printf("%s upgraded %s to a HOTEL.\n",
                               players[k].name,
                               properties[j].name);

                        printf("Remaining Balance : LKR %d\n\n",
                               players[k].money);
                    }
                }
            }
        }
    }

    if(constructed == 0)
    {
        printf("%s did not construct any houses.\n\n",
               players[k].name);
    }
    else
    {
        printf("%s constructed %d house(s) in total.\n\n",
               players[k].name,
               constructed);
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
//I asssumed that railway and utility buying and renting according to player behaviours
int railwayPurchaseDecision(int k, int railwayIndex)
{
    int remainingMoney;

    remainingMoney =
        players[k].money -
        railways[railwayIndex].currentPrice;

    switch(players[k].playerID)
    {
        case aggresiveInvestor:

            if(remainingMoney >=
               railways[railwayIndex].currentRent)
            {
                return 1;
            }

            break;


        case conservativeBanker:

            if(remainingMoney >=
               players[k].money / 2)
            {
                return 1;
            }

            break;


        case riskTaker:

            if(players[k].money >=
               railways[railwayIndex].currentPrice)
            {
                return 1;
            }

            break;


        case opportunisticTrader:

            if(players[k].money >=
               railways[railwayIndex].currentPrice)
            {
                if(railways[railwayIndex].currentPrice <=
                   railways[railwayIndex].basePurchasePrice)
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

    remainingMoney =
        players[k].money -
        utilities[utilityIndex].currentPrice;

    switch(players[k].playerID)
    {
        case aggresiveInvestor:

            if(remainingMoney >=
               utilities[utilityIndex].currentRent)
            {
                return 1;
            }

            break;


        case conservativeBanker:

            if(remainingMoney >=
               players[k].money / 2)
            {
                return 1;
            }

            break;


        case riskTaker:

            if(players[k].money >=
               utilities[utilityIndex].currentPrice)
            {
                return 1;
            }

            break;


        case opportunisticTrader:

            if(players[k].money >=
               utilities[utilityIndex].currentPrice)
            {
                if(utilities[utilityIndex].currentPrice <=
                   utilities[utilityIndex].basePurchasePrice)
                {
                    return 1;
                }
            }

            break;
    }

    return 0;
}
void manageLoan(int k)
{
    int maximumLoan;
    int additionalLoan;
    int rentalIncome = 0;

    maximumLoan = calculateMaximumLoan(k);

    for(int i = 0; i < 22; i++)
    {
        if(properties[i].owner ==
           players[k].playerID)
        {
            rentalIncome += properties[i].currentRent;
        }
    }

    for(int i = 0; i < 4; i++)
    {
        if(railways[i].owner ==
           players[k].playerID)
        {
            rentalIncome += railways[i].currentRent;
        }
    }

    for(int i = 0; i < 2; i++)
    {
        if(utilities[i].owner ==
           players[k].playerID)
        {
            rentalIncome += utilities[i].currentRent;
        }
    }


    switch(players[k].playerID)
    {
        case aggresiveInvestor:

            /*
             * Repay only when excess cash is
             * greater than twice the loan.
             */
            if(players[k].hasLoan == 1)
            {
                if(players[k].money >
                   players[k].currentLoan * 2)
                {
                    repayFullLoan(k);
                }
            }

            break;


        case conservativeBanker:

            /*
             * Avoid loans unless bankruptcy is
             * becoming likely.
             */
            if(players[k].hasLoan == 1)
            {
                if(players[k].money >=
                   players[k].currentLoan)
                {
                    repayFullLoan(k);
                }
            }
            else
            {
                if(players[k].money <= 3000 &&
                   maximumLoan > 0)
                {
                    obtainLoan(k,
                               players[k].currentPosition);
                }
            }

            break;


        case riskTaker:

            /*
             * Always borrow the maximum permitted.
             */
            if(players[k].hasLoan == 0)
            {
                if(maximumLoan > 0)
                {
                    obtainLoan(k,
                               players[k].currentPosition);
                }
            }
            else
            {
                additionalLoan =
                    maximumLoan -
                    players[k].currentLoan;

                if(additionalLoan > 0)
                {
                    increaseLoan(k,
                                 additionalLoan);
                }
            }

            break;


        case opportunisticTrader:

            /*
             * Borrow only when expected rental
             * income is greater than borrowing cost.
             */
            if(players[k].hasLoan == 0)
            {
                if(maximumLoan > 0)
                {
                    if(rentalIncome >
                       (maximumLoan *
                        rates.interestRate / 100))
                    {
                        obtainLoan(k,
                                   players[k].currentPosition);
                    }
                }
            }
            else
            {
                additionalLoan =
                    maximumLoan -
                    players[k].currentLoan;

                if(additionalLoan > 0)
                {
                    if(rentalIncome >
                       (additionalLoan *
                        rates.interestRate / 100))
                    {
                        increaseLoan(k,
                                     additionalLoan);
                    }
                }
            }

            break;
    }
}


int aggressiveAuctionDecision(int playerID, int propertyIndex, int currentBid)
{
    int maximumBid;
    int nextBid;

    /*
     * Aggressive Investor:
     * Bids aggressively until property reaches
     * 120% of current market value.
     */

    maximumBid =
        (properties[propertyIndex].currentPrice * 120) / 100;

    nextBid = currentBid + 250;

    if(nextBid <= maximumBid &&
       nextBid <= players[playerID].money)
    {
        return nextBid;
    }

    return 0;
}


int conservativeAuctionDecision(int playerID, int propertyIndex, int currentBid)
{
    int maximumBid;
    int nextBid;

    /*
     * Conservative Banker:
     * Will not bid above the current market value.
     */

    maximumBid =
        properties[propertyIndex].currentPrice;

    nextBid = currentBid + 250;

    if(nextBid <= maximumBid &&
       nextBid <= players[playerID].money)
    {
        return nextBid;
    }

    return 0;
}


int riskTakerAuctionDecision(int playerID, int propertyIndex, int currentBid)
{
    int nextBid;

    /*
     * Risk Taker:
     * Continues bidding as long as the next bid
     * can be paid with available money.
     */

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

    /*
     * Opportunistic Trader:
     * Prefers discounted auction purchases.
     *
     * Will pay at most 80% of current market value.
     */

    maximumBid =
        (properties[propertyIndex].currentPrice * 80) / 100;

    nextBid = currentBid + 250;

    if(nextBid <= maximumBid &&
       nextBid <= players[playerID].money)
    {
        return nextBid;
    }

    return 0;
}


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

    marketValue =
        properties[propertyIndex].currentPrice;

    /*
     * Rule-LK 19:
     * Auction starts at 50% of market value.
     */

    openingBid = properties[propertyIndex].auctionStartingPrice;

    /*
     * Make opening bid a multiple of LKR 250.
     */

    openingBid =
        (openingBid / 250) * 250;

    if(openingBid < 250)
    {
        openingBid = 250;
    }

    /*
     * No actual bid has been made yet.
     *
     * Therefore currentBid is one increment
     * below the opening bid.
     */

    currentBid = openingBid - 250;

    highestBidder = -1;

    /*
     * All non-bankrupt players participate.
     */

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
    printf("Property : %s\n",
           properties[propertyIndex].name);

    printf("Market Value : LKR %d\n",
           marketValue);

    printf("Opening Bid : LKR %d\n",
           openingBid);

    printf("========================================\n\n");


    while(1)
    {
        activeCount = 0;
        bidMade = 0;

        /*
         * Count active players.
         */

        for(i = 0; i < 4; i++)
        {
            if(activePlayers[i] == 1)
            {
                activeCount++;
            }
        }

        /*
         * No players remain.
         */

        if(activeCount == 0)
        {
            break;
        }

        /*
         * Give every active player one chance
         * to bid.
         */

        for(i = 0; i < 4; i++)
        {
            if(activePlayers[i] == 1)
            {
                bid = 0;

                /*
                 * Select the player's auction behaviour.
                 */

                switch(players[i].playerID)
                {
                    case aggresiveInvestor:

                        bid =
                            aggressiveAuctionDecision(
                                i,
                                propertyIndex,
                                currentBid
                            );

                        break;


                    case conservativeBanker:

                        bid =
                            conservativeAuctionDecision(
                                i,
                                propertyIndex,
                                currentBid
                            );

                        break;


                    case riskTaker:

                        bid =
                            riskTakerAuctionDecision(
                                i,
                                propertyIndex,
                                currentBid
                            );

                        break;


                    case opportunisticTrader:

                        bid =
                            opportunisticAuctionDecision(
                                i,
                                propertyIndex,
                                currentBid
                            );

                        break;
                }


                /*
                 * Player made a valid higher bid.
                 */

                if(bid > currentBid &&
                   bid <= players[i].money)
                {
                    currentBid = bid;

                    highestBidder = i;

                    bidMade = 1;

                    printf("%s bids LKR %d\n",
                           players[i].name,
                           currentBid);
                }

                /*
                 * Player cannot or does not want
                 * to continue.
                 */

                else
                {
                    activePlayers[i] = 0;

                    printf("%s withdraws from the auction.\n",
                           players[i].name);
                }
            }
        }


        /*
         * Nobody made a new bid.
         */

        if(bidMade == 0)
        {
            break;
        }


        /*
         * Count remaining active players.
         */

        activeCount = 0;

        for(i = 0; i < 4; i++)
        {
            if(activePlayers[i] == 1)
            {
                activeCount++;
            }
        }


        /*
         * Only one player remains.
         */

        if(activeCount == 1 &&
           highestBidder != -1)
        {
            break;
        }
    }


    /*
     * Nobody placed a bid.
     *
     * Property remains with the Bank.
     */

    if(highestBidder == -1)
    {
        printf("\nNo player placed a bid.\n");

        printf("%s remains with the Bank.\n\n",
               properties[propertyIndex].name);

        return;
    }


    /*
     * Deduct winning bid from winner.
     */

    players[highestBidder].money -= currentBid;

    //players[highestBidder].taxableMoney -= currentBid;


    /*
     * Give property to winner.
     */

    properties[propertyIndex].hasOwner = 1;

    properties[propertyIndex].owner =
        players[highestBidder].playerID;


    /*
     * Add property to player's property list.
     */

    /*
 * Add property to player's property list.
 */

if(players[highestBidder].ownedPropertiesCount < 22)
{
    players[highestBidder].ownedProperties[
        players[highestBidder].ownedPropertiesCount
    ] =
        properties[propertyIndex].squareNumber;

    players[highestBidder].ownedPropertiesCount++;
}


    printf("\n========================================\n");

    printf("Auction Result\n");

    printf("Winner : %s\n",
           players[highestBidder].name);

    printf("Property : %s\n",
           properties[propertyIndex].name);

    printf("Winning Bid : LKR %d\n",
           currentBid);

    printf("Remaining Balance : LKR %d\n",
           players[highestBidder].money);

    printf("========================================\n\n");
}

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

        /*
         * Only insure developed properties.
         */
        if(properties[i].houseCount == 0 &&
           properties[i].hotelCount == 0)
        {
            continue;
        }

        /*
         * Aggressive Investor:
         * Basic insurance for houses,
         * Comprehensive for hotels.
         */
        if(players[playerID].playerID ==
           aggresiveInvestor)
        {
            if(properties[i].hotelCount > 0)
            {
                policyType =
                    comprehensiveInsurance;
            }
            else
            {
                policyType =
                    basicPropertyInsurance;
            }
        }

        /*
         * Conservative Banker:
         * Comprehensive insurance for every
         * developed property.
         */
        else if(players[playerID].playerID ==
                conservativeBanker)
        {
            policyType =
                comprehensiveInsurance;
        }

        /*
         * Risk Taker:
         * Only purchases insurance if the player
         * has already suffered a financial loss.
         *
         * For now, use low cash as the trigger.
         */
        else if(players[playerID].playerID ==
                riskTaker)
        {
            if(players[playerID].money >= 30000)
            {
                continue;
            }

            policyType =
                comprehensiveInsurance;
        }

        /*
         * Opportunistic Trader:
         * Insure high-value developments.
         */
        else
        {
            if(properties[i].currentPrice < 7000)
            {
                continue;
            }

            policyType =
                comprehensiveInsurance;
        }

        /*
         * Do not buy another policy if the
         * property is already insured.
         */
        if(properties[i].isInsured)
        {
            continue;
        }

        if(purchaseInsurance(playerID,
                             i,
                             policyType))
        {
            /*
             * One insurance purchase per visit.
             */
            break;
        }
    }
}

int countUndevelopedProperties(int playerID)
{
    int i = 0;
    int count = 0;

    while(i < players[playerID].ownedPropertiesCount)
    {
        int squareNumber = players[playerID].ownedProperties[i];
        int j = 0;

        while(j < 22)
        {
            if(properties[j].squareNumber == squareNumber)
            {
                if(properties[j].houseCount == 0 &&
                   properties[j].hotelCount == 0)
                {
                    count++;
                }

                break;
            }

            j++;
        }

        i++;
    }

    return count;
}






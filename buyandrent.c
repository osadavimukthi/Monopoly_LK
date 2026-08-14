#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "types.h"
#include "players.h"
#include "board.h"
#include "finance.h"
#include "auctions.h"


void propertyBuyRent(int playerSquare, int k)
{
    int l = 0;

    while(l < 22)
    {
        if(playerSquare == properties[l].squareNumber)
        {
            if(properties[l].hasOwner == 0)
            {
                if(playerPurchaseDecision(k, l))
                {
                    properties[l].hasOwner = 1;
                    properties[l].owner = players[k].playerID;
                    players[k].money -= properties[l].currentPrice;
                    players[k].taxableMoney -= properties[l].currentPrice;
                    players[k].ownedProperties[players[k].ownedPropertiesCount] = properties[l].squareNumber;
                    players[k].ownedPropertiesCount++;

                    printf("%s purchased %s for LKR %d.\n",players[k].name,properties[l].name,properties[l].currentPrice);

                    printf("Remaining Balance : LKR %d.\n\n",players[k].money);
                }
                else
                {

                    printf("%s declined to purchase %s.\n",players[k].name,properties[l].name);
                    printf("Property enters auction.\n\n");
                    auctionProperty(l);
                }
            }
            else
            {
                if(properties[l].owner != players[k].playerID)
                {
                    printf("%s is already owned.\n",properties[l].name);

                    printf("%s landed on %s.\n",players[k].name,properties[l].name);

                    printf("Rent paid : LKR %d.\n",properties[l].currentRent);

                    printf("Owner : %s.\n\n",players[properties[l].owner].name);

                    players[k].money -= properties[l].currentRent;
                    players[k].taxableMoney -= properties[l].currentRent;

                    players[properties[l].owner].money += properties[l].currentRent;
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
                    players[k].taxableMoney -= railways[l].currentPrice;

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

                                printf("Base rent of %s is LKR %d \n", railways[i].name, railways[i].currentRent);
                            }
                        }

                        printf("\n");
                    }
                    else if(players[k].ownedRailwayCount == 4)
                    {
                        printf("%s owns all 4 railways! \n\n", players[k].name);

                        for(int i = 0; i < 4; i++)
                        {
                            if(railways[i].owner == players[k].playerID)
                            {
                                railways[i].currentRent = 2000;

                                printf("Base rent of %s is LKR %d \n", railways[i].name, railways[i].currentRent);
                            }
                        }

                        printf("\n");
                    }
                }
                else
                {
                    printf("%s declined to purchase %s.\n\n", players[k].name, railways[l].name);
                }
            }
            else
            {
                if(railways[l].owner != players[k].playerID)
                {
                    printf("%s is already owned.\n", railways[l].name);

                    printf("%s landed on %s \n", players[k].name, railways[l].name);

                    printf("Rent paid : %d \n", railways[l].currentRent);

                    printf("Owner : %s \n\n",players[railways[l].owner].name);

                    players[k].money -= railways[l].currentRent;
                    players[k].taxableMoney -= railways[l].currentRent;

                    players[railways[l].owner].money += railways[l].currentRent;
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
                    players[k].taxableMoney -= utilities[l].currentPrice;

                    players[k].ownedUtilities[players[k].ownedUtilitiesCount] = utilities[l].squareNumber;
                    players[k].ownedUtilitiesCount++;

                    printf("%s purchased %s for LKR %d.\n\n",players[k].name,utilities[l].name,utilities[l].currentPrice);
                }
                else
                {
                    printf("%s declined to purchase %s.\n\n",players[k].name,utilities[l].name);
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

                if(utilities[l].owner != players[k].playerID)
                {
                    printf("%s is already owned.\n",utilities[l].name);

                    printf("%s landed on %s \n",players[k].name,utilities[l].name);

                    printf("Rent paid : %d \n",utilities[l].currentRent);

                    printf("Owner : %s \n\n",players[utilities[l].owner].name);

                    players[k].money -= utilities[l].currentRent;
                    players[k].taxableMoney -= utilities[l].currentRent;

                    players[utilities[l].owner].money +=utilities[l].currentRent;
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

void payTax(int playerSquare ,int k)
{   
    if(playerSquare == 4)
    {
        double tax = players[k].taxableMoney * rates.incomeTaxRate / 100.0;
        players[k].money-=(int)tax;
        printf("Paid Tax : %d \n\n",(int)tax);
        players[k].taxableMoney =0;

    }
}


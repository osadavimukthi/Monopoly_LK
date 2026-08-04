#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "types.h"
#include "players.h"
#include "board.h"

void propertyBuyRent(int playerSquare, int k)
{
    int l = 0;

    while(l < 22)
    {
        if(playerSquare == properties[l].squareNumber)
        {
            if(properties[l].hasOwner == 0)
            {
                if(players[k].money >= properties[l].currentPrice)
                {
                    properties[l].hasOwner = 1;
                    properties[l].owner = players[k].playerID;

                    players[k].money -= properties[l].currentPrice;

                    players[k].ownedProperties[players[k].ownedPropertiesCount] =
                        properties[l].squareNumber;
                    players[k].ownedPropertiesCount++;

                    printf("%s purchased %s for LKR %d.\n\n",
                           players[k].name,
                           properties[l].name,
                           properties[l].currentPrice);
                }
                else
                {
                    printf("%s doesn't have enough money to buy %s.\n\n",
                           players[k].name,
                           properties[l].name);
                }
            }
            else
            {
                printf("%s is already owned.\n", properties[l].name);
                printf("%s landed on %s \n", players[k].name, properties[l].name);
                printf("Rent paid : %d \n", properties[l].currentRent);
                printf("Owner : %s \n\n", players[properties[l].owner].name);
                players[k].money -= properties[l].currentRent;
                players[properties[l].owner].money += properties[l].currentRent;
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
                if(players[k].money >= railways[l].currentPrice)
                {
                    railways[l].hasOwner = 1;
                    railways[l].owner = players[k].playerID;

                    players[k].money -= railways[l].currentPrice;

                    players[k].ownedProperties[players[k].ownedPropertiesCount] =
                        railways    [l].squareNumber;
                    players[k].ownedRailwayCount++;

                    printf("%s purchased %s for LKR %d.\n\n",
                           players[k].name,
                           railways[l].name,
                           railways[l].currentPrice);
                    if(players[k].ownedRailwayCount == 1)
                    {
                        printf("%s owns 1 railway! \n\n", players[k].name);
                        printf("Base rent of %s is LKR %d \n\n", railways[l].name, railways[l].currentRent);

                    }
                    else if(players[k].ownedRailwayCount == 2)
                    {
                        printf("%s owns 2 railways! \n\n", players[k].name);
                        railways[l-1].currentRent = 500;
                        railways[l].currentRent = 500;
                        printf("Base rent of %s is LKR %d \n", railways[l-1].name, railways[l-1].currentRent);
                        printf("Base rent of %s is LKR %d \n\n", railways[l].name, railways[l].currentRent);

                    }
                    else if(players[k].ownedRailwayCount == 3)
                    {
                        printf("%s owns 3 railways! \n\n", players[k].name);
                        railways[l-2].currentRent = 1000;
                        railways[l-1].currentRent = 1000;
                        railways[l].currentRent = 1000;
                        printf("Base rent of %s is LKR %d \n", railways[l-2].name, railways[l-2].currentRent);
                        printf("Base rent of %s is LKR %d \n", railways[l-1].name, railways[l-1].currentRent);
                        printf("Base rent of %s is LKR %d \n\n", railways[l].name, railways[l].currentRent);

                    }
                    else if(players[k].ownedRailwayCount == 4)
                    {
                        printf("%s owns all 4 railways! \n\n", players[k].name);
                        railways[l-3].currentRent = 2000;
                        railways[l-2].currentRent = 2000;
                        railways[l-1].currentRent = 2000;
                        railways[l].currentRent = 2000;
                        printf("Base rent of %s is LKR %d \n", railways[l-3].name, railways[l-3].currentRent);
                        printf("Base rent of %s is LKR %d \n", railways[l-2].name, railways[l-2].currentRent);
                        printf("Base rent of %s is LKR %d \n", railways[l-1].name, railways[l-1].currentRent);
                        printf("Base rent of %s is LKR %d \n\n", railways[l].name, railways[l].currentRent);

                    }

                }

                else
                {
                    printf("%s doesn't have enough money to buy %s.\n\n",
                           players[k].name,
                           railways[l].name);
                }
            }
            else
            {
                printf("%s is already owned.\n", railways[l].name);
                printf("%s landed on %s \n", players[k].name, railways[l].name);
                printf("Rent paid : %d \n", railways[l].currentRent);
                printf("Owner : %s \n\n", players[railways[l].owner].name);
                players[k].money -= railways[l].currentRent;
                players[railways[l].owner].money += railways[l].currentRent;
            }

            break;
        }

        l++;
    }
}
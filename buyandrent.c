#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "types.h"
#include "players.h"
#include "board.h"
#define INCOMETAXRATE 0.15

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
                    players[k].taxableMoney -= properties[l].currentPrice;
                    players[k].ownedProperties[players[k].ownedPropertiesCount] =
                    properties[l].squareNumber;
                    players[k].ownedPropertiesCount++;
                    
                    printf("%s purchased %s for LKR %d.\n\n",players[k].name,properties[l].name,properties[l].currentPrice);
                }
                else
                {
                    printf("%s doesn't have enough money to buy %s.\n\n",players[k].name,properties[l].name);
                }
            }
            else
            {   
                if(properties[l].owner != players[k].playerID)
                {
                    printf("%s is already owned.\n", properties[l].name);
                    printf("%s landed on %s \n", players[k].name, properties[l].name);
                    printf("Rent paid : %d \n", properties[l].currentRent);
                    printf("Owner : %s \n\n", players[properties[l].owner].name);
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
                if(players[k].money >= railways[l].currentPrice)
                {
                    railways[l].hasOwner = 1;
                    railways[l].owner = players[k].playerID;

                    players[k].money -= railways[l].currentPrice;
                    players[k].taxableMoney -= railways[l].currentPrice;

                    players[k].ownedRailways[players[k].ownedRailwayCount] =
                    railways[l].squareNumber;
                    players[k].ownedRailwayCount++;

                    printf("%s purchased %s for LKR %d.\n\n",players[k].name,railways[l].name,railways[l].currentPrice);

                    if(players[k].ownedRailwayCount == 1)
                    {
                        printf("%s owns 1 railway! \n\n", players[k].name);

                        for(int i = 0; i < 4; i++)
                        {
                            if(railways[i].owner == players[k].playerID)
                            {
                                railways[i].currentRent = 250;

                                printf("Base rent of %s is LKR %d \n\n", railways[i].name, railways[i].currentRent);
                            }
                        }
                    }
                    else if(players[k].ownedRailwayCount == 2)
                    {
                        printf("%s owns 2 railways! \n\n", players[k].name);

                        for(int i = 0; i < 4; i++)
                        {
                            if(railways[i].owner == players[k].playerID)
                            {
                                railways[i].currentRent = 500;

                                printf("Base rent of %s is LKR %d \n", railways[i].name,railways[i].currentRent);
                            }
                        }

                        printf("\n");
                    }
                    else if(players[k].ownedRailwayCount == 3)
                    {
                        printf("%s owns 3 railways! \n\n", players[k].name);

                        for(int i = 0; i < 4; i++)
                        {
                            if(railways[i].owner == players[k].playerID)
                            {
                                railways[i].currentRent = 1000;

                                printf("Base rent of %s is LKR %d \n", railways[i].name,railways[i].currentRent);
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

                                printf("Base rent of %s is LKR %d \n",railways[i].name,railways[i].currentRent);
                            }
                        }

                        printf("\n");
                    }
                }
                else
                {
                    printf("%s doesn't have enough money to buy %s.\n\n",players[k].name,railways[l].name);
                }
            }
            else
            {
                if(railways[l].owner != players[k].playerID)
                {
                    printf("%s is already owned.\n", railways[l].name);
                    printf("%s landed on %s \n", players[k].name, railways[l].name);
                    printf("Rent paid : %d \n", railways[l].currentRent);
                    printf("Owner : %s \n\n", players[railways[l].owner].name);

                    players[k].money -= railways[l].currentRent;
                    players[k].taxableMoney -= railways[l].currentRent;
                    players[railways[l].owner].money += railways[l].currentRent;
                }
                else
                {
                    printf("%s landed on their own railway %s. No rent paid.\n\n",players[k].name,railways[l].name);
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
                if(players[k].money >= utilities[l].currentPrice)
                {
                    utilities[l].hasOwner = 1;
                    utilities[l].owner = players[k].playerID;

                    players[k].money -= utilities[l].currentPrice;
                    players[k].taxableMoney -= utilities[l].currentPrice;
                    players[k].ownedUtilities[players[k].ownedUtilitiesCount] =
                    utilities[l].squareNumber;
                    players[k].ownedUtilitiesCount++;

                    printf("%s purchased %s for LKR %d.\n\n",players[k].name,utilities[l].name,utilities[l].currentPrice);
                }
                else
                {
                    printf("%s doesn't have enough money to buy %s.\n\n",players[k].name,utilities[l].name);
                }
            }
            else
            {   
                if(utilities[0].hasOwner && utilities[1].hasOwner &&
                   utilities[0].owner == utilities[1].owner)
                {
                    utilities[l].rent = 10 * ( players[k].lastRoll1 + players[k].lastRoll2);
                }
                else
                {
                    utilities[l].rent = 4 * ( players[k].lastRoll1 + players[k].lastRoll2);
                }
                if(utilities[l].owner != players[k].playerID)
                {
                    printf("%s is already owned.\n", utilities[l].name);
                    printf("%s landed on %s \n", players[k].name, utilities[l].name);
                    printf("Rent paid : %d \n", utilities[l].rent);
                    printf("Owner : %s \n\n", players[utilities[l].owner].name);
                    players[k].money -= utilities[l].rent;
                    players[k].taxableMoney -= utilities[l].rent;
                    players[utilities[l].owner].money += utilities[l].rent;
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
        double tax = players[k].taxableMoney * INCOMETAXRATE;
        players[k].money-=(int)tax;
        printf("Paid Tax : %d \n\n",(int)tax);
        players[k].taxableMoney =0;

    }
}

void checkMonopoly(int k)
{
    int monopoly = 0;

    /* Brown */
    if(properties[0].owner == players[k].playerID &&
       properties[1].owner == players[k].playerID)
    {
        monopoly = 1;
        printf("%s owns the Brown monopoly.\n", players[k].name);
    }

    /* Light Blue */
    if(properties[2].owner == players[k].playerID &&
       properties[3].owner == players[k].playerID &&
       properties[4].owner == players[k].playerID)
    {
        monopoly = 1;
        printf("%s owns the Light Blue monopoly.\n", players[k].name);
    }

    /* Pink */
    if(properties[5].owner == players[k].playerID &&
       properties[6].owner == players[k].playerID &&
       properties[7].owner == players[k].playerID)
    {
        monopoly = 1;
        printf("%s owns the Pink monopoly.\n", players[k].name);
    }

    /* Orange */
    if(properties[8].owner == players[k].playerID &&
       properties[9].owner == players[k].playerID &&
       properties[10].owner == players[k].playerID)
    {
        monopoly = 1;
        printf("%s owns the Orange monopoly.\n", players[k].name);
    }
    /* Red */
    if(properties[11].owner == players[k].playerID &&
       properties[12].owner == players[k].playerID &&
       properties[13].owner == players[k].playerID)
    {
        monopoly = 1;
        printf("%s owns the Red monopoly.\n", players[k].name);
    }
    /* Yellow */
    if(properties[14].owner == players[k].playerID &&
       properties[15].owner == players[k].playerID &&
       properties[16].owner == players[k].playerID)
    {
        monopoly = 1;
        printf("%s owns the Yellow monopoly.\n", players[k].name);
    }
    /* Green */
    if(properties[17].owner == players[k].playerID &&
       properties[18].owner == players[k].playerID &&
       properties[19].owner == players[k].playerID)
    {
        monopoly = 1;
        printf("%s owns the Green monopoly.\n", players[k].name);
    }
    /* Dark Blue */
    if(properties[20].owner == players[k].playerID &&
       properties[21].owner == players[k].playerID)
    {
        monopoly = 1;
        printf("%s owns the Dark Blue monopoly.\n", players[k].name);
    }
}
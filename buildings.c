#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "types.h"
#include "players.h"
#include "board.h"
#include "buyandrent.h"
#include "buildings.h"

void checkMonopoly(int k)
{
    /* Brown */
    if(properties[0].owner == players[k].playerID &&
       properties[1].owner == players[k].playerID)
    {
        printf("%s owns the Brown monopoly.\n", players[k].name);
    }

    /* Light Blue */
    if(properties[2].owner == players[k].playerID &&
       properties[3].owner == players[k].playerID &&
       properties[4].owner == players[k].playerID)
    {
        printf("%s owns the Light Blue monopoly.\n", players[k].name);
    }

    /* Pink */
    if(properties[5].owner == players[k].playerID &&
       properties[6].owner == players[k].playerID &&
       properties[7].owner == players[k].playerID)
    {
        printf("%s owns the Pink monopoly.\n", players[k].name);
    }

    /* Orange */
    if(properties[8].owner == players[k].playerID &&
       properties[9].owner == players[k].playerID &&
       properties[10].owner == players[k].playerID)
    {
        printf("%s owns the Orange monopoly.\n", players[k].name);
    }

    /* Red */
    if(properties[11].owner == players[k].playerID &&
       properties[12].owner == players[k].playerID &&
       properties[13].owner == players[k].playerID)
    {
        printf("%s owns the Red monopoly.\n", players[k].name);
    }

    /* Yellow */
    if(properties[14].owner == players[k].playerID &&
       properties[15].owner == players[k].playerID &&
       properties[16].owner == players[k].playerID)
    {
        printf("%s owns the Yellow monopoly.\n", players[k].name);
    }

    /* Green */
    if(properties[17].owner == players[k].playerID &&
       properties[18].owner == players[k].playerID &&
       properties[19].owner == players[k].playerID)
    {
        printf("%s owns the Green monopoly.\n", players[k].name);
    }

    /* Dark Blue */
    if(properties[20].owner == players[k].playerID &&
       properties[21].owner == players[k].playerID)
    {
        printf("%s owns the Dark Blue monopoly.\n", players[k].name);
    }
}


int checkPropertyMonopoly(int k, int i)
{
    int monopoly = 0;

    /* Brown */
    if(i == 0 || i == 1)
    {
        if(properties[0].owner == players[k].playerID &&
           properties[1].owner == players[k].playerID)
        {
            monopoly = 1;
        }
    }

    /* Light Blue */
    if(i == 2 || i == 3 || i == 4)
    {
        if(properties[2].owner == players[k].playerID &&
           properties[3].owner == players[k].playerID &&
           properties[4].owner == players[k].playerID)
        {
            monopoly = 1;
        }
    }

    /* Pink */
    if(i == 5 || i == 6 || i == 7)
    {
        if(properties[5].owner == players[k].playerID &&
           properties[6].owner == players[k].playerID &&
           properties[7].owner == players[k].playerID)
        {
            monopoly = 1;
        }
    }

    /* Orange */
    if(i == 8 || i == 9 || i == 10)
    {
        if(properties[8].owner == players[k].playerID &&
           properties[9].owner == players[k].playerID &&
           properties[10].owner == players[k].playerID)
        {
            monopoly = 1;
        }
    }

    /* Red */
    if(i == 11 || i == 12 || i == 13)
    {
        if(properties[11].owner == players[k].playerID &&
           properties[12].owner == players[k].playerID &&
           properties[13].owner == players[k].playerID)
        {
            monopoly = 1;
        }
    }

    /* Yellow */
    if(i == 14 || i == 15 || i == 16)
    {
        if(properties[14].owner == players[k].playerID &&
           properties[15].owner == players[k].playerID &&
           properties[16].owner == players[k].playerID)
        {
            monopoly = 1;
        }
    }

    /* Green */
    if(i == 17 || i == 18 || i == 19)
    {
        if(properties[17].owner == players[k].playerID &&
           properties[18].owner == players[k].playerID &&
           properties[19].owner == players[k].playerID)
        {
            monopoly = 1;
        }
    }

    /* Dark Blue */
    if(i == 20 || i == 21)
    {
        if(properties[20].owner == players[k].playerID &&
           properties[21].owner == players[k].playerID)
        {
            monopoly = 1;
        }
    }

    return monopoly;
}


void buildHouse(int k, int squareNumber)
{
    int i = 0;

    while(i < 22)
    {
        if(properties[i].squareNumber == squareNumber)
        {
            if(checkPropertyMonopoly(k, i))
            {
                if(properties[i].houseCount < 4)
                {
                    if(players[k].money >= properties[i].houseConstructionCost)
                    {
                        properties[i].houseCount++;

                        players[k].money -=
                            properties[i].houseConstructionCost;

                        printf("%s built a house on %s. Total houses: %d\n",
                               players[k].name,
                               properties[i].name,
                               properties[i].houseCount);

                        switch(properties[i].houseCount)
                        {
                            case 1:
                                properties[i].currentRent =
                                    properties[i].baseRent * 2;
                                break;

                            case 2:
                                properties[i].currentRent =
                                    properties[i].baseRent * 3;
                                break;

                            case 3:
                                properties[i].currentRent =
                                    properties[i].baseRent * 5;
                                break;

                            case 4:
                                properties[i].currentRent =
                                    properties[i].baseRent * 7;
                                break;
                        }

                        printf("New rent for %s is LKR %d\n\n",
                               properties[i].name,
                               properties[i].currentRent);
                    }
                    else
                    {
                        printf("%s doesn't have enough money to build a house on %s.\n\n",
                               players[k].name,
                               properties[i].name);
                    }
                }
                else
                {
                    printf("%s already has 4 houses on %s.\n\n",
                           players[k].name,
                           properties[i].name);
                }
            }
            else
            {
                printf("%s cannot build a house on %s because the player does not own the complete monopoly.\n\n",
                       players[k].name,
                       properties[i].name);
            }

            break;
        }

        i++;
    }
}
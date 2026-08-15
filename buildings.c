#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "types.h"
#include "players.h"
#include "board.h"
#include "buyandrent.h"
#include "buildings.h"

int checkMonopoly(int playerID, int colorGroup)
{
    int i;
    int monopolyIndex = -1;
    int ownedCount = 0;

    for(i = 0; i < 8; i++)
    {
        if(monopolies[i].monopolyColor == colorGroup)
        {
            monopolyIndex = i;
            break;
        }
    }

    if(monopolyIndex == -1)
    {
        return 0;
    }

    for(i = 0; i < 22; i++)
    {
        if(properties[i].colorGroup == colorGroup &&
           properties[i].owner == playerID)
        {
            ownedCount++;
        }
    }

    if(ownedCount == monopolies[monopolyIndex].monopolyCount)
    {
        
        if(monopolies[monopolyIndex].hasOwner == 0)
        {
            monopolies[monopolyIndex].hasOwner = 1;
            monopolies[monopolyIndex].owner = playerID;

            printf("\n============================================\n");
            printf("MONOPOLY OBTAINED!\n");
            printf("%s has obtained the monopoly of Group %d.\n", players[playerID].name, colorGroup);
            printf("============================================\n\n");
        }
        else
        {
            monopolies[monopolyIndex].hasOwner = 1;
            monopolies[monopolyIndex].owner = playerID;
        }

        return 1;
    }

    monopolies[monopolyIndex].hasOwner = 0;
    monopolies[monopolyIndex].owner = -1;

    return 0;
}

int constructHouse(int k, int propertyIndex)
{
    if(properties[propertyIndex].isClosed == 1)
    {
        printf("%s is closed for business. Cannot construct house.\n", properties[propertyIndex].name);
        return 0;
    }

    if(players[k].money < properties[propertyIndex].houseConstructionCost)
    {
        return 0;
    }

    if(properties[propertyIndex].houseCount >= 4)
    {
        return 0;
    }

    players[k].money -= properties[propertyIndex].houseConstructionCost;

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
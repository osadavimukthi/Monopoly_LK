#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "types.h"

void setNewEconomicEventt()
{
    printf("A new Economic Event has started \n\n");
        int events[8] = {1,2,3,4,5,6,7,8};
        int a=0;
        srand(time(NULL));
        int randomEvent = rand() % 8;
        gameInfo.previousEconomicEvent = gameInfo.currentEconomicEvent;
        gameInfo.currentEconomicEvent = randomEvent;
        switch(randomEvent){
            case 1:
                a=0;
                printf("Economic Event : Tourism Boom\n");
                while(a<22){
                    printf("Hotels recieve double Rent\n");
                    if(properties[a].hotelCount==1){
                        properties[a].currentRent = properties[a].currentRent * 2;
                    }
                    printf("Southern costal property price increased by 15%\n");
                    if(properties[a].colorGroup==5)
                    {
                        properties[a].currentPrice = properties[a].currentPrice * 1.15;
                    }
                    a++;
                }
                break;

            case 2:
                printf("Economic Event : Fuel Crisis\n");
                printf("Railways recieve double Rent\n");
                a=0;
                while(a<4){
                    railways[a].currentRent = railways[a].currentRent * 2;
                    a++;
                }
                a = 0;
                printf("Property development costs increased by 20%\n");
                while(a<22){
                    properties[a].houseConstructionCost = properties[a].houseConstructionCost * 1.2;
                    properties[a].hotelConstructionCost = properties[a].hotelConstructionCost * 1.2;
                    a++;
                }
                break;

            case 3:
                printf("Economic Event : Heavy Mansoon\n");
                //implement inccreasement of flood risk
                //wrong percentage
                printf("Insuarence premiums increased by 30%\n");
                a=0;
                while(a<3)
                {
                    insurance[a].insurancePremium = insurance[a].insurancePremium * 13 / 10;
                    a++;
                }
                printf("Southern costal property price decreased by 10%\n");
                    if(properties[a].colorGroup==5)
                    {
                        properties[a].currentPrice = properties[a].currentPrice * 9 / 10;
                    }

                break;

            case 4:
                printf("Econoomic Event : Economic Recession\n");
                printf("All property prices decreased by 15%\n");
                a=0;
                while(a<22){
                    properties[a].currentPrice = properties[a].currentPrice * 0.85;
                    a++;
                }
                printf("Rent decreased by 10%\n");
                a=0;
                while(a<22){
                    properties[a].currentRent = properties[a].currentRent * 0.9;
                    a++;
                }
                a=0;
                while(a<4){
                    railways[a].currentRent = railways[a].currentRent * 0.9;
                    a++;
                }
                a=0;
                while(a<2){
                    utilities[a].currentRent = utilities[a].currentRent * 0.9;
                    a++;
                }
                a=0;
                printf("Loan interest rates increased by 15%\n");
                while(a<4){
                    rates.interestRate = rates.interestRate * 115 / 100;
                    a++;
                }
                break;

            case 5:
                printf("Economic Event : Stock Market Boom\n");
                printf("All property prices increased by 10%\n");
                a=0;
                while(a<22){
                    properties[a].currentPrice = properties[a].currentPrice * 1.1;
                    a++;
                }
                printf("loan interest rates decreased by 10%\n");
                a=0;
                while(a<4){
                    rates.interestRate = rates.interestRate * 90 / 100;
                    a++;
                }
                break;
            
            case 6:
                printf("Economic Event : Government Housing Programme\n");
                printf("House construction cost decreased by 25%\n");
                a=0;
                while(a<22){
                    properties[a].houseConstructionCost = properties[a].houseConstructionCost * 0.75;
                    a++;
                }
                break;
            case 7:
                printf("Economic Event : Foreign Investment\n");
                printf("Commercial property prices increased by 20%\n");
                a=0;
                //not implemented
                break;

            case 8:
                printf("Economic Event : Political Unrest\n");
                printf("Riot Probability doubled\n");
                //not implemented
                printf("Hotel occupancy and hotel rent decreased by 50%\n");
                //not mentioned about hotel occupancy in assignment
                a=0;
                while(a<22){
                    if(properties[a].hotelCount==1){
                        properties[a].currentRent = properties[a].currentRent * 0.5;
                    }
                printf("Business Interuption Claims increased.\n");
                //not implemented
                a++;

                }
    }
}

void resetCurrentEconomicEvent()
{
    int a=0;
    printf("Economic Event has ended\n");
    switch(gameInfo.currentEconomicEvent){
        case 1:
            while(a<22){
                if(properties[a].hotelCount==1){
                    properties[a].currentRent = properties[a].currentRent / 2;
                }
                if(properties[a].colorGroup==5)
                {
                    properties[a].currentPrice = properties[a].currentPrice / 1.15;
                }
                a++;
            }
            break;
        case 2:
            while(a<4){
                railways[a].currentRent = railways[a].currentRent / 2;
                a++;
            }
            a=0;
            while(a<22){
                properties[a].houseConstructionCost = properties[a].houseConstructionCost / 1.2;
                properties[a].hotelConstructionCost = properties[a].hotelConstructionCost / 1.2;
                a++;
            }
            break;
        case 3:
            while(a<3)
            {
                insurance[a].insurancePremium = insurance[a].insurancePremium * 10 / 13;
                a++;
            }
            a=0;
            while(a<22){
                if(properties[a].colorGroup==5)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 10 / 9;
                }
                a++;
            }
            break;
        case 4:
            while(a<22){
                properties[a].currentPrice = properties[a].currentPrice / 0.85;
                a++;
            }
            a=0;
            while(a<22){
                properties[a].currentRent = properties[a].currentRent / 0.9;
                a++;
            }
            a=0;
            while(a<4){
                railways[a].currentRent = railways[a].currentRent / 0.9;
                a++;
            }
}   
}

void economicEvents(int roundNumber)
{
    if(gameInfo.gameRound !=0 && roundNumber % 15 == 0)
    {
        resetCurrentEconomicEvent();
        setNewEconomicEventt();
    }

}

void setNewGovernmentRegulations(){
    printf("Goverment Regulation Change has been implemented\n");
        int regulations[8] = {1,2,3,4,5,6,7,8};
        int a=0;
        int i;
        srand(time(NULL));
        int randomRegulation = rand() % 8;
        gameInfo.previousGovernmentRegulation = gameInfo.currentGovernmentRegulation;
        gameInfo.currentGovernmentRegulation = randomRegulation;
        switch(randomRegulation)
{
    case 1:
        printf("Government Regulation : Increase Property Tax\n");

        rates.incomeTaxRate =
            rates.incomeTaxRate * 150 / 100;

        break;


    case 2:
        printf("Government Regulation : Reduce Loan Interest\n");

        rates.interestRate =
            rates.interestRate - 2;

        break;


    case 3:
        printf("Government Regulation : Housing Subsidy\n");

        for(a = 0; a < 22; a++)
        {
            properties[a].houseConstructionCost =
                properties[a].houseConstructionCost * 70 / 100;
        }

        break;


    case 4:
        printf("Government Regulation : Luxury Property Tax\n");

        for(a = 0; a < 22; a++)
        {
            if(properties[a].hotelCount > 0)
            {
                /* Annual maintenance tax will be handled here */
            }
        }

        break;


    case 5:
        printf("Government Regulation : Railway Modernization\n");

        for(a = 0; a < 4; a++)
        {
            railways[a].currentRent =
                railways[a].currentRent * 125 / 100;
        }

        break;


    case 6:
        printf("Government Regulation : Electricity Tariff Revision\n");

        for(a = 0; a < 2; a++)
        {
            utilities[a].currentRent =
                utilities[a].currentRent * 120 / 100;
        }

        break;


    case 7:
        printf("Government Regulation : Insurance Regulation\n");

        for(a = 0; a < 3; a++)
        {
            insurance[a].insurancePremium =
                insurance[a].insurancePremium * 85 / 100;
        }

        break;


    case 8:
        printf("Government Regulation : Anti-Speculation Act\n");

        /* Rule will be checked when a player attempts
           to purchase an undeveloped property. */

        break;
}
}

void resetCurrentGovernmentRegulations()
{
    int a = 0;

    printf("Government Regulation Change has ended.\n");

    switch(gameInfo.currentGovernmentRegulation)
    {
        case 1:
            rates.incomeTaxRate =
                rates.incomeTaxRate * 100 / 150;

            break;
        case 2:
            rates.interestRate =
                rates.interestRate + 2;

            break;
        case 3:
            for(a = 0; a < 22; a++)
            {
                properties[a].houseConstructionCost =
                    properties[a].houseConstructionCost * 100 / 70;
            }

            break;
        case 4:
            /* Annual maintenance tax will be handled here */

            break;
        case 5:
            for(a = 0; a < 4; a++)  
            {
                railways[a].currentRent =
                    railways[a].currentRent * 100 / 125;
            }
            break;
        case 6:
            for(a = 0; a < 2; a++)
            {
                utilities[a].currentRent =
                    utilities[a].currentRent * 100 / 120;
            }
            break;
        case 7:
            for(a = 0; a < 3; a++)
            {
                insurance[a].insurancePremium =
                    insurance[a].insurancePremium * 100 / 85;
            }
            break;
        case 8:
            /* Rule will be checked when a player attempts
               to purchase an undeveloped property. */

            break;   
    }
}

void governmentRegulations(int roundNumber)
{   
    
    if(gameInfo.gameRound !=0 && roundNumber % 20 == 0)
    {
        resetCurrentGovernmentRegulations();
        setNewGovernmentRegulations();

    }
}

void marketBoom(int PropertyColor)
{
    int i = 0;

    while(i < 22)
    {
        if(properties[i].colorGroup == PropertyColor)
        {
            properties[i].currentPrice =
                properties[i].currentPrice * 1.15;

            properties[i].mortgagedValue =
                properties[i].mortgagedValue * 1.15;

            properties[i].currentRent =
                properties[i].currentRent * 1.25;

            properties[i].houseConstructionCost =
                properties[i].houseConstructionCost * 1.10;

            properties[i].hotelConstructionCost =
                properties[i].hotelConstructionCost * 1.10;

            /*
             * Rule-LK 31
             *
             * Purchase price       +15%
             * Mortgage value       +15%
             * Rental income        +25%
             * Construction costs   +10%
             *
             * Property value +20% is not implemented here
             * because the current property structure does not
             * contain a separate property-value field.
             */

            printf("Property Color %d has entered a market boom\n",
                   PropertyColor);

            printf("Property %s has increased in price by 15%%\n",
                   properties[i].name);

            printf("Property %s has increased in rent by 25%%\n",
                   properties[i].name);

            printf("Property %s has increased in construction cost by 10%%\n",
                   properties[i].name);

            printf("Property %s has increased in mortgaged value by 15%%\n",
                   properties[i].name);
        }

        i++;
    }
}


void marketDecline(int PropertyColor)
{
    int i = 0;

    while(i < 22)
    {
        if(properties[i].colorGroup == PropertyColor)
        {
            properties[i].currentPrice =
                properties[i].currentPrice * 0.85;

            properties[i].mortgagedValue =
                properties[i].mortgagedValue * 0.90;

            properties[i].currentRent =
                properties[i].currentRent * 0.80;

            properties[i].auctionStartingPrice =
                properties[i].auctionStartingPrice * 0.75;

            /*
             * Rule-LK 32
             *
             * Property value          -15%
             * Rental income           -20%
             * Mortgage value          -10%
             * Auction starting price  -25%
             *
             * currentPrice is being used here for the
             * available property price field in your structure.
             */

            printf("Property Color %d has entered a market decline\n",
                   PropertyColor);

            printf("Property %s has decreased in price by 15%%\n",
                   properties[i].name);

            printf("Property %s has decreased in rent by 20%%\n",
                   properties[i].name);

            printf("Property %s has decreased in auction starting price by 25%%\n",
                   properties[i].name);

            printf("Property %s has decreased in mortgaged value by 10%%\n",
                   properties[i].name);
        }

        i++;
    }
}


void reversePreviousMarketBoom(int PropertyColor)
{
    int i = 0;

    while(i < 22)
    {
        if(properties[i].colorGroup == PropertyColor)
        {
            properties[i].currentPrice =
                properties[i].currentPrice / 1.15;

            properties[i].mortgagedValue =
                properties[i].mortgagedValue / 1.15;

            properties[i].currentRent =
                properties[i].currentRent / 1.25;

            properties[i].houseConstructionCost =
                properties[i].houseConstructionCost / 1.10;

            properties[i].hotelConstructionCost =
                properties[i].hotelConstructionCost / 1.10;
        }

        i++;
    }
}


void reversePreviousMarketDecline(int PropertyColor)
{
    int i = 0;

    while(i < 22)
    {
        if(properties[i].colorGroup == PropertyColor)
        {
            properties[i].currentPrice =
                properties[i].currentPrice / 0.85;

            properties[i].mortgagedValue =
                properties[i].mortgagedValue / 0.90;

            properties[i].currentRent =
                properties[i].currentRent / 0.80;

            properties[i].auctionStartingPrice =
                properties[i].auctionStartingPrice / 0.75;
        }

        i++;
    }
}


void dynamicPropertyMarkrt(int roundNumber)
{
    if(roundNumber % 10 == 0 && roundNumber != 0)
    {
        int propertyGroupList[8] =
        {
            Brown,
            LightBlue,
            Pink,
            Orange,
            Red,
            Yellow,
            Green,
            DarkBlue
        };

        int marketBoomPropertyColor = -1;
        int marketDeclinePropertyColor = -1;
        int randomColor;


        /*
         * Remove the previous Market Boom effect.
         */

        if(gameInfo.previousMarketBoomColor != -1)
        {
            printf("Reversing previous market boom affect ....\n");

            reversePreviousMarketBoom(
                gameInfo.previousMarketBoomColor
            );
        }


        /*
         * Remove the previous Market Decline effect.
         */

        if(gameInfo.previousMarketDeclineColor != -1)
        {
            printf("Reversing previous market decline affect ....\n");

            reversePreviousMarketDecline(
                gameInfo.previousMarketDeclineColor
            );
        }


        /*
         * Select Market Boom group.
         *
         * Rule-LK 33:
         * A group affected by either Boom or Decline
         * cannot be selected again until 30 rounds
         * have elapsed.
         */

        while(marketBoomPropertyColor == -1)
        {
            randomColor = rand() % 8;

            if(
                (propertyColors[propertyGroupList[randomColor]]
                    .marketBoomRound == 0
                ||
                roundNumber -
                propertyColors[propertyGroupList[randomColor]]
                    .marketBoomRound >= 30)

                &&

                (propertyColors[propertyGroupList[randomColor]]
                    .marketDeclineRound == 0
                ||
                roundNumber -
                propertyColors[propertyGroupList[randomColor]]
                    .marketDeclineRound >= 30)
            )
            {
                marketBoomPropertyColor =
                    propertyGroupList[randomColor];
            }
        }


        /*
         * Select Market Decline group.
         *
         * The Decline group MUST be different from
         * the Boom group.
         *
         * Rule-LK 33 is also checked here.
         */

        while(marketDeclinePropertyColor == -1)
        {
            randomColor = rand() % 8;

            if(
                propertyGroupList[randomColor] !=
                marketBoomPropertyColor
                &&

                (
                    propertyColors[propertyGroupList[randomColor]]
                        .marketBoomRound == 0
                    ||
                    roundNumber -
                    propertyColors[propertyGroupList[randomColor]]
                        .marketBoomRound >= 30
                )
                &&

                (
                    propertyColors[propertyGroupList[randomColor]]
                        .marketDeclineRound == 0
                    ||
                    roundNumber -
                    propertyColors[propertyGroupList[randomColor]]
                        .marketDeclineRound >= 30
                )
            )
            {
                marketDeclinePropertyColor =
                    propertyGroupList[randomColor];
            }
        }


        /*
         * Save previous market groups.
         */

        gameInfo.previousMarketBoomColor =
            gameInfo.currentMarketBoomColor;

        gameInfo.previousMarketDeclineColor =
            gameInfo.currentMarketDeclineColor;


        /*
         * Save current market groups.
         */

        gameInfo.currentMarketBoomColor =
            marketBoomPropertyColor;

        gameInfo.currentMarketDeclineColor =
            marketDeclinePropertyColor;


        /*
         * Record the round in which the groups
         * experienced the events.
         */

        propertyColors[marketBoomPropertyColor].marketBoomRound =
            roundNumber;

        propertyColors[marketDeclinePropertyColor].marketDeclineRound =
            roundNumber;


        /*
         * Activate Market Boom.
         */

        printf(
            "Activating new market boom for property color : %d\n",
            marketBoomPropertyColor
        );

        marketBoom(marketBoomPropertyColor);


        /*
         * Activate Market Decline.
         */

        printf(
            "Activating new market decline for property color : %d\n",
            marketDeclinePropertyColor
        );

        marketDecline(marketDeclinePropertyColor);
    }
}
void updateMarketRounds(int gameRound)
{
    int i;

    for(i = 0; i < 8; i++)
    {
        if(propertyColors[i].marketBoomRound != 0)
        {
            if(gameRound -
               propertyColors[i].marketBoomRound >= 30)
            {
                propertyColors[i].marketBoomRound = 0;
            }
        }

        if(propertyColors[i].marketDeclineRound != 0)
        {
            if(gameRound -
               propertyColors[i].marketDeclineRound >= 30)
            {
                propertyColors[i].marketDeclineRound = 0;
            }
        }
    }
}






/*
void shuffleEventCards()
{
    int numbers[20] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int i, j;
    int duplicate;

    srand(time(NULL));

    for(i = 0; i < 20; i++)
    {
        duplicate = 1;

        while(duplicate == 1)
        {
            numbers[i] = rand() % 20 + 1;
            duplicate = 0;

            for(j = 0; j < i; j++)
            {
                if(numbers[i] == numbers[j])
                {
                    duplicate = 1;
                    break;
                }
            }
        }
    }
}

void pickEventCard()
{
    switch(eventCards[0])
{
    case 1:
       
        printf("Event Card : Tourism Hype\n");
        printf("Hotels earn double rent for 5 rounds.\n");
        eventCardRound.tourismHype = 0;
        
        break;


    case 2:
    
        printf("Event Card : Fuel Shortage\n");
        printf("Railway rent doubles for 5 rounds.\n");

      
        break;


    case 3:
   
        printf("Event Card : Heavy Floods\n");

      
        break;


    case 4:
  
        printf("Event Card : Political Rally\n");

        break;


    case 5:
        
        printf("Event Card : Stock Market Rise\n");
        printf("All property values increase by 10%%.\n");

        
        break;


    case 6:
  
        printf("Event Card : Economic Downturn\n");
        printf("Property values decrease by 15%%.\n");

        break;


    case 7:
    
        printf("Event Card : Housing Subsidy\n");
        printf("House construction cost reduced by 30%%.\n");

        break;


    case 8:

        printf("Event Card : Interest Rate Cut\n");
        printf("Loan interest reduced by 2%%.\n");

        break;


    case 9:
   
        printf("Event Card : Interest Rate Increase\n");
        printf("Loan interest increased by 2%%.\n");

        break;


    case 10:
   
        printf("Event Card : Tax Amnesty\n");

        for(i = 0; i < 4; i++)
        {
            if(players[i].isBankrupt == 0)
            {
                players[i].money += 2000;
            }
        }

        printf("Each player receives LKR 2000.\n");
        break;


    case 11:
     
        printf("Event Card : Power Failure\n");
        printf("Utility income halved for 3 rounds.\n");

        break;


    case 12:
  
        printf("Event Card : Foreign Funding\n");
        printf("Commercial property values increase by 15%%.\n");

        break;


    case 13:
   
        printf("Event Card : Port Expansion\n");
        printf("Railway station values increase by 20%%.\n");

        break;


    case 14:
  
        printf("Event Card : Festival Season\n");
        printf("Hotels receive 50%% additional rent.\n");

        break;


    case 15:
      
        printf("Event Card : Labour Strike\n");
        printf("Construction suspended for 2 rounds.\n");

        
        break;


    case 16:
       
        printf("Event Card : Insurance Discount\n");
        printf("Insurance premiums reduced by 20%%.\n");

        
        break;


    case 17:
       
        printf("Event Card : Property Revaluation\n");

        
        break;


    case 18:
       
        printf("Event Card : Currency Depreciation\n");
        printf("Construction costs increase by 10%%.\n");

        break;


    case 19:
     
        printf("Event Card : Government Grant\n");

        i = rand() % 4;

        while(players[i].isBankrupt == 1)
        {
            i = rand() % 4;
        }

        players[i].money += 5000;

        printf("%s receives LKR 5000.\n",
               players[i].name);
        break;


    case 20:
        
        printf("Event Card : National Disaster\n");

  
        break;
}
}
*/
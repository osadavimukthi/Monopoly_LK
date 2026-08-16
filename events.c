#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "types.h"
#include "events.h"
#include "finance.h"

//economic events

void setNewEconomicEventt()
{
    printf("A new Economic Event has started\n\n");

    int a = 0;
    int randomEvent = rand() % 8 + 1;

    gameInfo.previousEconomicEvent = gameInfo.currentEconomicEvent;

    gameInfo.currentEconomicEvent = randomEvent;

    switch(randomEvent)
    {
        case 1:

            printf("Economic Event : Tourism Boom\n");
            printf("Hotels receive double Rent\n");
            printf("Southern coastal property price increased by 15%%\n");

            a = 0;

            while(a < 22)
            {
                if(properties[a].hotelCount > 0)
                {
                    properties[a].currentRent = properties[a].currentRent * 2;
                }

                if(properties[a].colorGroup == Yellow)
                {   
                    //assumed that the southern coastal properties are yellow group properties
                    properties[a].currentPrice = properties[a].currentPrice * 115 / 100;
                }

                a++;
            }

            break;


        case 2:

            printf("Economic Event : Fuel Crisis\n");
            printf("Railways receive double Rent\n");
            printf("Property development costs increased by 20%%\n");

            a = 0;

            while(a < 4)
            {
                railways[a].currentRent = railways[a].currentRent * 2;

                a++;
            }

            a = 0;

            while(a < 22)
            {
                properties[a].houseConstructionCost = properties[a].houseConstructionCost * 120 / 100;
                properties[a].hotelConstructionCost = properties[a].hotelConstructionCost * 120 / 100;

                a++;
            }

            break;


        case 3:

            printf("Economic Event : Heavy Monsoon\n");
            printf("Flood risk increased\n");
            printf("Insurance premiums increased\n");
            printf("Southern coastal property price decreased by 10%%\n");

            a = 0;

            while(a < 3)
            {
                insurance[a].insurancePremium = insurance[a].insurancePremium * 130 / 100;
                a++;
            }

            a = 0;

            while(a < 22)
            {
                if(properties[a].colorGroup == Yellow)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 90 / 100;
                }

                a++;
            }

            //flood risk increasement included in happenDisaster() function
            break;


        case 4:

            printf("Economic Event : Economic Recession\n");
            printf("All property prices decreased by 15%%\n");
            printf("Rent decreased by 10%%\n");
            printf("Loan interest rates increased by 15%%\n");

            a = 0;

            while(a < 22)
            {
                properties[a].currentPrice = properties[a].currentPrice * 85 / 100;

                properties[a].currentRent = properties[a].currentRent * 90 / 100;

                a++;
            }

            rates.interestRate = rates.interestRate * 115 / 100;
            break;

        case 5:

            printf("Economic Event : Stock Market Boom\n");
            printf("All property prices increased by 10%%\n");
            printf("Loan interest rates decreased by 10%%\n");

            a = 0;

            while(a < 22)
            {
                properties[a].currentPrice = properties[a].currentPrice * 110 / 100;

                a++;
            }
            rates.interestRate = rates.interestRate * 90 / 100;
            break;

        case 6:

            printf("Economic Event : Government Housing Programme\n");
            printf("House construction cost decreased by 25%%\n");

            a = 0;

            while(a < 22)
            {
                properties[a].houseConstructionCost = properties[a].houseConstructionCost * 75 / 100;
                a++;
            }
            break;

        case 7:

            printf("Economic Event : Foreign Investment\n");
            printf("Commercial property prices increased by 20%%\n");
            //assumed that all properties are economic properties
            a = 0;

            while(a < 22)
            {
                properties[a].currentPrice = properties[a].currentPrice * 120 / 100;
                a++;
            }

            break;

        case 8:

            printf("Economic Event : Political Unrest\n");
            printf("Riot probability doubled\n");
            printf("Hotel occupancy and hotel rent decreased by 50%%\n");
            printf("Business interruption claims increased\n");

            a = 0;

            while(a < 22)
            {
                if(properties[a].hotelCount > 0)
                {
                    properties[a].currentRent = properties[a].currentRent * 50 / 100;
                }

                a++;
            }

            //business interrpritatation premium handle inside insuarance
            //rioy probability handle inside happenDisaster() function
            break;
    }
}

void resetCurrentEconomicEvent()
{
    int a = 0;

    if(gameInfo.currentEconomicEvent == -1 ||
       gameInfo.currentEconomicEvent == 0)
    {
        return;
    }

    printf("Economic Event has ended.\n");

    switch(gameInfo.currentEconomicEvent)
    {
        case 1:
            a = 0;
            while(a < 22)
            {
                if(properties[a].hotelCount > 0)
                {
                    properties[a].currentRent = properties[a].currentRent / 2;
                }

                if(properties[a].colorGroup == Yellow)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 100 / 115;
                }

                a++;
            }

            break;


        case 2:
            a = 0;

            while(a < 4)
            {
                railways[a].currentRent = railways[a].currentRent / 2;
                a++;
            }

            a = 0;
            while(a < 22)
            {
                properties[a].houseConstructionCost = properties[a].houseConstructionCost * 100 / 120;

                properties[a].hotelConstructionCost = properties[a].hotelConstructionCost * 100 / 120;
                a++;
            }
            break;


        case 3:
            
            //flood risk decreasement included in happenDisaster() function
            a = 0;
            while(a < 3)
            {
                insurance[a].insurancePremium = insurance[a].insurancePremium * 100 / 130;
                a++;
            }

            a = 0;

            while(a < 22)
            {
                if(properties[a].colorGroup == Yellow)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 100 / 90;
                }
                a++;
            }

            break;


        case 4:

            a = 0;

            while(a < 22)
            {
                properties[a].currentPrice = properties[a].currentPrice * 100 / 85;
                properties[a].currentRent = properties[a].currentRent * 100 / 90;
                a++;
            }

            rates.interestRate = rates.interestRate * 100 / 115;
            break;


        case 5:
            a = 0;

            while(a < 22)
            {
                properties[a].currentPrice = properties[a].currentPrice * 100 / 110;
                a++;
            }
            rates.interestRate = rates.interestRate * 100 / 90;
            break;


        case 6:

            a = 0;

            while(a < 22)
            {
                properties[a].houseConstructionCost = properties[a].houseConstructionCost * 100 / 75;
                a++;
            }
            break;


        case 7:

            a = 0;

            while(a < 22)
            {
                properties[a].currentPrice = properties[a].currentPrice * 100 / 120;
                a++;
            }
            break;


        case 8:
            //riot probability handle inside happenDisaster() function
            a = 0;
            while(a < 22)
            {
                if(properties[a].hotelCount > 0)
                {
                    properties[a].currentRent = properties[a].currentRent * 100 / 50;
                }
                a++;
            }
            //business interrpritatation premium handle inside insuarance
            break;
    }

    gameInfo.currentEconomicEvent = 0;
}

void economicEvents(int roundNumber)
{
    if(gameInfo.gameRound !=0 && roundNumber % 15 == 0)
    {
        resetCurrentEconomicEvent();
        setNewEconomicEventt();
    }

}


//dynamic property market

void dynamicPropertyMarkrt(int roundNumber)
{
    if(roundNumber % 10 == 0 && roundNumber != 0)
    {
        int propertyGroupList[8] ={ Brown, LightBlue, Pink, Orange, Red, Yellow, Green, DarkBlue};

        int marketBoomPropertyColor = -1;
        int marketDeclinePropertyColor = -1;
        int randomColor;

        if(gameInfo.previousMarketBoomColor != -1)
        {
            printf("Reversing previous market boom affect ....\n");
            reversePreviousMarketBoom( gameInfo.previousMarketBoomColor );
            printf("\n");
        }

        if(gameInfo.previousMarketDeclineColor != -1)
        {
            printf("Reversing previous market decline affect ....\n");

            reversePreviousMarketDecline(gameInfo.previousMarketDeclineColor);
            printf("\n");
        }

        while(marketBoomPropertyColor == -1)
        {
            randomColor = rand() % 8;

            if(
                (propertyColors[propertyGroupList[randomColor]].marketBoomRound <= 0||
                roundNumber - propertyColors[propertyGroupList[randomColor]].marketBoomRound >= 30)
                &&
                (propertyColors[propertyGroupList[randomColor]].marketDeclineRound <= 0||
                roundNumber - propertyColors[propertyGroupList[randomColor]].marketDeclineRound >= 30)
            )
            {
                marketBoomPropertyColor = propertyGroupList[randomColor];
            }
        }

        while(marketDeclinePropertyColor == -1)
        {
            randomColor = rand() % 8;

            if( propertyGroupList[randomColor] != marketBoomPropertyColor &&
                ( propertyColors[propertyGroupList[randomColor]].marketBoomRound <= 0 ||
                    roundNumber - propertyColors[propertyGroupList[randomColor]].marketBoomRound >= 30)
                &&
                (
                    propertyColors[propertyGroupList[randomColor]] .marketDeclineRound <= 0 ||
                    roundNumber - propertyColors[propertyGroupList[randomColor]].marketDeclineRound >= 30
                )
            )
            {
                marketDeclinePropertyColor = propertyGroupList[randomColor];
            }
        }

        gameInfo.previousMarketBoomColor =gameInfo.currentMarketBoomColor;

        gameInfo.previousMarketDeclineColor =gameInfo.currentMarketDeclineColor;

        gameInfo.currentMarketBoomColor = marketBoomPropertyColor;

        gameInfo.currentMarketDeclineColor = marketDeclinePropertyColor;

        propertyColors[marketBoomPropertyColor].marketBoomRound = roundNumber;

        propertyColors[marketDeclinePropertyColor].marketDeclineRound = roundNumber;

        printf("Activating new market boom for property color : %d\n", marketBoomPropertyColor );

        marketBoom(marketBoomPropertyColor);
        
        printf("\n");

        printf( "Activating new market decline for property color : %d\n", marketDeclinePropertyColor );

        marketDecline(marketDeclinePropertyColor);

        printf("\n");
    }
}

void marketBoom(int PropertyColor)
{
    int i = 0;

    while(i < 22)
    {
        if(properties[i].colorGroup == PropertyColor)
        {
            //consided purchase price increase as the properties which dont have a owner 
            //its price additionally inclease by 15%
            if(properties[i].hasOwner == 0)
            {
                properties[i].currentPrice = properties[i].currentPrice * 1.15;
            }

            properties[i].mortgagedValue = properties[i].mortgagedValue * 1.15;

            properties[i].currentRent = properties[i].currentRent * 1.25;

            properties[i].houseConstructionCost = properties[i].houseConstructionCost * 1.10;

            properties[i].hotelConstructionCost = properties[i].hotelConstructionCost * 1.10;

            properties[i].currentPrice = properties[i].currentPrice * 1.20;

            printf("Property Color %d has entered a market boom\n", PropertyColor);

            printf("Property %s purchase price has increased by 20%%\n", properties[i].name);

            printf("Property %s has increased in rent by 25%%\n", properties[i].name);

            printf("Property %s has increased in construction cost by 10%%\n", properties[i].name);

            printf("Property %s has increased in mortgaged value by 15%%\n", properties[i].name);

            printf("Property %s has increased in price by 20%%\n",properties[i].name);
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
            properties[i].currentPrice = properties[i].currentPrice * 0.85;

            properties[i].mortgagedValue = properties[i].mortgagedValue * 0.90;

            properties[i].currentRent = properties[i].currentRent * 0.80;

            properties[i].auctionStartingPrice = properties[i].auctionStartingPrice * 0.75;

            printf("Property Color %d has entered a market decline\n", PropertyColor);

            printf("Property %s has decreased in price by 15%%\n", properties[i].name);

            printf("Property %s has decreased in rent by 20%%\n",  properties[i].name);

            printf("Property %s has decreased in auction starting price by 25%%\n", properties[i].name);

            printf("Property %s has decreased in mortgaged value by 10%%\n",  properties[i].name);
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
            
            if(properties[i].hasOwner == 0)
            {
                properties[i].currentPrice = properties[i].currentPrice / 1.15;
            }

            properties[i].mortgagedValue = properties[i].mortgagedValue / 1.15;

            properties[i].currentRent = properties[i].currentRent / 1.25;

            properties[i].houseConstructionCost = properties[i].houseConstructionCost / 1.10;

            properties[i].hotelConstructionCost = properties[i].hotelConstructionCost / 1.10;

            properties[i].currentPrice = properties[i].currentPrice / 1.20;
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
            properties[i].currentPrice = properties[i].currentPrice / 0.85;

            properties[i].mortgagedValue = properties[i].mortgagedValue / 0.90;

            properties[i].currentRent = properties[i].currentRent / 0.80;

            properties[i].auctionStartingPrice = properties[i].auctionStartingPrice / 0.75;
        }

        i++;
    }
}

void updateMarketRounds(int gameRound)
{
    int i;

    for(i = 0; i < 8; i++)
    {
        if(propertyColors[i].marketBoomRound != 0)
        {
            if(gameRound - propertyColors[i].marketBoomRound >= 30)
            {
                propertyColors[i].marketBoomRound = 0;
            }
        }

        if(propertyColors[i].marketDeclineRound != 0)
        {
            if(gameRound - propertyColors[i].marketDeclineRound >= 30)
            {
                propertyColors[i].marketDeclineRound = 0;
            }
        }
    }
}


//governmennt regulations

void governmentRegulations(int roundNumber)
{
    if(gameInfo.gameRound != 0 && roundNumber % 20 == 0)
    {
        resetCurrentGovernmentRegulations();
        setNewGovernmentRegulations();
    }
}

void setNewGovernmentRegulations()
{
    printf("Goverment Regulation Change has been implemented\n");

    int randomRegulation = rand() % 8 + 1;

    gameInfo.previousGovernmentRegulation = gameInfo.currentGovernmentRegulation;

    gameInfo.currentGovernmentRegulation = randomRegulation;

    switch(randomRegulation)
    {
        case 1:

            printf("Government Regulation : Increase Property Tax\n");

            rates.incomeTaxRate = rates.incomeTaxRate * 150 / 100;

            printf("Income Tax Rate increased by 50%%.\n");
            printf("New Income Tax Rate : %d%%\n\n",rates.incomeTaxRate);

            break;


        case 2:

            printf("Government Regulation : Reduce Loan Interest\n");

            rates.interestRate = rates.interestRate - 2;

            if(rates.interestRate < 0)
            {
                rates.interestRate = 0;
            }

            printf("Loan interest rate reduced by 2%%.\n");
            printf("New Loan Interest Rate : %d%%\n\n", rates.interestRate);

            break;


        case 3:

            printf("Government Regulation : Housing Subsidy\n");

            for(int a = 0; a < 22; a++)
            {
                properties[a].houseConstructionCost = properties[a].houseConstructionCost * 70 / 100;

                properties[a].hotelConstructionCost = properties[a].hotelConstructionCost * 70 / 100;
            }

            printf("House and hotel construction costs reduced by 30%%.\n\n");

            break;


        case 4:

            printf("Government Regulation : Luxury Property Tax\n");
            printf("Hotels are subject to a 25%% annual maintenance tax.\n\n");

            break;


        case 5:

            printf("Government Regulation : Railway Modernization\n");
            int a=0;
            while(a < 4)
            {
                railways[a].currentRent = railways[a].currentRent * 125 / 100;
                a++;
            }
            printf("Railway rent increased by 25%%.\n\n");

            break;


        case 6:

            printf("Government Regulation : Electricity Tariff Revision\n");
            printf("Utility rent increased by 20%%.\n\n");
            int b=0;
            while(b < 2)
            {
                utilities[b].currentRent = utilities[b].currentRent * 120 / 100;
                b++;
            }
            break;


        case 7:

            printf("Government Regulation : Insurance Regulation\n");
            int c=0;
            while(c < 3)
            {
                insurance[c].insurancePremium = insurance[c].insurancePremium * 85 / 100;
                c++;
            }
            printf("Insurance premiums reduced by 15%%.\n\n");
            break;


        case 8:

            printf("Government Regulation : Anti-Speculation Act\n");
            printf("Maximum of 3 undeveloped properties allowed.\n");
            printf("Additional properties must be developed within 5 rounds.\n\n");
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

            rates.incomeTaxRate = rates.incomeTaxRate * 100 / 150;
            break;

        case 2:

            rates.interestRate = rates.interestRate + 2;
            break;

        case 3:

            for(a = 0; a < 22; a++)
            {
                properties[a].houseConstructionCost = properties[a].houseConstructionCost * 100 / 70;
            }
            break;

        case 4:
            break;


        case 5:

            for(a = 0; a < 4; a++)
            {
                railways[a].currentRent = railways[a].currentRent * 100 / 125;
            }
            break;


        case 6:
            int b= 0;
            while(b < 2)
            {
                utilities[b].currentRent = utilities[b].currentRent * 100 / 120;
                b++;
            }
            break;


        case 7:
            int c= 0;
            while(c < 3)
            {
                insurance[c].insurancePremium = insurance[c].insurancePremium * 100 / 85;
                c++;
            }
            break;

        case 8:
            break;
    }
}

void payLuxuryPropertyTax()
{
    int k = 0;

    while(k < 4)
    {
        if(players[k].isBankrupt == 0)
        {
            int luxuryPropertyTax = 0;
            int a = 0;
            int payment = 0;

            while(a < 22)
            {
                if(properties[a].owner == players[k].playerID && properties[a].hotelCount > 0)
                {
                    luxuryPropertyTax += properties[a].currentPrice * 25 / 100;
                }
                a++;
            }

            players[k].luxuryPropertyTaxDue += luxuryPropertyTax;

            if(players[k].luxuryPropertyTaxDue > 0 && players[k].money > 0)
            {
                if(players[k].money >= players[k].luxuryPropertyTaxDue)
                {
                    payment = players[k].luxuryPropertyTaxDue;

                    players[k].money -= payment;

                    players[k].luxuryPropertyTaxDue = 0;
                }

                else
                {
                    payment = players[k].money;

                    players[k].money = 0;

                    players[k].luxuryPropertyTaxDue -= payment;
                }
            }

            if(luxuryPropertyTax > 0)
            {
                printf("%s Luxury Property Tax for this round : LKR %d\n", players[k].name, luxuryPropertyTax);
            }

            if(payment > 0)
            {
                printf("%s paid Luxury Property Tax : LKR %d\n", players[k].name, payment);
            }

            if(players[k].luxuryPropertyTaxDue > 0)
            {
                printf("%s outstanding Luxury Property Tax : LKR %d\n", players[k].name, players[k].luxuryPropertyTaxDue);
            }

            printf("\n");
        }

        k++;
    }
}

void payLuxuryPropertyTaxDebt(int playerID)
{
    int payment;

    if(players[playerID].luxuryPropertyTaxDue <= 0)
    {
        return;
    }

    if(players[playerID].money <= 0)
    {
        return;
    }

    if(players[playerID].money >= players[playerID].luxuryPropertyTaxDue)
    {
        payment = players[playerID].luxuryPropertyTaxDue;

        players[playerID].money -= payment;

        players[playerID].luxuryPropertyTaxDue = 0;
    }
    else
    {
        payment = players[playerID].money;

        players[playerID].money = 0;

        players[playerID].luxuryPropertyTaxDue -= payment;
    }

    printf("%s paid LKR %d of outstanding Luxury Property Tax.\n", players[playerID].name,  payment);

    if(players[playerID].luxuryPropertyTaxDue > 0)
    {
        printf("Remaining Luxury Property Tax Debt : LKR %d\n\n", players[playerID].luxuryPropertyTaxDue);
    }
    else
    {
        printf("Luxury Property Tax Debt fully paid.\n\n");
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

void updateAntiSpeculationAct()
{
    int i;
    int owner;

    if(gameInfo.currentGovernmentRegulation != 8)
    {
        return;
    }

    for(i = 0; i < 22; i++)
    {
        if(properties[i].undevelopedPurchaseRound >= 0)
        {
            if(gameInfo.gameRound - properties[i].undevelopedPurchaseRound >= 5)
            {

                if(properties[i].houseCount == 0 && properties[i].hotelCount == 0)
                {
                    owner = properties[i].owner;

                    printf("\nAnti-Speculation Act:\n");

                    printf("%s failed to develop %s within 5 rounds.\n", players[owner].name, properties[i].name);
                }

                properties[i].undevelopedPurchaseRound = -1;
            }
        }
    }
}


//natiomnal event cards

struct eventCardData eventCardData[4] = {0};

int eventCards[20];
int eventCardFront = 0;

void shuffleEventCards()
{
    int i;
    int j;
    int temp;

    for(i = 0; i < 20; i++)
    {
        eventCards[i] = i + 1;
    }

    for(i = 19; i > 0; i--)
    {
        j = rand() % (i + 1);

        temp = eventCards[i];
        eventCards[i] = eventCards[j];
        eventCards[j] = temp;
    }

    eventCardFront = 0;
}

void initializeEventCards()
{
    int i;
    int j;

    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 20; j++)
        {
            eventCardData[i].isActive[j] = 0;
            eventCardData[i].startRound[j] = 0;
        }
    }

    shuffleEventCards();
}

void pickEventCard(int playerID)
{
    int card;

    card = eventCards[eventCardFront];

    resetRepeatedEventCard(playerID, card);

    printf("\n=========================================\n");
    printf("National Event Card\n");
    printf("=========================================\n");

    printf("%s drew Event Card %d.\n\n", players[playerID].name, card);

    switch(card)
    {
        case 1:

            printf("Event Card : Tourism Hype\n");
            printf("Hotels earn double rent for 5 rounds.\n");

            eventCardData[playerID].isActive[0] = 1;
            eventCardData[playerID].startRound[0] = players[playerID].playerRound;
            break;


        case 2:

            printf("Event Card : Fuel Shortage\n");
            printf("Railway rent doubles for 5 rounds.\n");
            eventCardData[playerID].isActive[1] = 1;
            eventCardData[playerID].startRound[1] = players[playerID].playerRound;
            break;


        case 3:

            printf("Event Card : Heavy Floods\n");
            printf("A flood disaster has occurred.\n");

            nationalDisaster(flood);

            break;


        case 4:

            printf("Event Card : Political Rally\n");
            politicalRally();
            break;


       case 5:

            printf("Event Card : Stock Market Rise\n");
            printf("All property values increase by 10%%.\n");

            stockMarketRise();

            gameInfo.eventCard5Active = 1;
            gameInfo.eventCard5StartRound = players[playerID].playerRound;

            break;


        case 6:

            printf("Event Card : Economic Downturn\n");
            printf("Property values decrease by 15%%.\n");

            economicDownturn();

            gameInfo.eventCard6Active = 1;
            gameInfo.eventCard6StartRound = players[playerID].playerRound;

            break;


        case 7:

            printf("Event Card : Housing Subsidy\n");
            printf("House construction cost reduced by 30%%.\n");
            eventCardData[playerID].isActive[6] = 1;
            eventCardData[playerID].startRound[6] = players[playerID].playerRound;
            break;


        case 8:

            printf("Event Card : Interest Rate Cut\n");
            printf("Loan interest reduced by 2%%.\n");

            eventCardData[playerID].isActive[7] = 1;
            eventCardData[playerID].startRound[7] = players[playerID].playerRound;

            break;


        case 9:

            printf("Event Card : Interest Rate Increase\n");
            printf("Loan interest increased by 2%%.\n");

            eventCardData[playerID].isActive[8] = 1;
            eventCardData[playerID].startRound[8] = players[playerID].playerRound;
            break;


        case 10:

            printf("Event Card : Tax Amnesty\n");
            taxAmnesty();
            break;


        case 11:

            printf("Event Card : Power Failure\n");
            printf("Utility income halved for 3 rounds.\n");

            eventCardData[playerID].isActive[10] = 1;
            eventCardData[playerID].startRound[10] = players[playerID].playerRound;
            break;


        case 12:

            printf("Event Card : Foreign Funding\n");
            printf("Commercial property values increase by 15%%.\n");

            foreignFunding();

            gameInfo.eventCard12Active = 1;
            gameInfo.eventCard12StartRound = players[playerID].playerRound;

            break;


        case 13:

            printf("Event Card : Port Expansion\n");
            printf("Railway station values increase by 20%%.\n");

            portExpansion();

            gameInfo.eventCard13Active = 1;
            gameInfo.eventCard13StartRound = players[playerID].playerRound;

            break;


        case 14:

            printf("Event Card : Festival Season\n");
            printf("Hotels receive 50%% additional rent.\n");
            eventCardData[playerID].isActive[13] = 1;
            eventCardData[playerID].startRound[13] = players[playerID].playerRound;
            break;


        case 15:

            printf("Event Card : Labour Strike\n");
            printf("Construction suspended for 2 rounds.\n");
            eventCardData[playerID].isActive[14] = 1;
            eventCardData[playerID].startRound[14] = players[playerID].playerRound;
            break;


        case 16:

            printf("Event Card : Insurance Discount\n");
            printf("Insurance premiums reduced by 20%%.\n");
            eventCardData[playerID].isActive[15] = 1;
            eventCardData[playerID].startRound[15] = players[playerID].playerRound;
            break;


        case 17:

            printf("Event Card : Property Revaluation\n");

            propertyRevaluation();

            gameInfo.eventCard17StartRound = players[playerID].playerRound;

            break;


        case 18:

            printf("Event Card : Currency Depreciation\n");
            printf("Construction costs increase by 10%%.\n");
            eventCardData[playerID].isActive[17] = 1;
            eventCardData[playerID].startRound[17] = players[playerID].playerRound;
            break;


        case 19:

            printf("Event Card : Government Grant\n");
            governmentGrant();
            break;


        case 20:

            printf("Event Card : National Disaster\n");
            nationalDisaster(-1);
            break;
    }

    eventCardFront++;

    if(eventCardFront >= 20)
    {
        eventCardFront = 0;
        shuffleEventCards();
    }

    printf("=========================================\n\n");
}

void handleEventCard()
{
    int i;

    for(i = 0; i < 22; i++)
    {
        if(properties[i].isClosed == 1)
        {
            properties[i].closedRounds--;

            if(properties[i].closedRounds <= 0)
            {
                properties[i].isClosed = 0;
                properties[i].closedRounds = 0;

                printf("%s is no longer closed.\n\n",properties[i].name);
            }
        }
    }
}

void resetRepeatedEventCard(int playerID, int card)
{
    int i;
    int a;

    i = card - 1;

    if(card == 5)
    {
        if(gameInfo.eventCard5Active == 1)
        {
            for(a = 0; a < 22; a++)
            {
                properties[a].currentPrice =
                    properties[a].currentPrice * 100 / 110;
            }

            gameInfo.eventCard5Active = 0;
            gameInfo.eventCard5StartRound = 0;

            printf("Previous effect of Event Card 5 is being reset.\n");
        }

        return;
    }

    if(card == 6)
    {
        if(gameInfo.eventCard6Active == 1)
        {
            for(a = 0; a < 22; a++)
            {
                properties[a].currentPrice = properties[a].currentPrice * 100 / 85;
            }

            gameInfo.eventCard6Active = 0;
            gameInfo.eventCard6StartRound = 0;

            printf("Previous effect of Event Card 6 is being reset.\n");
        }

        return;
    }

    if(card == 12)
    {
        if(gameInfo.eventCard12Active == 1)
        {
            for(a = 0; a < 22; a++)
            {
                properties[a].currentPrice = properties[a].currentPrice * 100 / 115;
            }

            gameInfo.eventCard12Active = 0;
            gameInfo.eventCard12StartRound = 0;

            printf("Previous effect of Event Card 12 is being reset.\n");
        }

        return;
    }

    if(card == 13)
    {
        if(gameInfo.eventCard13Active == 1)
        {
            for(a = 0; a < 4; a++)
            {
                railways[a].currentPrice = railways[a].currentPrice * 100 / 120;
            }

            gameInfo.eventCard13Active = 0;
            gameInfo.eventCard13StartRound = 0;

            printf("Previous effect of Event Card 13 is being reset.\n");
        }

        return;
    }

    if(card == 17)
    {
        if(gameInfo.eventCard17Active == 1)
        {
            for(a = 0; a < 22; a++)
            {
                if(properties[a].colorGroup ==
                   gameInfo.eventCard17Group)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 100 / 115;
                }
            }

            gameInfo.eventCard17Active = 0;
            gameInfo.eventCard17StartRound = 0;

            printf("Previous effect of Event Card 17 is being reset.\n");
        }

        return;
    }

    if(eventCardData[playerID].isActive[i] == 0)
    {
        return;
    }

    printf("Previous effect of Event Card %d is being reset.\n", card);

    eventCardData[playerID].isActive[i] = 0;
    eventCardData[playerID].startRound[i] = 0;
}

int getEventCardDuration(int card)
{
    switch(card)
    {
        case 0:
            return 5;

        case 1:
            return 5;

        case 6:
            return 15;

        case 7:
            return 15;

        case 8:
            return 15;

        case 10:
            return 3;

        case 13:
            return 15;

        case 14:
            return 2;

        case 15:
            return 2;

        case 17:
            return 15;
    }

    return 0;
}

void updatePlayerEventCards(int playerID)
{
    int i;

    if(gameInfo.eventCard5Active == 1 &&
       players[playerID].playerRound >=
       gameInfo.eventCard5StartRound + 15)
    {
        resetRepeatedEventCard(playerID, 5);
    }

    if(gameInfo.eventCard6Active == 1 &&
       players[playerID].playerRound >=
       gameInfo.eventCard6StartRound + 15)
    {
        resetRepeatedEventCard(playerID, 6);
    }

    if(gameInfo.eventCard12Active == 1 &&
       players[playerID].playerRound >=
       gameInfo.eventCard12StartRound + 15)
    {
        resetRepeatedEventCard(playerID, 12);
    }

    if(gameInfo.eventCard13Active == 1 &&
       players[playerID].playerRound >=
       gameInfo.eventCard13StartRound + 15)
    {
        resetRepeatedEventCard(playerID, 13);
    }

    if(gameInfo.eventCard17Active == 1 &&
       players[playerID].playerRound >=
       gameInfo.eventCard17StartRound + 15)
    {
        resetRepeatedEventCard(playerID, 17);
    }


    for(i = 0; i < 20; i++)
    {
        if(eventCardData[playerID].isActive[i] == 1)
        {
            if(players[playerID].playerRound >=
               eventCardData[playerID].startRound[i] +
               getEventCardDuration(i))
            {
                eventCardData[playerID].isActive[i] = 0;
                eventCardData[playerID].startRound[i] = 0;

                printf("%s's Event Card %d effect has expired.\n\n",
                       players[playerID].name,
                       i + 1);
            }
        }
    }
}

void stockMarketRise()
{
    int i;

    for(i = 0; i < 22; i++)
    {
        properties[i].currentPrice = properties[i].currentPrice * 110 / 100;
    }
}

void economicDownturn()
{
    int i;

    for(i = 0; i < 22; i++)
    {
        properties[i].currentPrice = properties[i].currentPrice * 85 / 100;
    }
}

void portExpansion()
{
    int i;

    for(i = 0; i < 4; i++)
    {
        railways[i].currentPrice = railways[i].currentPrice * 120 / 100;
    }
}

void foreignFunding()
{
    int i;

    for(i = 0; i < 22; i++)
    {
        properties[i].currentPrice = properties[i].currentPrice * 115 / 100;
    }
}

void politicalRally()
{
    int propertyIndex;

    propertyIndex = rand() % 22;

    properties[propertyIndex].isClosed = 1;
    properties[propertyIndex].closedRounds = 2;

    printf("%s has been closed for 2 rounds.\n\n", properties[propertyIndex].name);
}

void taxAmnesty()
{
    int i;

    for(i = 0; i < 4; i++)
    {
        if(players[i].isBankrupt == 0)
        {
            players[i].money += 2000;
        }
    }

    printf("Each player receives LKR 2000.\n\n");
}

void governmentGrant()
{
    int playerID;

    playerID = rand() % 4;

    while(players[playerID].isBankrupt == 1)
    {
        playerID = rand() % 4;
    }

    players[playerID].money += 5000;
    players[playerID].taxableMoney += 5000;

    printf("%s receives LKR 5000.\n\n",  players[playerID].name);
}

void nationalDisaster(int disasterType)
{
    int developed[22];
    int count = 0;
    int i;
    int propertyIndex;
    int disaster;
    int compensation;
    int repairCost;
    int owner;

    for(i = 0; i < 22; i++)
    {
        if(properties[i].houseCount > 0 ||
           properties[i].hotelCount > 0)
        {
            if(properties[i].isDisasterDamaged == 0)
            {
                developed[count] = i;
                count++;
            }
        }
    }

    if(count == 0)
    {
        printf("\nNational Disaster\n");
        printf("No developed property was available for the disaster.\n\n");
        return;
    }

    propertyIndex =  developed[rand() % count];

    if(disasterType == -1)
    {
        disaster = rand() % 5;
    }
    else
    {
        disaster = disasterType;
    }

    properties[propertyIndex].isDisasterDamaged = 1;

    properties[propertyIndex].disasterType = disaster;

    repairCost = properties[propertyIndex].repairCost;

    properties[propertyIndex].disasterRepairCost = repairCost;

    owner =  properties[propertyIndex].owner;

    printf("\n");
    printf("=========================================\n");
    printf("              NATIONAL DISASTER\n");
    printf("=========================================\n");

    printf("Affected Property : %s\n", properties[propertyIndex].name);

    printf("Owner : %s\n", players[owner].name);

    printf("Repair Cost : LKR %d\n", repairCost);

    switch(disaster)
    {
        case fire:
            printf("Disaster : FIRE\n");
            break;

        case flood:
            printf("Disaster : FLOOD\n");
            break;

        case riot:
            printf("Disaster : RIOT\n");
            break;

        case buildingCollapse:
            printf("Disaster : BUILDING COLLAPSE\n");
            break;

        case electricalFailure:
            printf("Disaster : ELECTRICAL FAILURE\n");
            break;
    }

    compensation = calculateInsuranceCompensation(  propertyIndex, disaster );

    if(compensation > 0)
    {
        players[owner].money += compensation;

        printf("Insurance Claim : APPROVED\n");
        printf("Compensation Paid : LKR %d\n", compensation);

        if(properties[propertyIndex].insurancePolicyType == BusinessInterruptionInsurance)
        {
            printf("Business interruption compensation included.\n");
            printf("Lost rental income compensation : 5 rounds\n");
        }
    }
    else
    {
        printf("Insurance Claim : NOT COVERED\n");

        if(players[owner].money >= repairCost)
        {
            players[owner].money -= repairCost;

            properties[propertyIndex].isDisasterDamaged = 0;
            properties[propertyIndex].disasterRepairCost = 0;
            properties[propertyIndex].disasterType = -1;

            printf("Repair Cost Paid : LKR %d\n", repairCost);
            printf("Property repaired immediately.\n");
        }
        else
        {
            printf("%s does not have enough money to repair the property.\n", players[owner].name);

            printf("Property remains damaged.\n");
            printf("No rent can be collected until repaired.\n");
        }
    }

    printf("=========================================\n\n");
}

void propertyRevaluation()
{
    int group;
    int i;

    group = rand() % 8;
    gameInfo.eventCard17Group = group;
    gameInfo.eventCard17Active = 1;
    printf("Property Group %d has been revalued by 15%%.\n", group);

    for(i = 0; i < 22; i++)
    {
        if(properties[i].colorGroup == group)
        {
            properties[i].currentPrice = properties[i].currentPrice * 115 / 100;
        }
    }
}


//regional development cards

void regionalDevelopmentCards()
{   
    int regionalDevelopmentCards = rand() % 12 + 1;
    int a = 0;

    switch(regionalDevelopmentCards)
    {
        case 1:
            printf("Regional Development Card : Southern Tourism Boom\n");
            printf("Rental income of Galle Fort, Unawatuna and Hikkaduwa increased by 40%%\n");
            gameInfo.currentRegionalDevelopmentCard = 1;
            a = 0;
            while(a < 22)
            {
                if(properties[a].squareNumber == 26)
                {
                    properties[a].currentRent = properties[a].currentRent * 140 / 100;
                }

                if(properties[a].squareNumber == 27)
                {
                    properties[a].currentRent = properties[a].currentRent * 140 / 100;
                }

                if(properties[a].squareNumber == 29)
                {
                    properties[a].currentRent = properties[a].currentRent * 140 / 100;
                }

                a++;
            }
            break;


        case 2:
            printf("Regional Development Card : Port City Expansion\n");
            printf("Pettah, Maradana and Colombo Fort Station values increased by 25%%\n");
            gameInfo.currentRegionalDevelopmentCard = 2;
            a = 0;
            while(a < 22)
            {
                if(properties[a].squareNumber == 1)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 125 / 100;
                }

                if(properties[a].squareNumber == 3)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 125 / 100;
                }

                a++;
            }

            railways[0].currentPrice = railways[0].currentPrice * 125 / 100;

            break;


        case 3:
            printf("Regional Development Card : IT Industry Growth\n");
            printf("Maharagama, Nugegoda and Kottawa values increased by 20%%\n");
            gameInfo.currentRegionalDevelopmentCard = 3;
            a = 0;
            while(a < 22)
            {
                if(properties[a].squareNumber == 11)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 120 / 100;
                }

                if(properties[a].squareNumber == 13)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 120 / 100;
                }

                if(properties[a].squareNumber == 14)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 120 / 100;
                }

                a++;
            }
            break;


        case 4:
            printf("Regional Development Card : Northern Development Programme\n");
            printf("Jaffna Town, Nallur and Trincomalee values increased by 30%%\n");
            gameInfo.currentRegionalDevelopmentCard = 4;
            a = 0;
            while(a < 22)
            {
                if(properties[a].squareNumber == 31)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 130 / 100;
                }

                if(properties[a].squareNumber == 32)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 130 / 100;
                }

                if(properties[a].squareNumber == 34)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 130 / 100;
                }

                a++;
            }
            break;


        case 5:
            printf("Regional Development Card : Tea Export Boom\n");
            printf("Nuwara Eliya value increased by 35%%\n");
            gameInfo.currentRegionalDevelopmentCard = 5;
            a = 0;
            while(a < 22)
            {
                if(properties[a].squareNumber == 37)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 135 / 100;
                }

                a++;
            }
            break;


        case 6:
            printf("Regional Development Card : Airport Expansion\n");
            printf("Negombo, Katunayake and Ja-Ela rents increased by 30%%\n");
            gameInfo.currentRegionalDevelopmentCard = 6;
            a = 0;
            while(a < 22)
            {
                if(properties[a].squareNumber == 16)
                {
                    properties[a].currentRent = properties[a].currentRent * 130 / 100;
                }

                if(properties[a].squareNumber == 18)
                {
                    properties[a].currentRent = properties[a].currentRent * 130 / 100;
                }

                if(properties[a].squareNumber == 19)
                {
                    properties[a].currentRent = properties[a].currentRent * 130 / 100;
                }

                a++;
            }
            break;


        case 7:
            printf("Regional Development Card : University City Growth\n");
            printf("Peradeniya and Kandy City values increased by 20%%\n");
            gameInfo.currentRegionalDevelopmentCard = 7;
            a = 0;
            while(a < 22)
            {
                if(properties[a].squareNumber == 21)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 120 / 100;
                }

                if(properties[a].squareNumber == 23)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 120 / 100;
                }

                a++;
            }
            break;


        case 8:
            printf("Regional Development Card : Beach Pollution\n");
            printf("Southern coastal property rents decreased by 30%%\n");
            gameInfo.currentRegionalDevelopmentCard = 8;
            a = 0;
            while(a < 22)
            {
                if(properties[a].squareNumber == 26)
                {
                    properties[a].currentRent = properties[a].currentRent * 70 / 100;
                }

                if(properties[a].squareNumber == 27)
                {
                    properties[a].currentRent = properties[a].currentRent * 70 / 100;
                }

                if(properties[a].squareNumber == 29)
                {
                    properties[a].currentRent = properties[a].currentRent * 70 / 100;
                }

                a++;
            }
            break;


        case 9:
            printf("Regional Development Card : Flood Damage\n");
            printf("Low-lying coastal property values decreased by 20%%\n");
            gameInfo.currentRegionalDevelopmentCard = 9;

            a = 0;
            while(a < 22)
            {
                if(properties[a].squareNumber == 26)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 80 / 100;
                }

                if(properties[a].squareNumber == 27)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 80 / 100;
                }

                if(properties[a].squareNumber == 29)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 80 / 100;
                }

                a++;
            }
            break;


        case 10:
            printf("Regional Development Card : Transport Strike\n");
            printf("Railway revenue decreased by 40%%\n");
            gameInfo.currentRegionalDevelopmentCard = 10;
            a = 0;
            while(a < 4)
            {
                railways[a].currentRent = railways[a].currentRent * 60 / 100;
                a++;
            }
            break;


        case 11:
            printf("Regional Development Card : Electricity Tariff Increase\n");
            printf("Utility rent increased by 25%%\n");
            gameInfo.currentRegionalDevelopmentCard = 11;
  
            utilities[0].currentRent = utilities[0].currentRent * 125 / 100;

            break;


        case 12:
            printf("Regional Development Card : Water Shortage\n");
            printf("Water utility revenue increased by 20%%\n");
            printf("Surrounding property values decreased by 10%%\n");
            gameInfo.currentRegionalDevelopmentCard = 12;

            utilities[1].currentRent = utilities[1].currentRent * 120 / 100;

            a = 0;
            while(a < 22)
            {
                if(properties[a].squareNumber == 27)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 90 / 100;
                }

                if(properties[a].squareNumber == 29)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 90 / 100;
                }

                a++;
            }

            break;
    }
}

void resetCurrentRegionalDevelopmentCards(){
    if(gameInfo.currentRegionalDevelopmentCard != -1)
    {
        if(gameInfo.currentRegionalDevelopmentCard == 1)
        {
            int a = 0;
            while(a < 22)
            {
                if(properties[a].squareNumber == 26)
                {
                    properties[a].currentRent = properties[a].currentRent * 100 / 140;
                }

                if(properties[a].squareNumber == 27)
                {
                    properties[a].currentRent = properties[a].currentRent * 100 / 140;
                }

                if(properties[a].squareNumber == 29)
                {
                    properties[a].currentRent = properties[a].currentRent * 100 / 140;
                }

                a++;
            }
        }
        if(gameInfo.currentRegionalDevelopmentCard == 2)
        {
            int a = 0;
            while(a < 22)
            {
                if(properties[a].squareNumber == 1)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 100 / 125;
                }

                if(properties[a].squareNumber == 3)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 100 / 125;
                }

                a++;
            }

            railways[0].currentPrice = railways[0].currentPrice * 100 / 125;
        }
        if(gameInfo.currentRegionalDevelopmentCard == 3)
        {
            int a = 0;
            while(a < 22)
            {
                if(properties[a].squareNumber == 11)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 100 / 120;
                }

                if(properties[a].squareNumber == 13)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 100 / 120;
                }

                if(properties[a].squareNumber == 14)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 100 / 120;
                }

                a++;
            }
        }
        if(gameInfo.currentRegionalDevelopmentCard == 4)
        {
            int a = 0;
            while(a < 22)
            {
                if(properties[a].squareNumber == 31)
                {
                    properties[a].currentPrice =  properties[a].currentPrice * 100 / 130;
                }

                if(properties[a].squareNumber == 32)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 100 / 130;
                }

                if(properties[a].squareNumber == 34)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 100 / 130;
                }

                a++;
            }
        }
        if(gameInfo.currentRegionalDevelopmentCard == 5)
        {
            int a = 0;
            while(a < 22)
            {
                if(properties[a].squareNumber == 37)
                {
                    properties[a].currentPrice =  properties[a].currentPrice * 100 / 135;
                }

                a++;
            }
        }
        if(gameInfo.currentRegionalDevelopmentCard == 6)
        {
            int a = 0;
            while(a < 22)
            {
                if(properties[a].squareNumber == 16)
                {
                    properties[a].currentRent = properties[a].currentRent * 100 / 130;
                }

                if(properties[a].squareNumber == 18)
                {
                    properties[a].currentRent = properties[a].currentRent * 100 / 130;
                }

                if(properties[a].squareNumber == 19)
                {
                    properties[a].currentRent = properties[a].currentRent * 100 / 130;
                }

                a++;
            }
        }
        if(gameInfo.currentRegionalDevelopmentCard == 7)
        {
            int a = 0;
            while(a < 22)
            {
                if(properties[a].squareNumber == 21)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 100 / 120;
                }

                if(properties[a].squareNumber == 23)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 100 / 120;
                }

                a++;
            }
        }
        if(gameInfo.currentRegionalDevelopmentCard == 8)
        {
            int a = 0;
            while(a < 22)
            {
                if(properties[a].squareNumber == 26)
                {
                    properties[a].currentRent = properties[a].currentRent * 100 / 70;
                }

                if(properties[a].squareNumber == 27)
                {
                    properties[a].currentRent =  properties[a].currentRent * 100 / 70;
                }

                if(properties[a].squareNumber == 29)
                {
                    properties[a].currentRent = properties[a].currentRent * 100 / 70;
                }

                a++;
            }
        }
        if(gameInfo.currentRegionalDevelopmentCard == 9)
        {
            int a = 0;
            while(a < 22)
            {
                if(properties[a].squareNumber == 26)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 100 / 80;
                }

                if(properties[a].squareNumber == 27)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 100 / 80;
                }

                if(properties[a].squareNumber == 29)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 100 / 80;
                }

                a++;
            }
        }
        if(gameInfo.currentRegionalDevelopmentCard == 10)
        {
            int a = 0;
            while(a < 4)
            {
                railways[a].currentRent = railways[a].currentRent * 100 / 60;

                a++;
            }
        }
        if(gameInfo.currentRegionalDevelopmentCard == 11)
        {
            utilities[0].currentRent = utilities[0].currentRent * 100 / 125;
        }
        if(gameInfo.currentRegionalDevelopmentCard == 12)
        {
            utilities[1].currentRent = utilities[1].currentRent * 100 / 120;

            int a = 0;
            while(a < 22)
            {
                if(properties[a].squareNumber == 27)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 100 / 90;
                }

                if(properties[a].squareNumber == 29)
                {
                    properties[a].currentPrice = properties[a].currentPrice * 100 / 90;
                }

                a++;
            }
        }
    }
    gameInfo.currentRegionalDevelopmentCard = -1;
}


#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "types.h"

void economicEvents(int roundNumber)
{
    if(roundNumber % 50 == 0)
    {
        printf("A new Economic Event has started \n\n");
        int events[8] = {1,2,3,4,5,6,7,8};
        int a=0;
        srand(time(NULL));
        int randomEvent = rand() % 8;
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
                int a=0;
                while(a<3)
                {
                    insurance[a].insurancePremium = insurance[a].insurancePremium * 1.3;
                    a++;
                }
                printf("Southern costal property price decreased by 10%\n");
                    if(properties[a].colorGroup==5)
                    {
                        properties[a].currentPrice = properties[a].currentPrice * 0.9;
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
                    playerLoans[a].interestRate = playerLoans[a].interestRate * 1.15;
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
                    playerLoans[a].interestRate = playerLoans[a].interestRate * 0.9;
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

}

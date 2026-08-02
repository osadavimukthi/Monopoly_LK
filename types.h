#ifndef TYPES_H
#define TYPES_H

enum squareType
{
    Start,
    Property,
    Railway,
    Utility,
    Tax,
    Event,
    CommunityFund,
    Insurance,
    Bank,
    Jail,
    FreeParking,
    GoToJail
};

enum propertyColorGroup
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


enum players
{
    aggresiveInvestor,
    conservativeBanker,
    riskTaker,
    opportunisticTrader,
};



struct property
{
    char name[50];
    int squareNumber;
    enum propertyColorGroup colorGroup;
    int basePurchasePrice;
    int baseRent;
    int currentRent;
    int currentPrice;
    int mortgagedValue;
    int houseConstructionCost;
    int hotelConstructionCost;
    int owner;
    int isMortgaged;
    int isInsured;
    int houseCount;
    int hotelCount;
};

struct square
{
    char name[50];
    enum squareType type;
    int propertyColor;
};

struct player
{
    enum players playerID; 
    char name[50];
    int priority;
    int position;
    int money;
    int ownedProperties[50];
    int ownedPropertiesCount;
    int isInJail;
    int jailTurnCount;
    int isBankrupt;
    int railwayCount;
    int utiliy;
    int hasLoan;
};

struct railway {
    char name[50];
    int sqareNumber;
    int purchasePrice;     // ASSUMPTION: not specified in assignment — confirm with lecturer
    int mortgageValue;
    int owner;              // -1 = unowned, else player index
    int isMortgaged;
};

struct utility {
    char name[50];
    int sqareNumber;
    int purchasePrice;     // ASSUMPTION: not specified in assignment — confirm with lecturer
    int mortgageValue;
    int owner;              // -1 = unowned, else player index
    int isMortgaged;
};

struct insuranceCompany{
    char name[50];
    int sqareNumber;    // ASSUMPTION: not specified in assignment — confirm with lectur
};

enum insurancePolicyType{
    basicPropertyInsurance,
    comprehensiveInsurance,
    BusinessInterruptionInsurance,
};

enum disasterType {
    fire,
    flood,
    riot,
    buildingCollapse,
    electricalFailure,
    vandalism,
    earthquake
};

struct Insurance {
    enum insurancePolicyType insurance_policy;
    int coverage_disaster_types[7];
    int installment_percentage;
    int coverage_percentage;

};

#endif 

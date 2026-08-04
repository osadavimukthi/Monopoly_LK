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
    int hasOwner;
    int owner;
    int isMortgaged;
    int isInsured;
    int houseCount;
    int hotelCount;

};
extern struct property properties[22];

struct square
{
    char name[50];
    int squareNumber;
    enum squareType type;
    int propertyColor;
};
extern struct square board[40];

struct player
{
    enum players playerID; 
    char name[50];
    int priority;
    int oldPosition;
    int currentPosition;
    int money;
    int ownedProperties[22];
    int ownedPropertiesCount;
    int isInJail;
    int jailTurnCount;
    int isBankrupt;
    int ownedRailwayCount;
    int utiliy;
    int hasLoan;
    int lastRoll1;
    int lastRoll2;
    int playerRound;
    int playerTurn;
};
extern struct player players[4];

struct railway {
    char name[50];
    int squareNumber;
    int basePurchasePrice;
    int currentPrice;
    int baseRent;
    int currentRent;        // ASSUMPTION: not specified in assignment — confirm with lecturer
    int mortgageValue;
    int owner;              // -1 = unowned, else player index
    int hasOwner;
    int isMortgaged;

};
extern struct railway railways[4];

struct utility {
    char name[50];
    int squareNumber;
    int purchasePrice;     // ASSUMPTION: not specified in assignment — confirm with lecturer
    int mortgageValue;
    int owner;              // -1 = unowned, else player index
    int isMortgaged;

};
extern struct utility utilities[2];

struct insuranceCompany{
    char name[50];
    int squareNumber;    // ASSUMPTION: not specified in assignment — confirm with lectur
};
extern struct insuranceCompany insuranceCompanies[2];

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

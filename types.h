#ifndef TYPES_H
#define TYPES_H

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

enum squareType
{
    Start,
    Property,
    Railway,
    Utility,
    Tax,
    Event,
    Insurance,
    Bank,
    Jail,
    FreeParking,
    GoToJail
};

struct property
{
    char name[20];
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

struct player
{
    char name[20];
    enum players playerID; 
    int money;
    int position;
    int ownedProperties[40];
    int ownedPropertiesCount;
    int isBankrupt;
    int hasLoan;
    int isInJail;
    int jailTurnCount;
};

struct square
{
    char name[20];
    enum squareType type;
};

#endif 

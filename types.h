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
    int isLoanLocked;
    int isInsured;
    int houseCount;
    int hotelCount;
    int repairCost;
    int propertyAge;
    int depreciationPercent;
    int auctionStartingPrice;


};
extern struct property properties[22];

struct propertyColor{
    enum propertyColorGroup color;
    int propertyCount;    
    int marketBoomRound;
    int marketDeclineRound;
};

extern struct propertyColor propertyColors[8];
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
    int taxableMoney;
    int ownedProperties[22];
    int ownedPropertiesCount;
    int isInJail;
    int jailTurnCount;
    int isBankrupt;
    int ownedRailways[4];
    int ownedRailwayCount;
    int ownedUtilities[2];
    int ownedUtilitiesCount;
    int hasLoan;
    int lastRoll1;
    int lastRoll2;
    int playerRound;
    int playerTurn;
    int obtainableMaximumLoan;
    int currentLoan;
    int loanRound;
    int loanInterestRate;
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
    int isLoanLocked;
    int netWorth;

};
extern struct railway railways[4];

struct utility {
    char name[50];
    int squareNumber;
    int basePurchasePrice;     // ASSUMPTION: not specified in assignment — confirm with lecturer
    int currentPrice;          // ASSUMPTION: not specified in assignment — confirm with lecturer
    int mortgageValue;
    int owner;              // -1 = unowned, else player index
    int hasOwner;
    int isMortgaged;
    int isLoanLocked;
    int baseRent;
    int currentRent;

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
    int insurancePremium;
    int coverage_disaster_types[7];
    int installment_percentage;
    int coverage_percentage;
};
extern struct Insurance insurance[3];

struct Bidding{
    int currentBid;
    int highestBidder;
    int activePlayers[4];
};

extern struct Bidding bidding;

struct gameData {
    int gameRound;
    int bankruptedPlayerCount;
    int previousEconomicEvent;
    int currentEconomicEvent;
    int previousGovernmentRegulation;
    int currentGovernmentRegulation;
    int previousMarketBoomColor;
    int currentMarketBoomColor;
    int previousMarketDeclineColor;
    int currentMarketDeclineColor;


};

extern struct gameData gameInfo;

struct rate {
    int interestRate;
    int incomeTaxRate;
};
extern struct rate rates;

struct monopoly{
    int monopolyColor;
    int monopolyCount;
    int hasOwner;
    int owner;
};

extern struct monopoly monopolies[8];
/* Function prototypes for finance-related operations */

struct eventCardRound{
    int tourismHype;
};
#endif 

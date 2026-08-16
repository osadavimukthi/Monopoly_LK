#ifndef FINANCE_H
#define FINANCE_H

#include "types.h"

// Loan Functions
int calculateMaximumLoan(int playerId);
void lockLoanCollateral(int playerID);
void unlockLoanCollateral(int playerID);
void obtainLoan(int playerID, int playerPosition);
void updateLoanInterest(int playerID);
void propertyForeclose(int playerID);
void repayFullLoan(int playerID);
void repayPartofLoan(int playerID, int amount);
void increaseLoan(int playerID, int amount);

// Insurance Functions
int purchaseInsurance(int playerID, int propertyIndex, int policyType);
void updateInsurancePolicies(void);
int calculateInsuranceCompensation(int propertyIndex, int disaster);
int isDisasterCovered(int propertyIndex, int disaster);
int claimInsurance(int propertyIndex);

// Bankruptcy and Tax Functions
void playerBankrupt(int playerID, int *bankruptedPlayerCount);
void payTax(int playerSquare, int k);
void communityDevelopmentFund(int playerID);

// Property Renovation and Depreciation Functions
void renovateProperty(int squareNumber, int playerID);
int shouldRenovateProperty(int playerID, int depreciation);
void updatePropertyDepreciation(void);

// Building Condition and Maintenance Functions
int calculateAverageBuildingCondition(int propertyIndex);
int getConditionRentPercentage(int averageCondition);
void updateBuildingCondition(void);
void maintainBuildings(int playerID);
int shouldMaintainBuilding(int playerID, int condition);
int shouldRenovateDamagedBuilding(int playerID);
void updateMaintenanceDamage(void);
void renovateDamagedBuilding(int propertyIndex, int playerID);

// Disaster Functions
void happenDisaster(void);
void repairDisasterDamagedProperties(int playerID);
void processDisasterRepairs(void);

// Inflation Functions
void propertyInflation(int randomPercentage);
void insuaranceInflation(int randomPercentage);
void loanInflation(int randomPercentage);
void inflation(int gameRound);

// Auction Functions
void auctionProperty(int propertyIndex);
void auctionRailway(int railwayIndex);
void auctionUtility(int utilityIndex);

// Buy and Rent Functions
void propertyBuyRent(int playerSquare, int k);
void railwayBuyRent(int playerSquare, int k);
void utilityBuyRent(int playerSquare, int k);

// Building Construction Functions
int constructHouse(int k, int propertyIndex);
int constructHotel(int k, int propertyIndex);

// Financial Calculation Functions
int calculateNetWorth(int playerID);

#endif
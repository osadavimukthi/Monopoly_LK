#ifndef FINANCE_H
#define FINANCE_H

int calculateMaximumLoan(int playerId);

void obtainLoan(int playerID, int playerPosition);
void updateLoanInterest(int playerID);

void repayPartofLoan(int playerID, int amount);
void repayFullLoan(int playerID);

void increaseLoan(int playerID, int amount);
void extendLoanPeriod(int playerID);

void lockLoanCollateral(int playerID);
void unlockLoanCollateral(int playerID);

void renovateProperty(int squareNumber, int playerID);

void updatePropertyDepreciation(void);
void updateBuildingCondition(void);

int calculateAverageBuildingCondition(int propertyIndex);
int getConditionRentPercentage(int averageCondition);

void maintainBuildings(int playerID);
void updateMaintenanceDamage(void);

void renovateDamagedBuilding(int propertyIndex, int playerID);

int shouldMaintainBuilding(int playerID, int condition);
int shouldRenovateDamagedBuilding(int playerID);
int shouldRenovateProperty(int playerID, int depreciation);

void communityDevelopmentFund(int playerID);
void propertyForeclose(int playerID);

void playerBankrupt(int playerID, int *bankruptedPlayerCount);

int calculateNetWorth(int playerID);

int purchaseInsurance(int playerID, int propertyIndex, int policyType);
void updateInsurancePolicies(void);

int isDisasterCovered(int propertyIndex, int disaster);
int calculateInsuranceCompensation(int propertyIndex, int disaster);

#endif
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
void communityDevelopmentFund(int playerID);
void propertyForeclose(int playerID);

void playerBankrupt(int playerID,int *bankruptedPlayerCount);

#endif
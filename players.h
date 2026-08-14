#ifndef PLAYERS_H
#define PLAYERS_H

int aggressivePurchaseDecision(int k, int propertyIndex);
int conservativePurchaseDecision(int k, int propertyIndex);
int riskTakerPurchaseDecision(int k, int propertyIndex);
int opportunisticPurchaseDecision(int k, int propertyIndex);

int playerPurchaseDecision(int k, int propertyIndex);

int buildHouses(int k, int group, int reservePercent);

int aggressiveConstruction(int k);
int conservativeConstruction(int k);
int riskTakerConstruction(int k);
int opportunisticConstruction(int k);

int playerConstruction(int k);

void gotoJail(int playerSquare, int k);
void outOfJail(int playerSquare, int k);

int railwayPurchaseDecision(int k, int railwayIndex);
int utilityPurchaseDecision(int k, int utilityIndex);

void manageLoan(int k);
void manageInsurance(int playerID);

int aggressiveAuctionDecision(int playerID, int propertyIndex, int currentBid);
int conservativeAuctionDecision(int playerID, int propertyIndex, int currentBid);
int riskTakerAuctionDecision(int playerID, int propertyIndex, int currentBid);
int opportunisticAuctionDecision(int playerID, int propertyIndex, int currentBid);

void auctionProperty(int propertyIndex);
#endif
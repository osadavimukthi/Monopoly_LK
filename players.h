#ifndef PLAYERS_H
#define PLAYERS_H

#include "types.h"

// Player Initialization
void initializePlayers(void);

// Player Turn and Movement
void playerTurn(int playerID);
void movePlayer(int playerID, int diceValue);

// Property Decisions
int playerPurchaseDecision(int k, int propertyIndex);
int aggressivePurchaseDecision(int k, int propertyIndex);
int conservativePurchaseDecision(int k, int propertyIndex);
int riskTakerPurchaseDecision(int k, int propertyIndex);
int opportunisticPurchaseDecision(int k, int propertyIndex);

// Railway and Utility Decisions
int railwayPurchaseDecision(int k, int railwayIndex);
int utilityPurchaseDecision(int k, int utilityIndex);

// Auction Decisions
int aggressiveAuctionDecision(int playerID, int propertyIndex, int currentBid);
int conservativeAuctionDecision(int playerID, int propertyIndex, int currentBid);
int riskTakerAuctionDecision(int playerID, int propertyIndex, int currentBid);
int opportunisticAuctionDecision(int playerID, int propertyIndex, int currentBid);

int aggressiveRailwayAuctionDecision(int playerID, int railwayIndex, int currentBid);
int conservativeRailwayAuctionDecision(int playerID, int railwayIndex, int currentBid);
int riskTakerRailwayAuctionDecision(int playerID, int railwayIndex, int currentBid);
int opportunisticRailwayAuctionDecision(int playerID, int railwayIndex, int currentBid);

int aggressiveUtilityAuctionDecision(int playerID, int utilityIndex, int currentBid);
int conservativeUtilityAuctionDecision(int playerID, int utilityIndex, int currentBid);
int riskTakerUtilityAuctionDecision(int playerID, int utilityIndex, int currentBid);
int opportunisticUtilityAuctionDecision(int playerID, int utilityIndex, int currentBid);

// Construction Decisions
int buildHouses(int k, int group, int reservePercent);
int aggressiveConstruction(int k);
int conservativeConstruction(int k);
int riskTakerConstruction(int k);
int opportunisticConstruction(int k);
int playerConstruction(int k);

// Loan and Insurance Decisions
void manageLoan(int playerID);
void manageInsurance(int playerID);

// Player Financial Decisions
void manageFinances(int playerID);
void manageProperties(int playerID);

// Bankruptcy
void checkBankruptcy(int playerID);

// Player Information
void displayPlayerStatus(int playerID);

#endif
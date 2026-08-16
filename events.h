#ifndef EVENTS_H
#define EVENTS_H

#include "types.h"

void setNewEconomicEventt(void);
void resetCurrentEconomicEvent(void);
void economicEvents(int roundNumber);

void dynamicPropertyMarkrt(int roundNumber);
void marketBoom(int PropertyColor);
void marketDecline(int PropertyColor);
void reversePreviousMarketBoom(int PropertyColor);
void reversePreviousMarketDecline(int PropertyColor);
void updateMarketRounds(int gameRound);

void governmentRegulations(int roundNumber);
void setNewGovernmentRegulations(void);
void resetCurrentGovernmentRegulations(void);

void payLuxuryPropertyTax(void);
void payLuxuryPropertyTaxDebt(int playerID);
int countUndevelopedProperties(int playerID);
void updateAntiSpeculationAct(void);

void shuffleEventCards(void);
void initializeEventCards(void);
void pickEventCard(int playerID);
void handleEventCard(void);
void resetRepeatedEventCard(int playerID, int card);
int getEventCardDuration(int card);
void updatePlayerEventCards(int playerID);

void stockMarketRise(void);
void economicDownturn(void);
void portExpansion(void);
void foreignFunding(void);
void politicalRally(void);
void taxAmnesty(void);
void governmentGrant(void);
void nationalDisaster(int disasterType);
void propertyRevaluation(void);

void regionalDevelopmentCards(void);
void resetCurrentRegionalDevelopmentCards(void);

#endif
#ifndef EVENTS_H
#define EVENTS_H

void setNewEconomicEventt();
void resetCurrentEconomicEvent();
void economicEvents(int roundNumber);

void setNewGovernmentRegulations();
void resetCurrentGovernmentRegulations();
void governmentRegulations(int roundNumber);

void marketBoom(int PropertyColor);
void marketDecline(int PropertyColor);

void reversePreviousMarketBoom(int PropertyColor);
void reversePreviousMarketDecline(int PropertyColor);

void dynamicPropertyMarkrt(int roundNumber);
void updateMarketRounds(int gameRound);

void shuffleEventCards(void);
void initializeEventCards(void);
void pickEventCard(int playerID);
void handleEventCard(void);
void updatePlayerEventCards(int playerID);

void politicalRally();
void stockMarketRise();
void economicDownturn();
void taxAmnesty();
void foreignFunding();
void portExpansion();
void propertyRevaluation();
void governmentGrant();
void nationalDisaster();

int getEventCardDuration(int card);

void regionalDevelopmentCards();
void resetCurrentRegionalDevelopmentCards();

void processDisasterRepairs();
void payLuxuryPropertyTax();
#endif
#ifndef EVENTS_H
#define EVENTS_H

void setNewEconomicEventt(void);
void resetCurrentEconomicEvent(void);
void economicEvents(int roundNumber);

void setNewGovernmentRegulations(void);
void resetCurrentGovernmentRegulations(void);
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

void politicalRally(void);
void stockMarketRise(void);
void economicDownturn(void);
void taxAmnesty(void);
void foreignFunding(void);
void portExpansion(void);
void propertyRevaluation(void);
void governmentGrant(void);
void nationalDisaster(void);

int getEventCardDuration(int card);

void regionalDevelopmentCards(void);
void resetCurrentRegionalDevelopmentCards(void);

void processDisasterRepairs(void);

#endif
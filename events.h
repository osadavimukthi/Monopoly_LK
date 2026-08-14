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

#endif
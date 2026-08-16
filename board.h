#ifndef BOARD_H
#define BOARD_H

// Jail Functions
void gotoJail(int playerSquare, int k);
void outOfJail(int playerSquare, int k);

// Monopoly Functions
int checkMonopoly(int playerID, int colorGroup);

#endif
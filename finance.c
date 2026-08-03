#include <stdio.h>
#include "types.h"

//void board();

struct Insurance insurance[3]={
    {basicPropertyInsurance, {fire, flood, -1, -1, -1, -1, -1}, 5, 80},

    {
        comprehensiveInsurance, {fire, flood, riot, -1, -1, vandalism, earthquake}, 10, 100
    },
    {
        BusinessInterruptionInsurance, {fire, flood, riot, buildingCollapse, electricalFailure, vandalism, earthquake}, 15, 70
    },
};

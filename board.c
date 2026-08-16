#include <stdio.h>
#include "types.h"

struct square board[40] = {
    {"GO",                                      0,  Start,          -1},
    {"Pettah",                                  1,  Property,       Brown},
    {"Community Development Fund",              2,  CommunityFund,  -1},
    {"Maradana",                                3,  Property,       Brown},
    {"Income Tax",                              4,  Tax,            -1},
    {"Colombo Fort Railway Station",            5,  Railway,        -1},
    {"Bambalapitiya",                            6,  Property,       LightBlue},
    {"National Event Card",                     7,  Event,          -1},
    {"Wellawatte",                              8,  Property,       LightBlue},
    {"Mount Lavinia",                           9,  Property,       LightBlue},
    {"Jail / Just Visiting",                   10,  Jail,           -1},
    {"Nugegoda",                               11,  Property,       Pink},
    {"Ceylon Electricity Board",               12,  Utility,        -1},
    {"Maharagama",                              13,  Property,       Pink},
    {"Kottawa",                                 14,  Property,       Pink},
    {"Kandy Railway Station",                   15,  Railway,        -1},
    {"Negombo",                                16,  Property,       Orange},
    {"Sri Lanka Insurance",                    17,  Insurance,      -1},
    {"Katunayake",                              18,  Property,       Orange},
    {"Ja-Ela",                                  19,  Property,       Orange},
    {"Free Parking",                            20,  FreeParking,    -1},
    {"Kandy City",                              21,  Property,       Red},
    {"National Event Card",                    22,  Event,          -1},
    {"Peradeniya",                              23,  Property,       Red},
    {"Katugastota",                             24,  Property,       Red},
    {"Galle Railway Station",                   25,  Railway,        -1},
    {"Galle Fort",                              26,  Property,       Yellow},
    {"Unawatuna",                               27,  Property,       Yellow},
    {"National Water Supply and Drainage Board",28,  Utility,        -1},
    {"Hikkaduwa",                               29,  Property,       Yellow},
    {"Go To Jail",                              30,  GoToJail,       -1},
    {"Jaffna Town",                             31,  Property,       Green},
    {"Nallur",                                  32,  Property,       Green},
    {"Ceylinco Insurance",                      33,  Insurance,      -1},
    {"Trincomalee",                             34,  Property,       Green},
    {"Jaffna Railway Station",                  35,  Railway,        -1},
    {"National Event Card",                    36,  Event,          -1},
    {"Nuwara Eliya",                            37,  Property,       DarkBlue},
    {"Bank of Ceylon",                          38,  Bank,           -1},
    {"Galle Face",                              39,  Property,       DarkBlue}
};

struct property properties[22] =
{
    {
        .name = "Pettah",
        .squareNumber = 1,
        .colorGroup = Brown,
        .basePurchasePrice = 1500,
        .baseRent = 100,
        .currentRent = 100,
        .currentPrice = 1500,
        .mortgagedValue = 750,
        .houseConstructionCost = 500,
        .hotelConstructionCost = 2000,
        .hasOwner = 0,
        .owner = -1,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .isInsured = 0,
        .houseCount = 0,
        .hotelCount = 0,
        .repairCost = 0,
        .propertyAge = 0,
        .depreciationPercent = 0,
        .auctionStartingPrice = 750,
        .isClosed = 0,
        .closedRounds = 0,
        .isUnderTourismHype = 0,
        .buildingCondition = {100, 100, 100, 100},
        .maintenanceIgnoredRounds = 0,
        .isStructurallyDamaged = 0,
        .isDisasterDamaged = 0,
        .disasterType = -1,
        .disasterRepairCost = 0,
        .insurancePolicyType = -1,
        .insuranceExpiryRound = 0,
        .undevelopedPurchaseRound = 0
    },

    {
        .name = "Maradana",
        .squareNumber = 3,
        .colorGroup = Brown,
        .basePurchasePrice = 1800,
        .baseRent = 120,
        .currentRent = 120,
        .currentPrice = 1800,
        .mortgagedValue = 750,
        .houseConstructionCost = 500,
        .hotelConstructionCost = 2000,
        .hasOwner = 0,
        .owner = -1,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .isInsured = 0,
        .houseCount = 0,
        .hotelCount = 0,
        .repairCost = 0,
        .propertyAge = 0,
        .depreciationPercent = 0,
        .auctionStartingPrice = 900,
        .isClosed = 0,
        .closedRounds = 0,
        .isUnderTourismHype = 0,
        .buildingCondition = {100, 100, 100, 100},
        .maintenanceIgnoredRounds = 0,
        .isStructurallyDamaged = 0,
        .isDisasterDamaged = 0,
        .disasterType = -1,
        .disasterRepairCost = 0,
        .insurancePolicyType = -1,
        .insuranceExpiryRound = 0,
        .undevelopedPurchaseRound = 0
    },

    {
        .name = "Bambalapitiya",
        .squareNumber = 6,
        .colorGroup = LightBlue,
        .basePurchasePrice = 2500,
        .baseRent = 180,
        .currentRent = 180,
        .currentPrice = 2500,
        .mortgagedValue = 1250,
        .houseConstructionCost = 750,
        .hotelConstructionCost = 3000,
        .hasOwner = 0,
        .owner = -1,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .isInsured = 0,
        .houseCount = 0,
        .hotelCount = 0,
        .repairCost = 0,
        .propertyAge = 0,
        .depreciationPercent = 0,
        .auctionStartingPrice = 1250,
        .isClosed = 0,
        .closedRounds = 0,
        .isUnderTourismHype = 0,
        .buildingCondition = {100, 100, 100, 100},
        .maintenanceIgnoredRounds = 0,
        .isStructurallyDamaged = 0,
        .isDisasterDamaged = 0,
        .disasterType = -1,
        .disasterRepairCost = 0,
        .insurancePolicyType = -1,
        .insuranceExpiryRound = 0,
        .undevelopedPurchaseRound = 0
    },

    {
        .name = "Wellawatte",
        .squareNumber = 8,
        .colorGroup = LightBlue,
        .basePurchasePrice = 2700,
        .baseRent = 200,
        .currentRent = 200,
        .currentPrice = 2700,
        .mortgagedValue = 1250,
        .houseConstructionCost = 750,
        .hotelConstructionCost = 3000,
        .hasOwner = 0,
        .owner = -1,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .isInsured = 0,
        .houseCount = 0,
        .hotelCount = 0,
        .repairCost = 0,
        .propertyAge = 0,
        .depreciationPercent = 0,
        .auctionStartingPrice = 1350,
        .isClosed = 0,
        .closedRounds = 0,
        .isUnderTourismHype = 0,
        .buildingCondition = {100, 100, 100, 100},
        .maintenanceIgnoredRounds = 0,
        .isStructurallyDamaged = 0,
        .isDisasterDamaged = 0,
        .disasterType = -1,
        .disasterRepairCost = 0,
        .insurancePolicyType = -1,
        .insuranceExpiryRound = 0,
        .undevelopedPurchaseRound = 0
    },

    {
        .name = "Mount Lavinia",
        .squareNumber = 9,
        .colorGroup = LightBlue,
        .basePurchasePrice = 3000,
        .baseRent = 220,
        .currentRent = 220,
        .currentPrice = 3000,
        .mortgagedValue = 1250,
        .houseConstructionCost = 750,
        .hotelConstructionCost = 3000,
        .hasOwner = 0,
        .owner = -1,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .isInsured = 0,
        .houseCount = 0,
        .hotelCount = 0,
        .repairCost = 0,
        .propertyAge = 0,
        .depreciationPercent = 0,
        .auctionStartingPrice = 1500,
        .isClosed = 0,
        .closedRounds = 0,
        .isUnderTourismHype = 0,
        .buildingCondition = {100, 100, 100, 100},
        .maintenanceIgnoredRounds = 0,
        .isStructurallyDamaged = 0,
        .isDisasterDamaged = 0,
        .disasterType = -1,
        .disasterRepairCost = 0,
        .insurancePolicyType = -1,
        .insuranceExpiryRound = 0,
        .undevelopedPurchaseRound = 0
    },

    {
        .name = "Nugegoda",
        .squareNumber = 11,
        .colorGroup = Pink,
        .basePurchasePrice = 3500,
        .baseRent = 260,
        .currentRent = 260,
        .currentPrice = 3500,
        .mortgagedValue = 1750,
        .houseConstructionCost = 1000,
        .hotelConstructionCost = 4000,
        .hasOwner = 0,
        .owner = -1,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .isInsured = 0,
        .houseCount = 0,
        .hotelCount = 0,
        .repairCost = 0,
        .propertyAge = 0,
        .depreciationPercent = 0,
        .auctionStartingPrice = 1750,
        .isClosed = 0,
        .closedRounds = 0,
        .isUnderTourismHype = 0,
        .buildingCondition = {100, 100, 100, 100},
        .maintenanceIgnoredRounds = 0,
        .isStructurallyDamaged = 0,
        .isDisasterDamaged = 0,
        .disasterType = -1,
        .disasterRepairCost = 0,
        .insurancePolicyType = -1,
        .insuranceExpiryRound = 0,
        .undevelopedPurchaseRound = 0
    },

    {
        .name = "Maharagama",
        .squareNumber = 13,
        .colorGroup = Pink,
        .basePurchasePrice = 3800,
        .baseRent = 280,
        .currentRent = 280,
        .currentPrice = 3800,
        .mortgagedValue = 1750,
        .houseConstructionCost = 1000,
        .hotelConstructionCost = 4000,
        .hasOwner = 0,
        .owner = -1,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .isInsured = 0,
        .houseCount = 0,
        .hotelCount = 0,
        .repairCost = 0,
        .propertyAge = 0,
        .depreciationPercent = 0,
        .auctionStartingPrice = 1900,
        .isClosed = 0,
        .closedRounds = 0,
        .isUnderTourismHype = 0,
        .buildingCondition = {100, 100, 100, 100},
        .maintenanceIgnoredRounds = 0,
        .isStructurallyDamaged = 0,
        .isDisasterDamaged = 0,
        .disasterType = -1,
        .disasterRepairCost = 0,
        .insurancePolicyType = -1,
        .insuranceExpiryRound = 0,
        .undevelopedPurchaseRound = 0
    },

    {
        .name = "Kottawa",
        .squareNumber = 14,
        .colorGroup = Pink,
        .basePurchasePrice = 4000,
        .baseRent = 300,
        .currentRent = 300,
        .currentPrice = 4000,
        .mortgagedValue = 1750,
        .houseConstructionCost = 1000,
        .hotelConstructionCost = 4000,
        .hasOwner = 0,
        .owner = -1,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .isInsured = 0,
        .houseCount = 0,
        .hotelCount = 0,
        .repairCost = 0,
        .propertyAge = 0,
        .depreciationPercent = 0,
        .auctionStartingPrice = 2000,
        .isClosed = 0,
        .closedRounds = 0,
        .isUnderTourismHype = 0,
        .buildingCondition = {100, 100, 100, 100},
        .maintenanceIgnoredRounds = 0,
        .isStructurallyDamaged = 0,
        .isDisasterDamaged = 0,
        .disasterType = -1,
        .disasterRepairCost = 0,
        .insurancePolicyType = -1,
        .insuranceExpiryRound = 0,
        .undevelopedPurchaseRound = 0
    },

    {
        .name = "Negombo",
        .squareNumber = 16,
        .colorGroup = Orange,
        .basePurchasePrice = 4500,
        .baseRent = 350,
        .currentRent = 350,
        .currentPrice = 4500,
        .mortgagedValue = 2250,
        .houseConstructionCost = 1250,
        .hotelConstructionCost = 5000,
        .hasOwner = 0,
        .owner = -1,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .isInsured = 0,
        .houseCount = 0,
        .hotelCount = 0,
        .repairCost = 0,
        .propertyAge = 0,
        .depreciationPercent = 0,
        .auctionStartingPrice = 2250,
        .isClosed = 0,
        .closedRounds = 0,
        .isUnderTourismHype = 0,
        .buildingCondition = {100, 100, 100, 100},
        .maintenanceIgnoredRounds = 0,
        .isStructurallyDamaged = 0,
        .isDisasterDamaged = 0,
        .disasterType = -1,
        .disasterRepairCost = 0,
        .insurancePolicyType = -1,
        .insuranceExpiryRound = 0,
        .undevelopedPurchaseRound = 0
    },

    {
        .name = "Katunayake",
        .squareNumber = 18,
        .colorGroup = Orange,
        .basePurchasePrice = 4700,
        .baseRent = 370,
        .currentRent = 370,
        .currentPrice = 4700,
        .mortgagedValue = 2250,
        .houseConstructionCost = 1250,
        .hotelConstructionCost = 5000,
        .hasOwner = 0,
        .owner = -1,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .isInsured = 0,
        .houseCount = 0,
        .hotelCount = 0,
        .repairCost = 0,
        .propertyAge = 0,
        .depreciationPercent = 0,
        .auctionStartingPrice = 2350,
        .isClosed = 0,
        .closedRounds = 0,
        .isUnderTourismHype = 0,
        .buildingCondition = {100, 100, 100, 100},
        .maintenanceIgnoredRounds = 0,
        .isStructurallyDamaged = 0,
        .isDisasterDamaged = 0,
        .disasterType = -1,
        .disasterRepairCost = 0,
        .insurancePolicyType = -1,
        .insuranceExpiryRound = 0,
        .undevelopedPurchaseRound = 0
    },

    {
        .name = "Ja-Ela",
        .squareNumber = 19,
        .colorGroup = Orange,
        .basePurchasePrice = 5000,
        .baseRent = 400,
        .currentRent = 400,
        .currentPrice = 5000,
        .mortgagedValue = 2250,
        .houseConstructionCost = 1250,
        .hotelConstructionCost = 5000,
        .hasOwner = 0,
        .owner = -1,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .isInsured = 0,
        .houseCount = 0,
        .hotelCount = 0,
        .repairCost = 0,
        .propertyAge = 0,
        .depreciationPercent = 0,
        .auctionStartingPrice = 2500,
        .isClosed = 0,
        .closedRounds = 0,
        .isUnderTourismHype = 0,
        .buildingCondition = {100, 100, 100, 100},
        .maintenanceIgnoredRounds = 0,
        .isStructurallyDamaged = 0,
        .isDisasterDamaged = 0,
        .disasterType = -1,
        .disasterRepairCost = 0,
        .insurancePolicyType = -1,
        .insuranceExpiryRound = 0,
        .undevelopedPurchaseRound = 0
    },

    {
        .name = "Kandy City",
        .squareNumber = 21,
        .colorGroup = Red,
        .basePurchasePrice = 5500,
        .baseRent = 450,
        .currentRent = 450,
        .currentPrice = 5500,
        .mortgagedValue = 2750,
        .houseConstructionCost = 1500,
        .hotelConstructionCost = 6000,
        .hasOwner = 0,
        .owner = -1,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .isInsured = 0,
        .houseCount = 0,
        .hotelCount = 0,
        .repairCost = 0,
        .propertyAge = 0,
        .depreciationPercent = 0,
        .auctionStartingPrice = 2750,
        .isClosed = 0,
        .closedRounds = 0,
        .isUnderTourismHype = 0,
        .buildingCondition = {100, 100, 100, 100},
        .maintenanceIgnoredRounds = 0,
        .isStructurallyDamaged = 0,
        .isDisasterDamaged = 0,
        .disasterType = -1,
        .disasterRepairCost = 0,
        .insurancePolicyType = -1,
        .insuranceExpiryRound = 0,
        .undevelopedPurchaseRound = 0
    },

    {
        .name = "Peradeniya",
        .squareNumber = 23,
        .colorGroup = Red,
        .basePurchasePrice = 5800,
        .baseRent = 480,
        .currentRent = 480,
        .currentPrice = 5800,
        .mortgagedValue = 2750,
        .houseConstructionCost = 1500,
        .hotelConstructionCost = 6000,
        .hasOwner = 0,
        .owner = -1,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .isInsured = 0,
        .houseCount = 0,
        .hotelCount = 0,
        .repairCost = 0,
        .propertyAge = 0,
        .depreciationPercent = 0,
        .auctionStartingPrice = 2900,
        .isClosed = 0,
        .closedRounds = 0,
        .isUnderTourismHype = 0,
        .buildingCondition = {100, 100, 100, 100},
        .maintenanceIgnoredRounds = 0,
        .isStructurallyDamaged = 0,
        .isDisasterDamaged = 0,
        .disasterType = -1,
        .disasterRepairCost = 0,
        .insurancePolicyType = -1,
        .insuranceExpiryRound = 0,
        .undevelopedPurchaseRound = 0
    },

    {
        .name = "Katugastota",
        .squareNumber = 24,
        .colorGroup = Red,
        .basePurchasePrice = 6000,
        .baseRent = 500,
        .currentRent = 500,
        .currentPrice = 6000,
        .mortgagedValue = 2750,
        .houseConstructionCost = 1500,
        .hotelConstructionCost = 6000,
        .hasOwner = 0,
        .owner = -1,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .isInsured = 0,
        .houseCount = 0,
        .hotelCount = 0,
        .repairCost = 0,
        .propertyAge = 0,
        .depreciationPercent = 0,
        .auctionStartingPrice = 3000,
        .isClosed = 0,
        .closedRounds = 0,
        .isUnderTourismHype = 0,
        .buildingCondition = {100, 100, 100, 100},
        .maintenanceIgnoredRounds = 0,
        .isStructurallyDamaged = 0,
        .isDisasterDamaged = 0,
        .disasterType = -1,
        .disasterRepairCost = 0,
        .insurancePolicyType = -1,
        .insuranceExpiryRound = 0,
        .undevelopedPurchaseRound = 0
    },

    {
        .name = "Galle Fort",
        .squareNumber = 26,
        .colorGroup = Yellow,
        .basePurchasePrice = 6500,
        .baseRent = 600,
        .currentRent = 600,
        .currentPrice = 6500,
        .mortgagedValue = 3250,
        .houseConstructionCost = 2000,
        .hotelConstructionCost = 8000,
        .hasOwner = 0,
        .owner = -1,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .isInsured = 0,
        .houseCount = 0,
        .hotelCount = 0,
        .repairCost = 0,
        .propertyAge = 0,
        .depreciationPercent = 0,
        .auctionStartingPrice = 3250,
        .isClosed = 0,
        .closedRounds = 0,
        .isUnderTourismHype = 0,
        .buildingCondition = {100, 100, 100, 100},
        .maintenanceIgnoredRounds = 0,
        .isStructurallyDamaged = 0,
        .isDisasterDamaged = 0,
        .disasterType = -1,
        .disasterRepairCost = 0,
        .insurancePolicyType = -1,
        .insuranceExpiryRound = 0,
        .undevelopedPurchaseRound = 0
    },

    {
        .name = "Unawatuna",
        .squareNumber = 27,
        .colorGroup = Yellow,
        .basePurchasePrice = 6800,
        .baseRent = 620,
        .currentRent = 620,
        .currentPrice = 6800,
        .mortgagedValue = 3250,
        .houseConstructionCost = 2000,
        .hotelConstructionCost = 8000,
        .hasOwner = 0,
        .owner = -1,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .isInsured = 0,
        .houseCount = 0,
        .hotelCount = 0,
        .repairCost = 0,
        .propertyAge = 0,
        .depreciationPercent = 0,
        .auctionStartingPrice = 3400,
        .isClosed = 0,
        .closedRounds = 0,
        .isUnderTourismHype = 0,
        .buildingCondition = {100, 100, 100, 100},
        .maintenanceIgnoredRounds = 0,
        .isStructurallyDamaged = 0,
        .isDisasterDamaged = 0,
        .disasterType = -1,
        .disasterRepairCost = 0,
        .insurancePolicyType = -1,
        .insuranceExpiryRound = 0,
        .undevelopedPurchaseRound = 0
    },

    {
        .name = "Hikkaduwa",
        .squareNumber = 29,
        .colorGroup = Yellow,
        .basePurchasePrice = 7000,
        .baseRent = 650,
        .currentRent = 650,
        .currentPrice = 7000,
        .mortgagedValue = 3250,
        .houseConstructionCost = 2000,
        .hotelConstructionCost = 8000,
        .hasOwner = 0,
        .owner = -1,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .isInsured = 0,
        .houseCount = 0,
        .hotelCount = 0,
        .repairCost = 0,
        .propertyAge = 0,
        .depreciationPercent = 0,
        .auctionStartingPrice = 3500,
        .isClosed = 0,
        .closedRounds = 0,
        .isUnderTourismHype = 0,
        .buildingCondition = {100, 100, 100, 100},
        .maintenanceIgnoredRounds = 0,
        .isStructurallyDamaged = 0,
        .isDisasterDamaged = 0,
        .disasterType = -1,
        .disasterRepairCost = 0,
        .insurancePolicyType = -1,
        .insuranceExpiryRound = 0,
        .undevelopedPurchaseRound = 0
    },

    {
        .name = "Jaffna Town",
        .squareNumber = 31,
        .colorGroup = Green,
        .basePurchasePrice = 8000,
        .baseRent = 750,
        .currentRent = 750,
        .currentPrice = 8000,
        .mortgagedValue = 4000,
        .houseConstructionCost = 2500,
        .hotelConstructionCost = 10000,
        .hasOwner = 0,
        .owner = -1,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .isInsured = 0,
        .houseCount = 0,
        .hotelCount = 0,
        .repairCost = 0,
        .propertyAge = 0,
        .depreciationPercent = 0,
        .auctionStartingPrice = 4000,
        .isClosed = 0,
        .closedRounds = 0,
        .isUnderTourismHype = 0,
        .buildingCondition = {100, 100, 100, 100},
        .maintenanceIgnoredRounds = 0,
        .isStructurallyDamaged = 0,
        .isDisasterDamaged = 0,
        .disasterType = -1,
        .disasterRepairCost = 0,
        .insurancePolicyType = -1,
        .insuranceExpiryRound = 0,
        .undevelopedPurchaseRound = 0
    },

    {
        .name = "Nallur",
        .squareNumber = 32,
        .colorGroup = Green,
        .basePurchasePrice = 8300,
        .baseRent = 780,
        .currentRent = 780,
        .currentPrice = 8300,
        .mortgagedValue = 4000,
        .houseConstructionCost = 2500,
        .hotelConstructionCost = 10000,
        .hasOwner = 0,
        .owner = -1,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .isInsured = 0,
        .houseCount = 0,
        .hotelCount = 0,
        .repairCost = 0,
        .propertyAge = 0,
        .depreciationPercent = 0,
        .auctionStartingPrice = 4150,
        .isClosed = 0,
        .closedRounds = 0,
        .isUnderTourismHype = 0,
        .buildingCondition = {100, 100, 100, 100},
        .maintenanceIgnoredRounds = 0,
        .isStructurallyDamaged = 0,
        .isDisasterDamaged = 0,
        .disasterType = -1,
        .disasterRepairCost = 0,
        .insurancePolicyType = -1,
        .insuranceExpiryRound = 0,
        .undevelopedPurchaseRound = 0
    },

    {
        .name = "Trincomalee",
        .squareNumber = 34,
        .colorGroup = Green,
        .basePurchasePrice = 8500,
        .baseRent = 800,
        .currentRent = 800,
        .currentPrice = 8500,
        .mortgagedValue = 4000,
        .houseConstructionCost = 2500,
        .hotelConstructionCost = 10000,
        .hasOwner = 0,
        .owner = -1,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .isInsured = 0,
        .houseCount = 0,
        .hotelCount = 0,
        .repairCost = 0,
        .propertyAge = 0,
        .depreciationPercent = 0,
        .auctionStartingPrice = 4250,
        .isClosed = 0,
        .closedRounds = 0,
        .isUnderTourismHype = 0,
        .buildingCondition = {100, 100, 100, 100},
        .maintenanceIgnoredRounds = 0,
        .isStructurallyDamaged = 0,
        .isDisasterDamaged = 0,
        .disasterType = -1,
        .disasterRepairCost = 0,
        .insurancePolicyType = -1,
        .insuranceExpiryRound = 0,
        .undevelopedPurchaseRound = 0
    },

    {
        .name = "Nuwara Eliya",
        .squareNumber = 37,
        .colorGroup = DarkBlue,
        .basePurchasePrice = 10000,
        .baseRent = 1000,
        .currentRent = 1000,
        .currentPrice = 10000,
        .mortgagedValue = 5000,
        .houseConstructionCost = 3000,
        .hotelConstructionCost = 12000,
        .hasOwner = 0,
        .owner = -1,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .isInsured = 0,
        .houseCount = 0,
        .hotelCount = 0,
        .repairCost = 0,
        .propertyAge = 0,
        .depreciationPercent = 0,
        .auctionStartingPrice = 5000,
        .isClosed = 0,
        .closedRounds = 0,
        .isUnderTourismHype = 0,
        .buildingCondition = {100, 100, 100, 100},
        .maintenanceIgnoredRounds = 0,
        .isStructurallyDamaged = 0,
        .isDisasterDamaged = 0,
        .disasterType = -1,
        .disasterRepairCost = 0,
        .insurancePolicyType = -1,
        .insuranceExpiryRound = 0,
        .undevelopedPurchaseRound = 0
    },

    {
        .name = "Galle Face",
        .squareNumber = 39,
        .colorGroup = DarkBlue,
        .basePurchasePrice = 12000,
        .baseRent = 1200,
        .currentRent = 1200,
        .currentPrice = 12000,
        .mortgagedValue = 5000,
        .houseConstructionCost = 3000,
        .hotelConstructionCost = 12000,
        .hasOwner = 0,
        .owner = -1,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .isInsured = 0,
        .houseCount = 0,
        .hotelCount = 0,
        .repairCost = 0,
        .propertyAge = 0,
        .depreciationPercent = 0,
        .auctionStartingPrice = 6000,
        .isClosed = 0,
        .closedRounds = 0,
        .isUnderTourismHype = 0,
        .buildingCondition = {100, 100, 100, 100},
        .maintenanceIgnoredRounds = 0,
        .isStructurallyDamaged = 0,
        .isDisasterDamaged = 0,
        .disasterType = -1,
        .disasterRepairCost = 0,
        .insurancePolicyType = -1,
        .insuranceExpiryRound = 0,
        .undevelopedPurchaseRound = 0
    }
};

struct monopoly monopolies[8] =
{
    {1, 2, 0, -1},   
    {2, 3, 0, -1},  
    {3, 3, 0, -1},  
    {4, 3, 0, -1},   
    {5, 3, 0, -1},   
    {6, 3, 0, -1},   
    {7, 3, 0, -1},   
    {8, 2, 0, -1}    
};

struct propertyColor propertyColors[8] =
{
    {Brown,     2, -1, -1},
    {LightBlue, 3, -1, -1},
    {Pink,      3, -1, -1},
    {Orange,    3, -1, -1},
    {Red,       3, -1, -1},
    {Yellow,    3, -1, -1},
    {Green,     3, -1, -1},
    {DarkBlue,  2, -1, -1}
};


struct railway railways[4] =
{
    {
        .name = "Colombo Fort Railway Station",
        .squareNumber = 5,
        .basePurchasePrice = 1500,
        .currentPrice = 1500,
        .baseRent = 250,
        .currentRent = 250,
        .mortgageValue = 750,
        .owner = -1,
        .hasOwner = 0,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .netWorth = 0,
        .auctionStartingPrice = 750
    },
    {
        .name = "Kandy Railway Station",
        .squareNumber = 15,
        .basePurchasePrice = 1500,
        .currentPrice = 1500,
        .baseRent = 250,
        .currentRent = 250,
        .mortgageValue = 750,
        .owner = -1,
        .hasOwner = 0,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .netWorth = 0,
        .auctionStartingPrice = 750
    },
    {
        .name = "Galle Railway Station",
        .squareNumber = 25,
        .basePurchasePrice = 1500,
        .currentPrice = 1500,
        .baseRent = 250,
        .currentRent = 250,
        .mortgageValue = 750,
        .owner = -1,
        .hasOwner = 0,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .netWorth = 0,
        .auctionStartingPrice = 750
    },
    {
        .name = "Jaffna Railway Station",
        .squareNumber = 35,
        .basePurchasePrice = 1500,
        .currentPrice = 1500,
        .baseRent = 250,
        .currentRent = 250,
        .mortgageValue = 750,
        .owner = -1,
        .hasOwner = 0,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .netWorth = 0,
        .auctionStartingPrice = 750
    }
};


struct utility utilities[2] =
{
    {
        .name = "Ceylon Electricity Board",
        .squareNumber = 12,
        .basePurchasePrice = 1500,
        .currentPrice = 1500,
        .mortgageValue = 750,
        .owner = -1,
        .hasOwner = 0,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .baseRent = 0,
        .currentRent = 0,
        .auctionStartingPrice = 750
    },
    {
        .name = "National Water Supply and Drainage Board",
        .squareNumber = 28,
        .basePurchasePrice = 1500,
        .currentPrice = 1500,
        .mortgageValue = 750,
        .owner = -1,
        .hasOwner = 0,
        .isMortgaged = 0,
        .isLoanLocked = 0,
        .baseRent = 0,
        .currentRent = 0,
        .auctionStartingPrice = 750
    }
};


struct insuranceCompany insuranceCompanies[2] =
{
    {
        .name = "Sri Lanka Insurance",
        .squareNumber = 17
    },
    {
        .name = "Ceylinco Insurance",
        .squareNumber = 33
    }
};


struct gameData gameInfo =
{
    .gameRound = 0,
    .bankruptedPlayerCount = 0,
    .previousEconomicEvent = -1,
    .currentEconomicEvent = -1,
    .previousGovernmentRegulation = -1,
    .currentGovernmentRegulation = -1,
    .previousMarketBoomColor = -1,
    .currentMarketBoomColor = -1,
    .previousMarketDeclineColor = -1,
    .currentMarketDeclineColor = -1,
    .currentRegionalDevelopmentCard = -1,
    .eventCard5Active = 0,
    .eventCard5StartRound = 0,
    .eventCard6Active = 0,
    .eventCard6StartRound = 0,
    .eventCard12Active = 0,
    .eventCard12StartRound = 0,
    .eventCard13Active = 0,
    .eventCard13StartRound = 0,
    .eventCard17Active = 0,
    .eventCard17StartRound = 0,
    .eventCard17Group = -1
};



//jail functions in board

void gotoJail(int playerSquare, int k)
{
    if (playerSquare == 30) {
        players[k].currentPosition = 10; 
        players[k].isInJail = 1; 
        players[k].jailTurnCount = 0; 
        printf("%s has been sent to Jail!\n", players[k].name);
    }
}

void outOfJail(int playerSquare, int k)
{
    if(players[k].lastRoll1 == players[k].lastRoll2)
    {
        printf("%s rolled doubles and is out of Jail!\n", players[k].name);
        players[k].isInJail = 0;
        players[k].jailTurnCount = 0;
    }
    else if(players[k].money >= 300) 
    //i took an assume that if a player in prison he want to release immediately he will pay 300 to get out of jail
    {
        printf("%s paid LKR 300 to get out of Jail.\n", players[k].name);
        players[k].money -= 300;
        players[k].isInJail = 0;
        players[k].jailTurnCount = 0;
    }
    else if(players[k].jailTurnCount < 2)
    {
        players[k].jailTurnCount++;
        printf("%s is still in Jail. Turn %d of 3.\n", players[k].name, players[k].jailTurnCount);
    }
    else if(players[k].jailTurnCount == 2)
    {
        players[k].jailTurnCount++;
        printf("%s has served 3 turns in Jail and is now released.\n", players[k].name);
        players[k].isInJail = 0;
        players[k].jailTurnCount = 0;
    }
}

//monnopoly check function

int checkMonopoly(int playerID, int colorGroup)
{
    int i;
    int monopolyIndex = -1;
    int ownedCount = 0;

    for(i = 0; i < 8; i++)
    {
        if(monopolies[i].monopolyColor == colorGroup)
        {
            monopolyIndex = i;
            break;
        }
    }

    if(monopolyIndex == -1)
    {
        return 0;
    }

    for(i = 0; i < 22; i++)
    {
        if(properties[i].colorGroup == colorGroup &&
           properties[i].owner == playerID)
        {
            ownedCount++;
        }
    }

    if(ownedCount == monopolies[monopolyIndex].monopolyCount)
    {
        
        if(monopolies[monopolyIndex].hasOwner == 0)
        {
            monopolies[monopolyIndex].hasOwner = 1;
            monopolies[monopolyIndex].owner = playerID;

            printf("\n============================================\n");
            printf("MONOPOLY OBTAINED!\n");
            printf("%s has obtained the monopoly of Group %d.\n", players[playerID].name, colorGroup);
            printf("============================================\n\n");
        }
        else
        {
            monopolies[monopolyIndex].hasOwner = 1;
            monopolies[monopolyIndex].owner = playerID;
        }

        return 1;
    }

    monopolies[monopolyIndex].hasOwner = 0;
    monopolies[monopolyIndex].owner = -1;

    return 0;
}
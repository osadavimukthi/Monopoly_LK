#include <stdio.h>
#include "types.h"



struct square board[40] = {
    {"GO",                                  0,  Start,          -1},
    {"Pettah",                              1,  Property,       -1},
    {"Community Development Fund",          2,  CommunityFund,  -1},
    {"Maradana",                            3,  Property,       -1},
    {"Income Tax",                          4,  Tax,            -1},
    {"Colombo Fort Railway Station",        5,  Railway,        -1},
    {"Bambalapitiya",                       6,  Property,       -1},
    {"National Event Card",                 7,  Event,          -1},
    {"Wellawatte",                          8,  Property,       -1},
    {"Mount Lavinia",                       9,  Property,       -1},
    {"Jail / Just Visiting",               10,  Jail,           -1},
    {"Nugegoda",                           11,  Property,       -1},
    {"Ceylon Electricity Board",           12,  Utility,        -1},
    {"Maharagama",                         13,  Property,       -1},
    {"Kottawa",                            14,  Property,       -1},
    {"Kandy Railway Station",              15,  Railway,        -1},
    {"Negombo",                            16,  Property,       -1},
    {"Sri Lanka Insurance",                17,  Insurance,      -1},
    {"Katunayake",                         18,  Property,       -1},
    {"Ja-Ela",                             19,  Property,       -1},
    {"Free Parking",                       20,  FreeParking,    -1},
    {"Kandy City",                         21,  Property,       -1},
    {"National Event Card",                22,  Event,          -1},
    {"Peradeniya",                         23,  Property,       -1},
    {"Katugastota",                        24,  Property,       -1},
    {"Galle Railway Station",              25,  Railway,        -1},
    {"Galle Fort",                         26,  Property,       -1},
    {"Unawatuna",                          27,  Property,       -1},
    {"National Water Supply and Drainage Board", 28, Utility,   -1},
    {"Hikkaduwa",                          29,  Property,       -1},
    {"Go To Jail",                         30,  GoToJail,       -1},
    {"Jaffna Town",                        31,  Property,       -1},
    {"Nallur",                             32,  Property,       -1},
    {"Ceylinco Insurance",                 33,  Insurance,      -1},
    {"Trincomalee",                        34,  Property,       -1},
    {"Jaffna Railway Station",             35,  Railway,        -1},
    {"National Event Card",                36,  Event,          -1},
    {"Nuwara Eliya",                       37,  Property,       -1},
    {"Bank of Ceylon",                     38,  Bank,           -1},
    {"Galle Face",                         39,  Property,       -1}
};

struct property properties[22] = {

    // Brown group — house 500, hotel 2000, mortgage 750
    {"Pettah",        1,  Brown,     1500, 100, 100, 1500, 750,  500,  2000, 0, -1, 0, 0, 0, 0, 0},
    {"Maradana",      3,  Brown,     1800, 120, 120, 1800, 750,  500,  2000, 0, -1, 0, 0, 0, 0, 0},

    // Light Blue group — house 750, hotel 3000, mortgage 1250
    {"Bambalapitiya", 6,  LightBlue, 2500, 180, 180, 2500, 1250, 750,  3000, 0, -1, 0, 0, 0, 0, 0},
    {"Wellawatte",    8,  LightBlue, 2700, 200, 200, 2700, 1250, 750,  3000, 0, -1, 0, 0, 0, 0, 0},
    {"Mount Lavinia", 9,  LightBlue, 3000, 220, 220, 3000, 1250, 750,  3000, 0, -1, 0, 0, 0, 0, 0},

    // Pink group — house 1000, hotel 4000, mortgage 1750
    {"Maharagama",    13, Pink,      3500, 260, 260, 3500, 1750, 1000, 4000, 0, -1, 0, 0, 0, 0, 0},
    {"Nugegoda",      11, Pink,      3500, 260, 260, 3500, 1750, 1000, 4000, 0, -1, 0, 0, 0, 0, 0},
    {"Kottawa",       14, Pink,      4000, 300, 300, 4000, 1750, 1000, 4000, 0, -1, 0, 0, 0, 0, 0},

    // Orange group — house 1250, hotel 5000, mortgage 2250
    {"Negombo",       16, Orange,    4500, 350, 350, 4500, 2250, 1250, 5000, 0, -1, 0, 0, 0, 0, 0},
    {"Katunayake",    18, Orange,    4700, 375, 375, 4700, 2250, 1250, 5000, 0, -1, 0, 0, 0, 0, 0},
    {"Ja-Ela",        19, Orange,    5000, 400, 400, 5000, 2250, 1250, 5000, 0, -1, 0, 0, 0, 0, 0},

    // Red group — house 1500, hotel 6000, mortgage 2750
    {"Kandy City",     21, Red,       5500, 450, 450, 5500, 2750, 1500, 6000, 0, -1, 0, 0, 0, 0, 0},
    {"Peradeniya",     23, Red,       5800, 480, 480, 5800, 2750, 1500, 6000, 0, -1, 0, 0, 0, 0, 0},
    {"Katugastota",    24, Red,       6000, 500, 500, 6000, 2750, 1500, 6000, 0, -1, 0, 0, 0, 0, 0},

    // Yellow group — house 2000, hotel 8000, mortgage 3250
    {"Galle Fort",     26, Yellow,    6500, 550, 550, 6500, 3250, 2000, 8000, 0, -1, 0, 0, 0, 0, 0},
    {"Unawatuna",      27, Yellow,    6750, 600, 600, 6750, 3250, 2000, 8000, 0, -1, 0, 0, 0, 0, 0},
    {"Hikkaduwa",      29, Yellow,    7000, 650, 650, 7000, 3250, 2000, 8000, 0, -1, 0, 0, 0, 0, 0},

    // Green group — house 2500, hotel 10000, mortgage 4000
    {"Jaffna Town",    31, Green,     8000, 750, 750, 8000, 4000, 2500, 10000, 0, -1, 0, 0, 0, 0, 0},
    {"Nallur",         32, Green,     8300, 780, 780, 8300, 4000, 2500, 10000, 0, -1, 0, 0, 0, 0, 0},
    {"Trincomalee",    34, Green,     8500, 800, 800, 8500, 4000, 2500, 10000, 0, -1, 0, 0, 0, 0, 0},

    // Dark Blue group — house 3000, hotel 12000, mortgage 5000
    {"Nuwara Eliya",   37, DarkBlue, 10000, 1000, 1000, 10000, 5000, 3000, 12000, 0, -1, 0, 0, 0, 0, 0},
    {"Galle Face",     39, DarkBlue, 12000, 1200, 1200, 12000, 5000, 3000, 12000, 0, -1, 0, 0, 0, 0, 0}
};


//wrong morgaged and base  values
struct railway railways[4] = {
    {"Colombo Fort Railway Station", 5,  8000, 8000, 250, 250, 4000, -1, 0, 0},
    {"Kandy Railway Station",        15, 8000, 8000, 250, 250, 4000, -1, 0, 0},
    {"Galle Railway Station",        25, 8000, 8000, 250, 250, 4000, -1, 0, 0},
    {"Jaffna Railway Station",       35, 8000, 8000, 250, 250, 4000, -1, 0, 0}
};

struct utility utilities[2] = {
    {"Ceylon Electricity Board",                 12, 6000, 6000, 3000, -1, 0, 0, 0,0},
    {"National Water Supply and Drainage Board", 28, 6000, 6000, 3000, -1, 0, 0, 0,0}
};

struct insuranceCompany insuranceCompanies[2] = {
    {"Sri Lanka Insurance", 17},
    {"Ceylinco Insurance", 33}
};

struct gameData gameInfo = {0, 0};
struct loan playerLoans[4] = {{0}};

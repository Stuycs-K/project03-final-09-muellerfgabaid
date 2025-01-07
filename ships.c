#include "ships.h"

//Zero represents empty space
//One represents the ship's body
//Two represents the ship's coordinate reference point

const int board[4][4] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

const int battleshipLeft[3] = {2,1,1};
const int battleshipUp[3][1] = {
    {2},
    {1},
    {1},
};

const int destroyerUp[2] = {2, 1};
const int destroyerLeft[2][1] = {
    {2},
    {1}
};

const int carrierQ1[2][2] = {
    {0, 2},
    {1, 1}
};
const int carrierQ2[2][2] = {
    {2, 0},
    {1, 1}
};
const int carrierQ3[2][2] = {
    {0, 1},
    {2, 1}
};
const int carrierQ4[2][2] = {
    {0, 1},
    {1, 2}
};
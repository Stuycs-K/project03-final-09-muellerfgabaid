#ifndef PARSEDATA_H
#define PARSEDATA_H

// Rock - Paper - Scissors 
#define ROCK 0
#define PAPER 1
#define SCISSORS 2

#define VALID 0
#define INVALID 1

#define LOSE 0
#define WIN 1

union data {
    int choice;
};

struct response {
    int isValid;
    union data data;
};

#endif

#ifndef PARSEDATA_H
#define PARSEDATA_H

// client message types
#define C_MOVE 0
#define C_PLACE 1

// server message types
#define S_GAME_OVER 0
#define S_RESULT 1 // hit or miss
#define S_OPP_MOVE 2

struct coord {
    char x;
    char y;
};

union data {
    struct coord move;
    struct coord place;
    char result;
    struct coord opp_move;
};

struct response {
    char type;
    union data data;
};

struct response parse_server_response(int *msg);
#endif

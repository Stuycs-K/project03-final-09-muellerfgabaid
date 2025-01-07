#include "parseData.h"
#include "string.h"

int parseServerResponse(char * msg, char * msg_type, char * data) {
    char *curr = msg;
    char * token;
    token = strsep(&curr, "|");
    strcpy(msg_type, token);
    strcpy(data, curr);
}
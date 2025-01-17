#ifndef SUBSERVER_H
#define SUBSERVER_H

#include "game.h"

/* returns pp fd to read result from subserver */
int fork_subserver(struct client *clients, int num_clients);

#endif

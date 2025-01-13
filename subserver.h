#ifndef SUBSERVER_H
#define SUBSERVER_H

/* returns pp fd to read result from subserver */
int fork_subserver(int **clients, int num_clients);

#endif

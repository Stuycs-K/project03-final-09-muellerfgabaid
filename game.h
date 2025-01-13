#ifndef GAME_H
#define GAME_H
void send_to_client(int * client, int data);
int get_winner(int r1, int r2);
void play_game(int * client1, int * client2, int * result);
#endif

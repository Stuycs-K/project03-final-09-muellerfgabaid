#ifndef GAME_H
#define GAME_H
void send_to_client(int * client, int data);
int get_winner(int r1, int r2);
void play_game_server(int * to_client1, int * to_client2, int * from_client1, int * from_client2, int * result);
int get_user_turn();
void play_game_client(int to_server, int from_server);
#endif

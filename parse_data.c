#include "parse_data.h"
#include "pipe_networking.h"

void getInput(int from, int to) {
    int in;
    char input[100];
    printf("Enter your move: (Rock / Paper / Scissors\n)");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("ERROR\n");
        exit(1);
      }
    write(to, &input, sizeof(input));
    read(from, &in, sizeof(in));
    if (in != VALID) {
        printf("INVALID INPUT\n");
        getInput(from, to);
    }
}

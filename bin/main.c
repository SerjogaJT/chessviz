#include "chessviz.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  struct step *movements=NULL;
  int end, hire = 0;
  if (readFile(&movements, &end) != 0) {
    printf("Count the game failed.\n");
    return 0;
  }
  char board[8][8] = {"rnbqkbnr", "pppppppp", "        ", "        ", "        ", "        ", "PPPPPPPP", "RNBQKBNR"};
  copyBoard(movements, board, hire);
  int run = 1;
  int enter;
  while (run) {
    system("clear");
    printf("Stroke number: %d\n", hire);
    if (movements[hire].msW == 2)
      printf("WHITE WIN");
    if (movements[hire].msB == 2)
      printf("BLACK WIN");
    printf("\n");
    getBoard(board);
    printf("To control, enter \"2\" - next move or \"1\"- previous move\n");
    printf("Enter \"3\" to exit\n");
    scanf("%d", &enter);
    if (enter == 3)
      run = 0;
    else if (enter == 2) {
      if (hire + 1 > end)
        continue;
      next(movements, board, hire);
      ++hire;
    } else if (enter == 1) {
      if (hire == 0)
        continue;
      back(movements, board, hire);
      --hire;
    } else if (enter < 1 || enter > 3)
      run = 0;
  }

  return 0;
}

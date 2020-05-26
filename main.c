#include <stdio.h>
#include <stdlib.h>

void getBoard(char arr[8][8]);
void tostep(char *, char *);

int main() {
  char board[8][8] = {"rnbqkbnr", "pppppppp", "        ", "        ",
                      "        ", "        ", "pppppppp", "rnbqkbnr"};
  char figurs[5] = "RNBQK", step[10];
  int key[4];

  getBoard(board);
  while (1) {
    scanf("%s", step);
    if (step[0] != figurs[0] && step[0] != figurs[1] && step[0] != figurs[2] &&
        step[0] != figurs[3] && step[0] != figurs[4]) {
      key[0] = step[0] - 97;
      key[1] = step[1] - 49;
      key[2] = step[3] - 97;
      key[3] = step[4] - 49;
    } else {
      key[0] = step[1] - 97;
      key[1] = step[2] - 49;
      key[2] = step[4] - 97;
      key[3] = step[5] - 49;
    }
    tostep(&board[key[1]][key[0]], &board[key[3]][key[2]]);
    getBoard(board);
  }

  return 0;
}

void tostep(char *a, char *b) {
  *b = *a;
  *a = ' ';
}

void getBoard(char arr[8][8]) {
  system("clear");
  for (int i = 1; i <= 9; i++) {
    if (i == 9)
      printf("  a b c d e f g h");
    else {
      printf("%d ", i);
      for (int j = 0; j < 8; j++) {
        printf("%c ", arr[i - 1][j]);
      }
    }
    printf("\n");
  }
}

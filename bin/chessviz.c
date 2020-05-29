#include "chessviz.h"
#include <stdio.h>
#include <stdlib.h>

void tostep(char *a, char *b) {
  *b = *a;
  *a = ' ';
}

void getBoard(char arr[8][8]) {
  for (int i = 1; i <= 9; i++) {
    if (i == 9)
      printf("  a b c d e f g h");
    else {
      printf("%d ", i);
      for (int j = 0; j < 8; j++) {
        printf("%c ", arr[i - 1][j]);
      }
      if (i == 1)
        printf("\tWhite - Lowercase");
      if (i == 8)
        printf("\tBlack - Caps");
    }
    printf("\n");
  }
}

int readFile(struct step **movements, int *end) {
  FILE *gameSteps = NULL;
  unsigned int steps = 0;
  char str[30];
  //Ñ÷¸ò õîäîâ
  gameSteps = fopen("bin/game.txt", "r");
  if (gameSteps != NULL) {
    while (fgets(str, 30, gameSteps)) {
      steps++;
    }
    fclose(gameSteps);
    *end = steps - 1;
  } else
    return 1;
  //Çàïèñü Õîäîâ
  *movements = malloc(steps * sizeof(struct step));
  if (*movements == NULL)
    return 1;
  gameSteps = fopen("bin/game.txt", "r");
  if (gameSteps != NULL) {
    char figurs[6] = "RNBQKp";
    steps = 0;
    while (fgets(str, 30, gameSteps)) {
      //Íîìåð Õîäà
      (*movements)[steps].number = steps + 1;
      //Áåëûå
      int ptr = 3;
      if (str[ptr] != figurs[0] && str[ptr] != figurs[1] &&
          str[ptr] != figurs[2] && str[ptr] != figurs[3] &&
          str[ptr] != figurs[4]) {
        //Ôèãóðà, êëþ÷è è òèï õîäà
        (*movements)[steps].figurW = figurs[5];
        (*movements)[steps].keysW[0] = str[ptr++] - 97;
        (*movements)[steps].keysW[1] = str[ptr++] - 49;
        (*movements)[steps].stepW = str[ptr++];
        (*movements)[steps].keysW[2] = str[ptr++] - 97;
        (*movements)[steps].keysW[3] = str[ptr++] - 49;
      } else {
        //Ôèãóðà, êëþ÷è è òèï õîäà
        (*movements)[steps].figurW = str[ptr++];
        (*movements)[steps].keysW[0] = str[ptr++] - 97;
        (*movements)[steps].keysW[1] = str[ptr++] - 49;
        (*movements)[steps].stepW = str[ptr++];
        (*movements)[steps].keysW[2] = str[ptr++] - 97;
        (*movements)[steps].keysW[3] = str[ptr++] - 49;
      }
      if (str[ptr] == '#')
        (*movements)[steps].msW = 2;
      else if (str[ptr] == '+')
        (*movements)[steps].msW = 1;
      else
        (*movements)[steps].msW = 0;
      ptr++;
      //×¸ðíûå
      if (str[ptr] != figurs[0] && str[ptr] != figurs[1] &&
          str[ptr] != figurs[2] && str[ptr] != figurs[3] &&
          str[ptr] != figurs[4]) {
        //Ôèãóðà, êëþ÷è è òèï õîäà
        (*movements)[steps].figurB = figurs[5];
        (*movements)[steps].keysB[0] = str[ptr] - 97;
        (*movements)[steps].keysB[1] = str[++ptr] - 49;
        (*movements)[steps].stepB = str[++ptr];
        (*movements)[steps].keysB[2] = str[++ptr] - 97;
        (*movements)[steps].keysB[3] = str[++ptr] - 49;
      } else {
        //Ôèãóðà, êëþ÷è è òèï õîäà
        (*movements)[steps].figurB = str[ptr++];
        (*movements)[steps].keysB[0] = str[ptr++] - 97;
        (*movements)[steps].keysB[1] = str[ptr++] - 49;
        (*movements)[steps].stepB = str[ptr++];
        (*movements)[steps].keysB[2] = str[ptr++] - 97;
        (*movements)[steps].keysB[3] = str[ptr++] - 49;
      }
      if (str[ptr] == '#')
        (*movements)[steps].msB = 2;
      else if (str[ptr] == '+')
        (*movements)[steps].msB = 1;
      else
        (*movements)[steps].msB = 0;
      steps++;
    }
    fclose(gameSteps);
  } else
    return 1;

  return 0;
}

void next(struct step *movements, char board[8][8], int hire) {
  if (checkStep(movements, hire)) {
    printf("Quit the game and check the input of the file on move number %d\n",
           hire);
    system("pause");
  } else {
    tostep(&board[movements[hire].keysW[1]][movements[hire].keysW[0]],
           &board[movements[hire].keysW[3]][movements[hire].keysW[2]]);
    tostep(&board[movements[hire].keysB[1]][movements[hire].keysB[0]],
           &board[movements[hire].keysB[3]][movements[hire].keysB[2]]);
    copyBoard(movements, board, hire + 1);
  }
}

int checkStep(struct step *movements, int hire) {
  if (movements[hire].figurW == 'p' || movements[hire].figurB == 'p') {
    //ïðîâåðêà íà ïåðâûé õîä ïåøêè
    int i, j;
    if (movements[hire].keysW[1] == 1)
      i = 1;
    else
      i = 0;
    if (movements[hire].keysB[1] == 6)
      j = 1;
    else
      j = 0;
    if (movements[hire].figurW == 'p') {
      if (movements[hire].keysW[0] != movements[hire].keysW[2] &&
          movements[hire].stepW != 'e') {
        printf("Wrong move of the white pawn. (Horizont)\n");
        return 1;
      }
      if (movements[hire].keysW[3] - movements[hire].keysW[1] > i + 1) {
        printf("Wrong move of the white pawn. (Vertical)\n");
        return 1;
      }
    }
    if (movements[hire].figurB == 'p') {
      if (movements[hire].keysB[1] - movements[hire].keysB[3] > j + 1) {
        printf("Wrong move of the white pawn. (Horizont)\n");
        return 1;
      }
      if (movements[hire].keysB[0] != movements[hire].keysB[2] &&
          movements[hire].stepB != 'e') {
        printf("Wrong move of the white pawn. (Horizont)\n");
        return 1;
      }
    }
  }
  return 0;
}

void back(struct step *movements, char board[8][8], int hire) {
  setBoard(movements, board, hire - 1);
}

void copyBoard(struct step *movements, char board[8][8], int hire) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      movements[hire].lastMove[i][j] = board[i][j];
    }
  }
}

void setBoard(struct step *movements, char board[8][8], int hire) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      board[i][j] = movements[hire].lastMove[i][j];
    }
  }
}

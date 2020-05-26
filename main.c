#include <stdio.h>
#include <stdlib.h>

struct step {
  int number; // номер хода
  char figurW;
  char stepW; /*e - взятиe на проходе; + - шах; # - мат; Z и z - ракировки*/
  int keysW[4]; // ключи хода белых
  int msW;      //Мат = 2; шах = 1; иначе 0
  char figurB;
  char stepB;
  int keysB[4]; // ключи хода чёрных
  int msB;
  char lastMove[8][8]; // прошлый ход
};

void getBoard(char arr[8][8]);
void tostep(char *, char *);
int readFile(struct step **, int *);
void next(struct step *, char arr[8][8], int);
void back(struct step *, char arr[8][8], int);
void setBoard(struct step *, char board[8][8], int);
void copyBoard(struct step *, char board[8][8], int);
void back(struct step *, char board[8][8], int);

int main() {
  struct step *movements = NULL;
  int end, hire = 0;
  if (readFile(&movements, &end) != 0) {
    printf("Count the game failed.\n");
    return 0;
  }
  char board[8][8] = {"rnbqkbnr", "pppppppp", "        ", "        ",
                      "        ", "        ", "PPPPPPPP", "RNBQKBNR"};
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
  //Счёт ходов
  gameSteps = fopen("game.txt", "r");
  if (gameSteps != NULL) {
    while (fgets(str, 30, gameSteps)) {
      steps++;
    }
    fclose(gameSteps);
    *end = steps - 1;
  } else
    return 1;
  //Запись Ходов
  *movements = malloc(steps * sizeof(struct step));
  if (*movements == NULL)
    return 1;
  gameSteps = fopen("game.txt", "r");
  if (gameSteps != NULL) {
    char figurs[6] = "RNBQKp";
    steps = 0;
    while (fgets(str, 30, gameSteps)) {
      //Номер Хода
      (*movements)[steps].number = steps + 1;
      //Белые
      int ptr = 3;
      if (str[ptr] != figurs[0] && str[ptr] != figurs[1] &&
          str[ptr] != figurs[2] && str[ptr] != figurs[3] &&
          str[ptr] != figurs[4]) {
        //Фигура, ключи и тип хода
        (*movements)[steps].figurW = figurs[5];
        (*movements)[steps].keysW[0] = str[ptr++] - 97;
        (*movements)[steps].keysW[1] = str[ptr++] - 49;
        (*movements)[steps].stepW = str[ptr++];
        (*movements)[steps].keysW[2] = str[ptr++] - 97;
        (*movements)[steps].keysW[3] = str[ptr++] - 49;
      } else {
        //Фигура, ключи и тип хода
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
      //Чёрные
      if (str[ptr] != figurs[0] && str[ptr] != figurs[1] &&
          str[ptr] != figurs[2] && str[ptr] != figurs[3] &&
          str[ptr] != figurs[4]) {
        //Фигура, ключи и тип хода
        (*movements)[steps].figurB = figurs[5];
        (*movements)[steps].keysB[0] = str[ptr] - 97;
        (*movements)[steps].keysB[1] = str[++ptr] - 49;
        (*movements)[steps].stepB = str[++ptr];
        (*movements)[steps].keysB[2] = str[++ptr] - 97;
        (*movements)[steps].keysB[3] = str[++ptr] - 49;
      } else {
        //Фигура, ключи и тип хода
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
  tostep(&board[movements[hire].keysW[1]][movements[hire].keysW[0]],
         &board[movements[hire].keysW[3]][movements[hire].keysW[2]]);
  tostep(&board[movements[hire].keysB[1]][movements[hire].keysB[0]],
         &board[movements[hire].keysB[3]][movements[hire].keysB[2]]);
  copyBoard(movements, board, hire + 1);
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

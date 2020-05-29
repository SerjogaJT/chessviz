#pragma once

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
int checkStep(struct step *, int);
void back(struct step *, char arr[8][8], int);
void setBoard(struct step *, char board[8][8], int);
void copyBoard(struct step *, char board[8][8], int);
void back(struct step *, char board[8][8], int);

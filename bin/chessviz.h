#pragma once

struct step {
  int number; // ����� ����
  char figurW;
  char stepW; /*e - �����e �� �������; + - ���; # - ���; Z � z - ���������*/
  int keysW[4]; // ����� ���� �����
  int msW;      //��� = 2; ��� = 1; ����� 0
  char figurB;
  char stepB;
  int keysB[4]; // ����� ���� ������
  int msB;
  char lastMove[8][8]; // ������� ���
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

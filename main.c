#include <stdio.h>
#include <stdlib.h>

void getBoard(char arr[8][8])
{
	for(int i = 1; i <= 9; i++){
		if(i == 9)
			printf("  a b c d e f g h");
		else {
			printf("%d ", i);
			for(int j = 0; j < 8; j++){
				printf("%c ", arr[i-1][j]);
			}
		}
		printf("\n");
	}
}

int main()
{
	char board[8][8] = {"rnbqkbnr","pppppppp","        ","        ","        ","        ","pppppppp","rnbqkbnr"};

	getBoard(board);
	return 0;
}
#include <stdio.h>
#include<time.h>
#include<stdlib.h>

#define ROW 9
#define COL 9
#define ROWS ROW+2
#define COLS COL+2

void InitBoard(char board[ROWS][COLS], int r, int c, char set);

void DisplayBoard(char board[ROWS][COLS], int r, int c);


void SetMine(char board[ROWS][COLS], int r, int c);
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int r, int c);

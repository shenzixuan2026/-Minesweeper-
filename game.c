#include <stdio.h>
#include<stdlib.h>

#include "game.h"
#include<time.h>


void InitBoard(char board [ROWS][COLS], int r, int c, char set )
{
    int i = 0;
    int j = 0;
    for (i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
        {
            board[i][j] = set;
        }
    }
}

void DisplayBoard(char board[ROWS][COLS], int r, int c)
{
    int i = 0;
    int j = 0;
    for(j = 0; j < c; j++)
    {
        printf("%d ", j);
    }
    printf("\n");
    for (i = 1; i < r; i++)
    {
        printf("%d ", i);
        for(j = 1; j < c; j++)
        {

            //%c打印字符
            printf("%c ", board[i][j]);
        
            
        }
        printf("\n");
    }
    printf("\n");
}  


void SetMine(char board[ROWS][COLS], int r, int c)
{
    int count = 10;
    while(count)
    {
    int x = rand() % r + 1;
    int y = rand() % c + 1;
    if(board[x][y] == '0')
    {
        board[x][y] = '1';
        count -- ;
    }
    
    }
    
}

size_t GetMineCount(char mine[ROWS][COLS], int x, int y)
{
    //九宫格，定义中间模块为(x,y)
    return mine[x - 1][y] + mine[x - 1][y - 1] + mine[x][y - 1] + mine[x + 1][y - 1] +
    mine[x + 1][y] + mine[x + 1][y + 1] + mine[x][y + 1] + 
    mine[x - 1][y + 1] - 8*'0';


}

/*
 * 展开函数：当点开的格子周围没有雷时，
 * 自动向四面八方扩散展开，直到遇到有雷的边界。
 * 通过 win 指针累计已经排查的非雷格数量。
 */
void Spread(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y, int* win)
{
    //防止越界访问（只在 1~ROW 1~COL 范围内处理）
    if (x < 1 || x > ROW || y < 1 || y > COL)
        return;
    //已经展开过的地方，或者本身是雷，就不再处理
    if (show[x][y] != '*' || mine[x][y] == '1')
        return;

    size_t count = GetMineCount(mine, x, y);
    show[x][y] = (char)count + '0';
    (*win)++;

    //如果周围有雷，就只显示数字，不再向下展开
    if (count == 0)
    {
        Spread(mine, show, x - 1, y - 1, win);
        Spread(mine, show, x - 1, y, win);
        Spread(mine, show, x - 1, y + 1, win);
        Spread(mine, show, x, y - 1, win);
        Spread(mine, show, x, y + 1, win);
        Spread(mine, show, x + 1, y - 1, win);
        Spread(mine, show, x + 1, y, win);
        Spread(mine, show, x + 1, y + 1, win);
    }
}

void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int r, int c)
{
    int x = 0;
    int y = 0;
    int win = 0;
    
    //先控制输入坐标的范围在r和c之间
while(win < r*c-10)
{
    printf("请输入想要排查的雷的坐标:");
    scanf("%d%d" , &x, &y);

    if(x >= 1 && x <= r && y >= 1 && y <= c)
    {
        if(show[x][y] == '*')
        {
            if(mine[x][y] == '1')
            {
                printf("很遗憾，你被炸死了，吼吼哈哈哈\n");
                DisplayBoard(mine, ROW, COL);
                //break只能在for while等语句中使用，且这个判断是个一直循环的过程
                break;

            }else{
                //用展开函数处理：周围无雷会自动扩散
                Spread(mine, show, x, y, &win);
                DisplayBoard(show, ROW, COL);


            }


        }else{
            printf("输入的坐标已被排查过，请重新输入\n");
        }

    }
    else{
        printf("输入的坐标非法，重新输入\n");
    }
    

}  
if(win == r*c-10)
{
    printf("恭喜您，排雷成功\n");
    DisplayBoard(mine, ROW, COL);
}
}
    
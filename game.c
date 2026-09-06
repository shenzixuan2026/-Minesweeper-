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

static size_t GetMineCount(char mine[ROWS][COLS], int x, int y)
{
    //九宫格，定义中间模块为(x,y)
    return mine[x - 1][y] + mine[x - 1][y - 1] + mine[x][y - 1] + mine[x + 1][y - 1] +
    mine[x + 1][y] + mine[x + 1][y + 1] + mine[x][y + 1] + 
    mine[x - 1][y + 1] - 8*'0';


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
                size_t count = GetMineCount(mine, x, y);
                show[x][y] = (char)count + '0'; 
                DisplayBoard(show, ROW, COL);
                win++;


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
    
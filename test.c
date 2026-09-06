#include <stdio.h>
#include<stdlib.h>
#include "game.h"
#include<time.h>

void menu(void) 
{
    printf("------------\n");
    printf("------------\n");
    printf("---1.play---\n");
    printf("---0.exit---\n");
    printf("------------\n");
    printf("------------\n");

}

void game(void)
{   
    char mine[ROWS][COLS];
    char show[ROWS][COLS];
    //初始化棋盘
    InitBoard(mine, ROWS, COLS, '0' );
    InitBoard(show, ROWS, COLS, '*' );
    //打印棋盘
    //打印棋盘的下面语句是有顺序的
    //打印棋盘
    DisplayBoard(show, ROW, COL);
    //安雷，然后再把下面的mine展示出来
    SetMine(mine, ROW, COL);
    DisplayBoard(mine, ROW, COL);
    //排雷
    FindMine(mine, show, ROW, COL);

    
    printf("游戏开始啦\n");
}

int main(void)
{
    int input = 0;
    srand((unsigned int)time(NULL));
    do
    {
        menu();
        printf("请选择：");

        /*
         * scanf 读不到数字（例如终端输入结束）时会失败。
         * 此时必须退出，否则 input 会保留上一次的值并无限循环。
         */
        //scanf读一个整数放进input里，若读到整数就返回1往下走，若不行就返回0进入if支线
        if (scanf("%d", &input) != 1)
        {
            printf("没有读到有效输入，游戏已退出。\n");
            return 0;
        }

        switch(input){
            case 1:
                game();
                break;
            case 0:
                printf("退出游戏\n");
                break;
            default:
                printf("输入错误，请重新选择\n");
        }

    } while (input != 0);

    return 0;
}

/*
 * 初学项目使用：把游戏功能的实现一并编译进 test.c。
 * 因此无论 VS Code 执行 "gcc test.c"，还是运行本项目的构建任务，
 * InitBoard 和 DisplayBoard 都能被找到。
 */
#include "game.c"

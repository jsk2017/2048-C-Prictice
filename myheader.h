#ifndef __H__MYHEADER
#define __H__MYHEADER
#include<stdint.h>
#include<stdio.h>

#define SIZE 4
/*
头文件编写的一些说明：

在头文件中尽量不要包含其他头文件，因为这会使预处理阶段的速度变慢
头文件中包含 外部需要使用的全局变量 数据结构 函数声明 宏定义
外部全局变量 在头文件中定义 只能进行一次初始化

*/
extern uint32_t score;
extern uint32_t scheme;

//printf for test
void printfBoard(uint8_t board[SIZE][SIZE]);

//Paint 
void getColor(uint8_t value,char *color,size_t length); //这个函数没有修改！

void drawBoard(uint8_t board[SIZE][SIZE]);

void addRandom(uint8_t board[SIZE][SIZE]);

void initBoard(uint8_t board[SIZE][SIZE]);

//move or merge
void rotateBoard(uint8_t board[SIZE][SIZE]);

uint8_t findTarget(uint8_t array[SIZE],uint8_t x,uint8_t stop);

bool findPairDown(uint8_t board[SIZE][SIZE]);

bool slideArray(uint8_t array[SIZE]);

bool moveUp(uint8_t board[SIZE][SIZE]);

bool moveLeft(uint8_t board[SIZE][SIZE]);

bool moveRight(uint8_t board[SIZE][SIZE]);

bool moveDown(uint8_t board[SIZE][SIZE]);


//设置终端
void setBufferedInput(bool enable);

void signal_callback_handler(int signum);



uint8_t countEmpty(uint8_t board[SIZE][SIZE]);


bool gameEnded(uint8_t board[SIZE][SIZE]);



#endif
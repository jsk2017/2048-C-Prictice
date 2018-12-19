#ifndef __H__MYHEADER
#define __H__MYHEADER

#include<stdint.h>
#include<stdio.h>
#include<stdbool.h>

#define SIZE 4

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

bool gameWin(uint8_t board[SIZE][SIZE]);

bool checkBoard(uint8_t board[SIZE][SIZE]);

#endif
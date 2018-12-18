#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

// 清除屏幕
#define CLEAR() printf("\033[2J")
 
// 上移光标
#define MOVEUP(x) printf("\033[%dA", (x))
 
// 下移光标
#define MOVEDOWN(x) printf("\033[%dB", (x))
 
// 左移光标
#define MOVELEFT(y) printf("\033[%dD", (y))
 
// 右移光标
#define MOVERIGHT(y) printf("\033[%dC",(y))
 
// 定位光标
#define MOVETO(x,y) printf("\033[%d;%dH", (x), (y))
 
// 光标复位
#define RESET_CURSOR() printf("\033[H")
 
// 隐藏光标
#define HIDE_CURSOR() printf("\033[?25l")
 
// 显示光标
#define SHOW_CURSOR() printf("\033[?25h")
 
//反显
#define HIGHT_LIGHT() printf("\033[7m")
#define UN_HIGHT_LIGHT() printf("\033[27m")

void printAuthorColorful(int color){

    char * line1 = "__________             ._____________\n";             
    char * line2 = "\\______   \\_____     __| _/\\______   \\ ___________\n";
    char * line3 = " |    |  _/\\__  \\   / __ |  |       _// __ \\_  __ \\\n";
    char * line4 = " |    |   \\ / __ \\_/ /_/ |  |    |   \\  ___/|  | \\/\n";
    char * line5 = " |______  /(____  /\\____ |  |____|_  /\\___  >__|\n";   
    char * line6 = "        \\/      \\/      \\/         \\/     \\/       ";

    // printf("\033[2J\n");
    printf("\033[%dm%s",color,line1);
    printf("\033[%dm%s",color,line2);
    printf("\033[%dm%s",color,line3);
    printf("\033[%dm%s",color,line4);
    printf("\033[%dm%s",color,line5);
    printf("\033[%dm%s",color,line6);
}
int main(int argc,char **argv)
{
    printAuthorColorful(31);

    
    // printf("\033[31m    The color,%s!   \033[1m\n","haha");//红色
    // printf("\033[31mThe color,%s!\033[4m\n","haha");//橘黄色
    // printf("\033[31mThe color,%s!\033[5m\n","haha");//红色+下划线
    // printf("\033[31mThe color,%s!\033[7m\n","haha");//反显
    // printf("\033[31mThe color,%s!\033[0m\n","haha");
    // printf("\033[47;31mThe color,%s!\033[0m\n","haha");
    // printf("\033[47mThe color,%s!\033[0m\n","haha");
    // sleep(2);
    // printf("\033[47m%s!\033[5A\n","up 5");
    // sleep(2);
    // printf("\033[47m%s!\033[9B\n","down 9");
    // sleep(2);
    // printf("\033[47m%s!\033[19C\n","right 19");
    // printf("right19");
    // sleep(2);
    // printf("\033[47m%s!\033[10D\n","left 10");
    // printf("left 10");
    // sleep(2);
    // printf("\033[47m%s!\033[50;20H\n","move to y:50,x 20");
    // printf("y50 x 20");
    // sleep(2);
    // printf("\033[47m%s!\033[?25l\n","hide cursor");
    // sleep(2);
    // printf("\033[47m%s!\033[?25h\n","sow cursor");
    // sleep(2);
    // printf("\033[47m%s!\033[2J\n","clear scleen");
    // sleep(2);
 
    return EXIT_SUCCESS;

}

   
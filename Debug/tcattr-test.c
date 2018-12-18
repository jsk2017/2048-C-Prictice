#include<stdio.h>
#include<termios.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdbool.h>

int main(int argc,char ** argv){

    printf("Test for tcgetattr & tcsetattr functions\n");
    char c ;
    struct termios term;

    //获取用户的输入 但不在终端显示 可以用在获取用户密码上
    if(tcgetattr(STDIN_FILENO,&term)==-1){
        printf("tcgetattr STDIN_FILENO failed!\n");
        return 1;
    }else{
        term.c_lflag &= (~ECHO & ~ ICANON);
        tcsetattr(STDIN_FILENO,TCSANOW,&term);
    }
    while(true){
        c = getchar();
        switch(c){
            case 113 :
                printf("\nDone q");
                exit(1);
            default:
                break;
        }
    }
    return 0;
}
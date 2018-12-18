#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
int flag = 0;
static void signal_handler(int signum){
    flag = 1;
}

int main(int argc,char ** argv){
    signal(SIGINT,signal_handler);
    while(1){
        if(flag){
            // printf("\033[?25l\033[2J");
            printf("Done");
            flag = 0;
        }
    }
    return 0;
}
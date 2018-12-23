//c 语言中 printf 中的缓冲区问题
//因为 printf 是带缓冲区的显示 如果需要立即显示那么有两种方法
// 1. setbuf(stdout,NULL); 在程序开头设置
// 2. fflush(stdout); 在打印之前清空stdout缓冲区
#include<stdio.h>

int main(int argc,char ** argv){
    fflush(stdout);
    setbuf(stdout,NULL);
    printf("helllo!\n");
    return 0;
}
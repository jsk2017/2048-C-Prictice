#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>


void str2hex(char *source,char *dest,int keyLen){
    uint8_t i;  
    uint8_t highByte, lowByte;  
  
    for (i = 0; i < keyLen; i++)  
    {  
        highByte = source[i] >> 4;  
        lowByte = source[i] & 0x0f ;  
  
        highByte += 0x30;  
  
        if (highByte > 0x39)  
                dest[i * 2] = highByte + 0x07;  
        else  
                dest[i * 2] = highByte;  
  
        lowByte += 0x30;  
        if (lowByte > 0x39)  
            dest[i * 2 + 1] = lowByte + 0x07;  
        else  
            dest[i * 2 + 1] = lowByte;  
    }  
    return ;  
}

int getStr(char *buffer,int maxLen){
    char c;  // 读取到的一个字符
    int len = 0;  // 当前输入的字符串的长度
    // 一次读取一个字符，保存到buffer
    // 直到遇到换行符(\n)，或者长度超过maxLen时，停止读取
    while( (c=getchar()) != '\n' ){
        buffer[len++]=c;  // 将读取到的字符保存到buffer
        if(len>=maxLen){
            break;
        }
    }
    buffer[len]='\0';  // 读取结束，在末尾手动添加字符串结束标志
    fflush(stdin);  // 刷新输入缓冲区
    return len;
}



int main(int argc,char ** argv){

    char *hexKey=NULL;
    uint8_t keyLen = 0;
    char key[9];
    keyLen = (uint8_t)getStr(key,8);
    hexKey = (char *)malloc(keyLen*2);
    str2hex(key,hexKey,keyLen);
    printf("%s",hexKey);
    return 0;
}
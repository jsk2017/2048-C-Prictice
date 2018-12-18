#include<stdio.h>
#include<stdint.h>
#include<string.h>


int main(int argc,char ** argv){

    char s[8];
    // printf("%u",(uint32_t)1<<2);
    snprintf(s,8,"%u",(uint32_t)1<<1);
    uint8_t len = strlen(s);
    uint8_t t = 7 - strlen(s);
    printf("%*s%s%*s",t-t/2,"*",s,t/2,"*");
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>

int main(int argc,char ** argv){
    char c;
    c = getchar();

    switch(c){
        case 97:            // 'a' key
        case 104:	         // 'h' key
        case 68:	        // 'd' arrow
            printf("%d Done",(uint8_t)c);
            break;
        default:
            break;
    }
    printf("\n");
    return 0;
}
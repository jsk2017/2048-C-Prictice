#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

uint8_t scheme = 0;



void getColor(uint8_t value, char *color, size_t length) {
	uint8_t original[] = {8,255,1,255,2,255,3,255,4,255,5,255,6,255,7,255,9,0,10,0,11,0,12,0,13,0,14,0,255,0,255,0};
	uint8_t blackwhite[] = {232,255,234,255,236,255,238,255,240,255,242,255,244,255,246,0,248,0,249,0,250,0,251,0,252,0,253,0,254,0,255,0};
	uint8_t bluered[] = {235,255,63,255,57,255,93,255,129,255,165,255,201,255,200,255,199,255,198,255,197,255,196,255,196,255,196,255,196,255,196,255};
	uint8_t *schemes[] = {original,blackwhite,bluered};
	uint8_t *background = schemes[scheme]+0;
	uint8_t *foreground = schemes[scheme]+1;

	if (value > 0) while (value--) {
		if (background+2<schemes[scheme]+sizeof(original)) {
			background+=2;
			foreground+=2;
		}
	}

    printf("%d+%d",*foreground,*background);
	snprintf(color,length,"\033[38;5;%d;48;5;%dm",*foreground,*background);
}

int main(int argc,char ** argv){
    char color[40];
    char reset[]="\033[m";
    uint8_t value = 0;
    getColor(value,color,40);
    printf("Done!\n");
    printf("%s",color);
    printf("           ");
    printf("%s",reset);
    return 0;
}
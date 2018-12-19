#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<stdbool.h>
#include<unistd.h>
#include<string.h>
#include"myheader.h"
#include"author.h"

int test(){
    uint8_t array[SIZE];
	// these are exponents with base 2 (1=2 2=4 3=8)
	uint8_t data[] = {
		0,0,0,1,	1,0,0,0,
		0,0,1,1,	2,0,0,0,
		0,1,0,1,	2,0,0,0,
		1,0,0,1,	2,0,0,0,
		1,0,1,0,	2,0,0,0,
		1,1,1,0,	2,1,0,0,
		1,0,1,1,	2,1,0,0,
		1,1,0,1,	2,1,0,0,
		1,1,1,1,	2,2,0,0,
		2,2,1,1,	3,2,0,0,
		1,1,2,2,	2,3,0,0,
		3,0,1,1,	3,2,0,0,
		2,0,1,1,	2,2,0,0
	};
	uint8_t *in,*out;
	uint8_t t,tests;
	uint8_t i;
	bool success = true;

	tests = (sizeof(data)/sizeof(data[0]))/(2*SIZE);
	for (t=0;t<tests;t++) {
		in = data+t*2*SIZE;
		out = in + SIZE;
		for (i=0;i<SIZE;i++) {
			array[i] = in[i];
		}
		slideArray(array);
		for (i=0;i<SIZE;i++) {
			if (array[i] != out[i]) {
				success = false;
			}
		}
		if (success==false) {
			for (i=0;i<SIZE;i++) {
				printf("%d ",in[i]);
			}
			printf("=> ");
			for (i=0;i<SIZE;i++) {
				printf("%d ",array[i]);
			}
			printf("expected ");
			for (i=0;i<SIZE;i++) {
				printf("%d ",in[i]);
			}
			printf("=> ");
			for (i=0;i<SIZE;i++) {
				printf("%d ",out[i]);
			}
			printf("\n");
			break;
		}
	}
	if (success) {
		printf("All %u tests executed successfully\n",tests);
	}
	return !success;
}


int main(int argc,char **argv){
    uint8_t board[SIZE][SIZE];
    char c;
    bool success;

    if(argc ==2 && strcmp(argv[1],"test")==0){
        return test();
    }
    if(argc ==2 && strcmp(argv[1],"blackwhite")==0){
        scheme = 1;
    }
    if(argc ==2 && strcmp(argv[1],"bluered")==0){
        scheme = 2;
    }

    //print author's name
    printAuthorColorful(31);

    printf("\033[?25l\033[2J");//隐藏光标 & 清屏

    // register signal handler for when ctrl-c is pressed!
    signal(SIGINT,signal_callback_handler);
    
    initBoard(board);

    // printfBoard(board);

    setBufferedInput(false);

    while(true){
        c = getchar();
        if(c == -1){
            puts("\nError! Can't read keyboard input!");
            break;
        }
        switch(c){
            case 97:            // 'a' key
			case 104:	         // 'h' key
			case 68:	        // left arrow
				success = moveLeft(board);  
                break;
            case 100:	// 'd' key
			case 108:	// 'l' key
			case 67:	// right arrow
				success = moveRight(board); 
                break;
			case 119:	// 'w' key
			case 107:	// 'k' key
			case 65:	// up arrow
				success = moveUp(board);    
                break;
			case 115:	// 's' key
			case 106:	// 'j' key
			case 66:	// down arrow
				success = moveDown(board);  
                break;
			default: 
                success = false;
                break;
        }

        if(success){
            drawBoard(board);

            usleep(150000);
            addRandom(board);

            drawBoard(board);
            if(gameEnded(board)){
                printf("        GAME OVER       \n");
                break;
            }
        }

        if(c == 'q'){
            printf("        QUIT? (y/n)         \n");
			c=getchar();
			if (c=='y') {
				break;
			}

            drawBoard(board);
        }

        if(c == 'r'){
            printf("        RESET? (y/n)         \n");
			c=getchar();
			if (c=='y') {
				initBoard(board);
			}

            drawBoard(board);
        }
    }
    //Over restore terminal attr
    setBufferedInput(true);

    printf("\033[?25h\033[m");

	return EXIT_SUCCESS;
}
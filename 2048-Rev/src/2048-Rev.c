#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<signal.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
#include<termios.h>

#include"myheader.h"
#include"author.h"

void test(){
    ;
}

int main(int argc,char ** argv){

    uint8_t board[SIZE][SIZE];
    bool success;
    char c;
    char input[8];
    struct termios new;
    //Gloabl config
    if(argc == 2){
        if(strcmp(argv[1],"test")==0){
            test();
        }
        if(strcmp(argv[1],"blackwhite")==0){
            scheme = 1;
        }
        if(strcmp(argv[1],"bluered")==0){
            scheme = 2;
        }
    }

    printAuthorColorful(31);


    printf("\033[?25l\033[2J");
    
    //register signal ctrl+c
    signal(SIGINT,signal_callback_handler);

    initBoard(board);

    drawBoard(board);

    setBufferedInput(false);

    while(true){
        c = getchar();
        if(c == -1){
            printf("\nError!");
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
            if(gameWin(board)){
                // paintWin();
                printf("        You Win!         \n");
                printf("Now,please input you flag:");
                checkBoard(board);//检查是否是 1-16
                setBufferedInput(true);
                printf("\033[?25h");
                scanf("%s",input);
                /*
                main_check 主要逻辑
                根据 board 进行hex
                将8位的key hex
                加密 最后和 score进行比较

                最后 paint flag
                */
                if(main_check()){
                    paintFlag();
                };

                break;
            }
            if(gameEnded(board)){
                printf("        GAME OVER         \n");
                break;
            }
        }
        if(c == 'q'){
            printf("        Quit? (Y/N)         \n");
            c = getchar();
            if(c =='y'){
                printf("        GAME OVER         \n");
                break;
            }
            drawBoard(board);
        }

        if(c == 'r'){
            printf("        Reset? (Y/N)         \n");
            c = getchar();
            if(c =='y'){
                initBoard(board);
            }
            drawBoard(board);
        }
    }

    return 0;
}
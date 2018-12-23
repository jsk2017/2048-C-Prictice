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
#include"antidebug.h"

void test(){
    ;
}

int main(int argc,char ** argv){

    uint8_t board[SIZE][SIZE];
    bool success;
    char c;
    char key[9];
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
    pid_sid();//简单的反调试
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
            if(gameWin()){//check score == 2**16+..+..+.. ==131070=0x0001fffe
                // paintWin();
                printf("        You Win!         \n");
                //这里在运行时没有立即打印出信息，这是因为缓冲区没有刷新，如果有必要的话可以使用fflush
                fflush(stdout);
                printf("Now,please input you key:");
                checkBoard(board);//check board 是否是 1-16
                setBufferedInput(true);
                printf("\033[?25h");

                uint8_t keyLen = (uint8_t)getStr(key,8);
                //correct key is aY2oPew9
                // printf("%s",input);
                /*
                main_check 主要逻辑
                根据 board 进行hex
                将8位的key hex
                加密 最后和 score进行比较

                最后 paint flag
                */
                //这里为了测试假设board和score已经符合要求
                if(!main_check(key,board,keyLen)){
                    paintFlag(key,keyLen);
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
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<termios.h>


#define SIZE 4

uint32_t score = 0;
uint32_t scheme = 0;

int test(){
    return 0;
}

void initBoard(uint8_t board[SIZE][SIZE]){
    ;
}
bool moveLeft(uint8_t board[SIZE][SIZE]){
    printf("moveleft\n");
    return true;
}

bool moveRight(uint8_t board[SIZE][SIZE]){
    printf("moveright\n");
    return true;
}

bool moveUp(uint8_t board[SIZE][SIZE]){
    printf("moveup\n");
    return true;
}

bool moveDown(uint8_t board[SIZE][SIZE]){
    printf("movedown\n");
    return true;
}

void drawBoard(uint8_t board[SIZE][SIZE]){
    ;
}

void setBufferedInput(bool enable){
    static bool enabled = true;
    static struct termios old;
    struct termios new;

    if(enable && !enabled){
        //restore the terminal
        tcsetattr(STDIN_FILENO,TCSANOW,&old);

        enabled = true;

    }else if(!enable && enabled){
        //get terminal attr
        if(tcgetattr(STDIN_FILENO,&new)==-1){
            printf("tcgetattr Error!\n");
            exit(-1);
        }
        //resotre now terminal attr
        old = new;
        //set c_cflag don't show cursor(光标)  attaction to order
        new.c_lflag &=(~ICANON & ~ECHO);

        tcsetattr(STDIN_FILENO,TCSANOW,&new);

        enable = false;
    }

}

void addRandom(uint8_t board[SIZE][SIZE]){
    ;
}

void drawRandom(uint8_t board[SIZE][SIZE]){
    ;
}

bool gameEnded(uint8_t board[SIZE][SIZE]){
    return false;
}
void signal_callback_handler(int signum){
    printf("        TERMINATED          \n");
    setBufferedInput(true);//恢复终端初始配置，显示输入字符
    printf("\033[?25h\033[m");//显示光标
    exit(signum);
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

    printf("\033[?25l\033[2J");//隐藏光标 & 清屏

    // register signal handler for when ctrl-c is pressed!
    signal(SIGINT,signal_callback_handler);
    
    initBoard(board);

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
				success = moveRight(board); break;
			case 119:	// 'w' key
			case 107:	// 'k' key
			case 65:	// up arrow
				success = moveUp(board);    break;
			case 115:	// 's' key
			case 106:	// 'j' key
			case 66:	// down arrow
				success = moveDown(board);  break;
			default: success = false;
        }
        if(success){
            drawBoard(board);

            usleep(150000);
            addRandom(board);
            drawRandom(board);
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
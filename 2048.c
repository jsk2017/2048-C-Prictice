#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<termios.h>

#define SIZE 4

uint32_t score = 0;
uint32_t scheme = 0;

int test(){
    return 0;
}


void printfBoard(uint8_t board[SIZE][SIZE]){
    uint8_t x,y;
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            printf("%d\t",board[x][y]);
        }
    }
}

//这个函数没有修改！
void getColor(uint8_t value,char *color,size_t length){
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
	snprintf(color,length,"\033[38;5;%d;48;5;%dm",*foreground,*background);//设置terminal 颜色
} 

void drawBoard(uint8_t board[SIZE][SIZE]){

    uint8_t x,y;
    char reset[] = "\033[m";//关闭所有属性 \033[0m 0 可以省略
    char color[40];
    char c;
    printf("\033[H");//光标复位

	printf("2048.c %17d pts\n\n",score);

    for(y=0;y<SIZE;y++){
        //每个小块都是 3 * 7
        for(x=0;x<SIZE;x++){
            getColor(board[x][y],color,40);
            printf("%s",color);
            printf("       ");//代表某一个块
			printf("%s",reset);//复位颜色 避免对之后的颜色造成影响
        }
        printf("\n");
        for(x=0;x<SIZE;x++){
            getColor(board[x][y],color,40);
            printf("%s",color);
            //打印文字 块
            if(board[x][y]!=0){
                char s[8];
                snprintf(s,8,"%u",(uint32_t)1<<board[x][y]);
                uint8_t t = 7 - strlen(s);
                printf("%*s%s%*s",t-t/2,"",s,t/2,"");
            }else{
                printf("   ·   ");
            }
            printf("%s",reset);
        }
        printf("\n");

        for(x=0;x<SIZE;x++){
            getColor(board[x][y],color,40);
            printf("%s",color);
            printf("       ");//代表某一个块
			printf("%s",reset);//复位颜色 避免对之后的颜色造成影响
        }
        printf("\n");
    }
    printf("\n");
	printf("        ←,↑,→,↓ or q        \n");
	printf("\033[A");//光标上移 一行
    
}

void addRandom(uint8_t board[SIZE][SIZE]){
    static bool initialized = false;
    uint8_t x,y;
    uint8_t r,len = 0;
    uint8_t n,list[SIZE*SIZE][2];

    if(!initialized){
        srand(time(NULL));
        initialized = true;
    }

    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            if(board[x][y]==0){
                //Get empty positon to list[0] list[1]
                list[len][0]=x;
                list[len][1]=y;
                len++;
            }
        }
    }
    if(len>0){
        r = rand()%len;
        //Random positon(x,y)
        x = list[r][0];
        y = list[r][1];
        n = (rand()%10)/9+1;//What's result ? 1 OR 2
        board[x][y]=n;
    }

}

void initBoard(uint8_t board[SIZE][SIZE]){
    int i,j;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            board[i][j]=0;
        }
    }

    addRandom(board);
    addRandom(board);

    drawBoard(board);
    score = 0;
}

//翻转
void rotateBoard(uint8_t board[SIZE][SIZE]){
    uint8_t x,y,tmp;
    uint8_t n = SIZE;
    for(x=0;x<n/2;x++){
        for(y=x;y<n-x-1;y++){
            tmp = board[x][y];
            board[x][y] = board[y][n-x-1];
            board[y][n-x-1]=board[n-x-1][n-y-1];
            board[n-x-1][n-y-1]=board[n-y-1][x];
            board[n-y-1][x]=tmp;
        }
    }
}

uint8_t findTarget(uint8_t array[SIZE],uint8_t x,uint8_t stop){
    uint8_t t;
    //begin direct return
    if(x==0){
        return x;
    }
    for(t=x-1;t>=0;t--){
        if(array[t]!=0){
            if(array[t]!=array[x]){
                return t+1;
            }
            return t;
        }else{
            if(t==stop) return  t;
        }
    }
    return x;

}
//移动 或者 合并 move or merge
bool slideArray(uint8_t array[SIZE]){
    bool success = false;
    uint8_t x,t,stop = 0;
    for(x=0;x<SIZE;x++){
        if(array[x]!=0){
            //找到需要移动到的位置，以及是否需要进行合并
            t = findTarget(array,x,stop);
            //如果目标位置和起始位置不同进行 move or merge
            if(t!=x){
                //判断是否进行合并
                if(array[t]==0){
                    array[t]=array[x];
                }else if(array[t]==array[x]){
                    //increase power of two
                    array[t]++;//2的n次幂
                    //increast score    (uint32_t)1<<array[t] == 2**array[t]    
                    score +=(uint32_t)1<<array[t];
                    
                    stop = t+1;
                }
                array[x]=0;
                success = true;
            }
        }
    }
    return success;

}

bool moveUp(uint8_t board[SIZE][SIZE]){
    uint8_t x;
    bool success = false;
    for(x=0;x<SIZE;x++){
        success |= slideArray(board[x]);
    }

    // printfBoard(board);
    return success;
}


bool moveLeft(uint8_t board[SIZE][SIZE]){
    bool success;
	rotateBoard(board);
	success = moveUp(board);
	rotateBoard(board);
	rotateBoard(board);
	rotateBoard(board);
    // printf("moveleft\n");
	return success;
}

bool moveRight(uint8_t board[SIZE][SIZE]){
    bool success;
	rotateBoard(board);
	rotateBoard(board);
	rotateBoard(board);
	success = moveUp(board);
	rotateBoard(board);
    // printf("moveright\n");
	return success;
}

bool moveDown(uint8_t board[SIZE][SIZE]){
    // printf("movedown\n");
    bool success;
	rotateBoard(board);
	rotateBoard(board);
	success = moveUp(board);
	rotateBoard(board);
	rotateBoard(board);
	return success;
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

uint8_t countEmpty(uint8_t board[SIZE][SIZE]){
    uint8_t x,y,count=0;
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            if(board[x][y]==0) count++;
        }
    }
    return count;
}

bool findPairDown(uint8_t board[SIZE][SIZE]){
    bool success=false;
    uint8_t x,y;
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE-1;y++){
            if(board[x][y]==board[x][y+1]) return true;
        }
    }

    return success;
}

bool gameEnded(uint8_t board[SIZE][SIZE]){
    bool ended = true;
    if(countEmpty(board)>0) return false;

    if(findPairDown(board)) return false;
    rotateBoard(board);
    if(findPairDown(board)) ended = false;
    rotateBoard(board);
    rotateBoard(board);
    rotateBoard(board);

    return ended;
}
void signal_callback_handler(int signum){
    printf("        TERMINATED          \n");
    setBufferedInput(true);//恢复终端初始配置，显示输入字符
    printf("\033[?25h\033[m");//显示光标
    exit(signum);
}

void printAuthorColorful(int color){

    char * line1 = "__________             ._____________\n";             
    char * line2 = "\\______   \\_____     __| _/\\______   \\ ___________\n";
    char * line3 = " |    |  _/\\__  \\   / __ |  |       _// __ \\_  __ \\\n";
    char * line4 = " |    |   \\ / __ \\_/ /_/ |  |    |   \\  ___/|  | \\/\n";
    char * line5 = " |______  /(____  /\\____ |  |____|_  /\\___  >__|\n";   
    char * line6 = "        \\/      \\/      \\/         \\/     \\/       \n";

    // printf("\033[2J\n");
    printf("\033[%dm%s",color,line1);
    printf("\033[%dm%s",color,line2);
    printf("\033[%dm%s",color,line3);
    printf("\033[%dm%s",color,line4);
    printf("\033[%dm%s",color,line5);
    printf("\033[%dm%s",color,line6);
    printf("\033[0m");//关闭所有设置的属性
    printf("\n\n");
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
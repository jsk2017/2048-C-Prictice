#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>

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

int getTransposeMatrix(uint8_t * matrix,uint8_t row,uint8_t column,uint8_t ** transposeMatrix){
   uint8_t i,j;

   for(i=0;i<row;++i){
        for(j=0;j<column;++j){
            transposeMatrix[j][i]=matrix[row*i+j];
        }
   }

   return 0;
}

int getTransposeMatrix_oneArray(uint8_t * matrix,uint8_t row,uint8_t column,uint8_t * transposeMatrix){
   uint8_t i,j;

   for(i=0;i<row;++i){
        for(j=0;j<column;++j){
            transposeMatrix[column*j+i]=matrix[row*i+j];
        }
   }

   return 0;
}

//C = A*B   要求：A的列数 = B的行数  ==> C的行数 = A的行数；C的列数 = B的列数
void matrixMul(int **A, int **B, int **C, int rowA, int columnB, int columnA){

    for (int i=0;i<rowA;i++){
        for (int j=0; j<columnB;j++){
            C[i][j] = 0;
            for (int k=0;k<columnA;k++){
                C[i][j]+=A[i][k]*B[k][j];
            }
         }
     }
}

void matrixMul_oneArray(uint8_t *A, uint8_t *B, uint32_t *C, uint8_t rowA, uint8_t columnB, uint8_t columnA){
    
    for (uint8_t i=0;i<rowA;i++){
        for (uint8_t j=0; j<columnB;j++){
            C[rowA*i+j] = 0;
            for (uint8_t k=0;k<columnA;k++){
                C[rowA*i+j]+=A[rowA*i+k]*B[columnA*k+j];
            }
         }
     }
}

int main(int argc,char ** argv){
    uint8_t i,j;
    char *hexKey;
    char key[9];
    uint8_t ** transposeMatrix = NULL;
    uint8_t * example = NULL;
    uint32_t * resultMatrix = NULL;
    uint8_t keyLen = (uint8_t)getStr(key,8);
    hexKey = (char *)malloc(keyLen*2);
    uint8_t board[4][4] = {
        {1 ,2 ,3 ,4 },
        {5 ,6 ,7 ,8 },
        {9 ,10,11,12},
        {13,14,15,16}
    };
    str2hex(key,hexKey,keyLen);

    // for(i=0;i<4;i++){
    //     for(j=0;j<4;j++){
    //         printf("%d\t",board[i][j]);
    //     }
    // }

    printf("\n");

    for(i=0;i<16;i++){
        printf("0x%02x\t",hexKey[i]);
    }

    transposeMatrix = (uint8_t **)malloc(sizeof(uint8_t *)*4);

    for(i=0;i<4;i++){
        transposeMatrix[i] = (uint8_t *)malloc(sizeof(uint8_t)*4);
    }
    //我们可以用一维数组模拟 二维数组
    example = (uint8_t *)malloc(sizeof(uint8_t *)*4*4);

    getTransposeMatrix((uint8_t *)hexKey,4,4,transposeMatrix);//注意 uint8_t * []  和 uint8_t ** 是不同的
    getTransposeMatrix_oneArray((uint8_t *)hexKey,4,4,example);
    printf("\n");
    printf("example!\n");
    // for(i=0;i<4;i++){
    //     for(j=0;j<4;j++){
    //         printf("%u",transposeMatrix[i][j]);
    //     }
    // }
    // printf("\n");

    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            printf("%d\t",example[4*i+j]);
        }
    }
    //A*A' hexKey * example
    resultMatrix  = (uint32_t *)malloc(sizeof(uint32_t)*4*4);
    uint8_t rev_matrix[16] = {
        1,0,0,0,
        2,1,0,0,
        3,2,1,0,
        9,3,2,1
    };
    
    matrixMul_oneArray((uint8_t *)rev_matrix,example,resultMatrix,4,4,4);
    // matrixMul_oneArray((uint8_t *)reverse_matrix,example,resultMatrix,4,4,4);

    //Print matrix mul result
    printf("result\n");
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            printf("%d\t",resultMatrix[4*i+j]);
        }
    }
    

    return 0;
}
#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<stdlib.h>
#include <stdio.h>
#include <string.h>


void rc4_init(uint8_t *s, uint8_t *key, uint16_t Len) //初始化函数
{
    int i =0, j = 0;
    char k[256] = {0};
    uint8_t tmp = 0;
    for (i=0;i<256;i++) {
        s[i] = i;
        k[i] = key[i%Len];
    }
    for (i=0; i<256; i++) {
        j=(j+s[i]+k[i])%256;
        tmp = s[i];
        s[i] = s[j]; //交换s[i]和s[j]
        s[j] = tmp;
    }
 }

void rc4_crypt(uint8_t *s, uint8_t *Data, uint16_t Len) //加解密
{
    int i = 0, j = 0, t = 0;
    uint16_t k = 0;
    uint8_t tmp;
    for(k=0;k<Len;k++) {
        i=(i+1)%256;
        j=(j+s[i])%256;
        tmp = s[i];
        s[i] = s[j]; //交换s[x]和s[y]
        s[j] = tmp;
        t=(s[i]+s[j])%256;
        Data[k] ^= s[t];
     }
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

void Hex2Str( const char *sSrc,  char *sDest, int nSrcLen )  
{  
    int  i;  
    char szTmp[3];  
  
    for( i = 0; i < nSrcLen; i++ )  
    {  
        sprintf( szTmp, "%02X", (unsigned char) sSrc[i] );  
        memcpy( &sDest[i * 2], szTmp, 2 );  
    }  
    return ;  
}  

int main()
{ 
    uint8_t s[256] = {0}; //S-box
    char key[256] = {"aY2oPew9"};
    char pData[512] = "flag{MaTr1x_0s_&R4_2os8_s0_f4n}";
    uint16_t len = strlen(pData);
    
    rc4_init(s,(uint8_t *)key,strlen(key)); //已经完成了初始化

    rc4_crypt(s,(uint8_t *)pData,len);//加密

    char dest[256]={0};
    //str2hex

    // str2hex((char *)pData,dest,strlen(pData));

    //hex2str
    Hex2Str( pData,dest,strlen(pData) );

    printf("encrypt  : %s\n", dest);
    //enc = 6552C0671FFEF2607055E0EBBD8C559016805D2EA47DF1869ACE655ACF769D

    //enc str2hex

    char enc[256]  = {0x65,0x52,0xC0,0x67,0x1F,0xFE,0xF2,0x60,0x70,0x55,0xE0,0xEB,0xBD,0x8C,0x55,0x90,0x16,0x80,0x5D,0x2E,0xA4,0x7D,0xF1,0x86,0x9A,0xCE,0x65,0x5A,0xCF,0x76,0x9D};
    rc4_init(s,(uint8_t *)key, strlen(key)); //初始化密钥
    rc4_crypt(s,(uint8_t *)enc,len);//解密
    //
    printf("decrypt  : %s\n",enc);
    return 0;
}
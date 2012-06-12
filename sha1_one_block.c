/*
 *Accept data must bu fixed length
 *
 *
 *
 *
 * */

#include <stdio.h>

#define rol(x,n) ( ((x) << (n)) | ((x) >> (32-(n))) )

#define dprintf 

#define TOTAL_DATA_LENGTH 80
#define INPUT_DATA_LENGTH 1
#define KEY_LENGTH 8

typedef struct {
    unsigned int  h0,h1,h2,h3,h4;
    unsigned int  nblocks;
    unsigned int buf[TOTAL_DATA_LENGTH];
    int  count;
} SHA1_CONTEXT;


unsigned int key[KEY_LENGTH]={'1','2','3','4','5','6','7','8'};

void sha1_init( SHA1_CONTEXT *hd )
{
    hd->h0 = 0x67452301;
    hd->h1 = 0xefcdab89;
    hd->h2 = 0x98badcfe;
    hd->h3 = 0x10325476;
    hd->h4 = 0xc3d2e1f0;
    hd->nblocks = 0;
    hd->count = 0;
}
void sha1sum(SHA1_CONTEXT *hd)
{
    int i = 0;
    unsigned int a=hd->h0;
    unsigned int b=hd->h1;
    unsigned int c=hd->h2;
    unsigned int d=hd->h3;
    unsigned int e=hd->h4;
    unsigned int f=0;
    unsigned int k=0;
    unsigned int temp = 0;
    for(i=0; i< TOTAL_DATA_LENGTH; i++)
    {
        if(i >=0 && i <=19)
        {
            f = (b&c)|((!b)&d);
            k = 0x5A827999;
        }
        if(i >=20 && i <=39)
        {
            f = b ^ c ^ d;
            k = 0x6ED9EBA1;
        }
        if(i >=40 && i <=59)
        {
            f = (b & c) | (b & d) | (c & d);
            k = 0x8F1BBCDC;
        }
        if(i >=60 && i <=79)
        {
            f = b ^ c ^ d;
            k = 0xCA62C1D6;
        }
        temp = (rol(a,5)) + f + e + k + hd->buf[i];
        e = d;
        d = c;
        c = rol(b,30);
        b = a;
        a = temp;
    }
    printf("0x%08x\n",hd->h0+a);
    printf("0x%08x\n",hd->h1+b);
    printf("0x%08x\n",hd->h2+c);
    printf("0x%08x\n",hd->h3+d);
    printf("0x%08x\n",hd->h4+e);
}

void create_sha1_buf(SHA1_CONTEXT *hd, unsigned int *data,unsigned int *key)
{
    int i = 0;//data_length;
    for(i = 0; i < INPUT_DATA_LENGTH; i++)
        hd->buf[i] = *data++;
    for(i = 0; i < KEY_LENGTH; i++)
        hd->buf[i+INPUT_DATA_LENGTH] = key[i];
    hd->buf[INPUT_DATA_LENGTH+KEY_LENGTH] = 0x80000000;
    hd->buf[INPUT_DATA_LENGTH+KEY_LENGTH+1] = 0x00000000;
    hd->buf[INPUT_DATA_LENGTH+KEY_LENGTH+2] = 0x00000000;
    hd->buf[INPUT_DATA_LENGTH+KEY_LENGTH+3] = (INPUT_DATA_LENGTH+KEY_LENGTH)*32;
    unsigned int temp = 0;
    //cal 16-79 buff
    for(i = INPUT_DATA_LENGTH+KEY_LENGTH+4; i < TOTAL_DATA_LENGTH; i++)
    {
        temp = (hd->buf[i-3] ^ hd->buf[i-8] ^ hd->buf[i-14] ^ hd->buf[i-16]);
        hd->buf[i] = rol(temp,1);
    }

    for(i=0; i< TOTAL_DATA_LENGTH; i++)
    {
        dprintf("0x%08x   ",hd->buf[i]);
        if((i+1)%4 == 0)
            dprintf("\n");
    }
    dprintf("\n");
}

int main(int argc, char **argv)
{
    if(argc != INPUT_DATA_LENGTH+1){
        printf("Useage: sha1_one_blck data1 \n");
        return -1;
    }
    unsigned int input_data[INPUT_DATA_LENGTH];// = atoi(argv[1]);
    int i = 0;
    for(i = 0 ; i < INPUT_DATA_LENGTH; i++)
        input_data[i] = atoi(argv[i+1]);
    dprintf("sizeof unsigned int is %d sizeof long is %d sizeof long long is %d\n",sizeof(int),sizeof(long),sizeof(long long));
    for(i = 0 ; i < INPUT_DATA_LENGTH; i++)
        dprintf("%8d --",input_data[i]);
    dprintf("\n");
    SHA1_CONTEXT hd;
    sha1_init(&hd);
    create_sha1_buf(&hd,&input_data[0],&key[0]);
    sha1sum(&hd);
    return 0;
}


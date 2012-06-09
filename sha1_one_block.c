/*
 *Accept data must bu fixed length
 *
 *
 *
 *
 * */

#include <stdio.h>

#define TOTAL_DATA_LENGTH 16
#define INPUT_DATA_LENGTH 4
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
    hd->buf[INPUT_DATA_LENGTH+KEY_LENGTH+3] = (4+8)*32;
    for(i=0; i< TOTAL_DATA_LENGTH; i++)
    {
        printf("0x%08x   ",hd->buf[i]);
        if((i+1)%4 == 0)
            printf("\n");
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    if(argc != 5){
        printf("Useage: sha1_one_blck data1 date2 data3 data4 \n");
        return -1;
    }
    unsigned int input_data[4];// = atoi(argv[1]);
    int i = 0;
    for(i = 1 ; i < 5; i++)
        input_data[i-1] = atoi(argv[i]);
    printf("sizeof unsigned int is %d sizeof long is %d sizeof long long is %d\n",sizeof(int),sizeof(long),sizeof(long long));
    for(i = 0 ; i < 4; i++)
        printf("%8d --",input_data[i]);
    printf("\n");
    SHA1_CONTEXT hd;
    sha1_init(&hd);
    create_sha1_buf(&hd,&input_data[0],&key[0]);
    return 1;
}


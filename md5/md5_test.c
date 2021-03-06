#include <stdio.h>
#include <string.h>
#include "md5.h"

void calc_md5(unsigned char *input, unsigned int inputlen, char *check_sum)
{
  MD5_CTX md5;
  int i;
  unsigned char digest[16];

  MD5Init(&md5);

  for (i = 0; i < inputlen / 1024; i++) {
    MD5Update(&md5, input, 1024);
    input += 1024;
  }

  if ((inputlen % 1024) > 0)
    MD5Update(&md5, input, (inputlen % 1024));

  MD5Final(&md5, digest);

  for (i = 0; i < 16; i++)
    sprintf(&check_sum[i*2], "%02x", digest[i]);
}

int main(int argc, char const *argv[])
{
    if(argc<2){
      printf("Usage:\n");
      printf("./MD5 path/to/file\n");
      return -1;
    }

    FILE *file = fopen(argv[1],"r");

    fseek(file,0,SEEK_END);
    
    int len = ftell(file);

    unsigned char buff[len];
    memset(buff,0,len);

    fseek(file,0,SEEK_SET);

    int read_len = fread(buff,1,len,file);
    if(read_len<0){
      printf("read file error\n");
    }

    char b_md5[32] = {0};

    calc_md5(buff,len,b_md5);

    /* print the MD5 value */
    printf("\n");
    printf("The MD5 value of %s is: ",argv[1]);
    for (int i=0;i<32;i++){
      printf("%c",b_md5[i]);
    }
    printf("\n\n");

    return 0;
}

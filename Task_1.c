#include <stdio.h>
#include <stdbool.h>
#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "windows.h"
#include <io.h>
#include <fcntl.h>
#define FILENAME "c:\\temp\\arbitrarydata.txt"
#define BIN_FILENAME "c:\\temp\\outfile.bin"
#define CHUNK 200

void writeToFile(char *buf, size_t len) {
  FILE *fp = NULL;
  fp = fopen(FILENAME,"a+");
  if(!fp) {
    printf("Unable to open file:%s\n",FILENAME);
    return;
  }
  if(buf && len && fp) {
   // printf("Value: %s\n",buf);
    fprintf(fp,"%.*s",len, buf);
    fflush(fp);
    fclose(fp);
  }
  return;
}

char *readinput(int *lent) {
   char* input = NULL;
   char tempbuf[CHUNK] ;
   size_t inputlen = 0, templen = 0;
   do {
       fgets(tempbuf, CHUNK, stdin);
       templen = strlen(tempbuf);
       input = realloc(input, inputlen+templen+1);
       strcpy(input+inputlen, tempbuf);
       inputlen += templen;
    } while (templen==CHUNK-1 && tempbuf[CHUNK-2]!='\n');
    *lent = inputlen;
    return input;
}


void readbinaryinput() {
    char rbuf[CHUNK * 20];
    char *outfilename = BIN_FILENAME;
    size_t r;
    
    freopen(NULL, "rb", stdin);
    _setmode(_fileno(stdin), _O_BINARY); //Setting the stdin mode to binary

    FILE *f = fopen(outfilename, "w+b"); // Opening the file in binary mode 
    if (f == NULL) {
        printf("unable to open %s\n", outfilename);
        return;
    }
   while(1) {
        read_data = fread(rbuf, 1, sizeof(rbuf), stdin);
        if (read_data > 0)    {
            size_t writen_data;
            for (size_t nleft =read_data; nleft > 0; )         {
                writen_data = fwrite(rbuf, 1, nleft, f);
                if (writen_data == 0)       {
                    printf("error: unable to write %d bytes to %s\n", nleft, outfilename);
                    return;
                }
                nleft -= writen_data;
                fflush(f);
            }
        }
    }
   _setmode(_fileno(stdin), _O_TEXT); //Change the mode back to Text
    return;
}
int main()
{
    int n = 0,i;
    printf("Program to read arbitrary data and write to a file\n");
    while(1) {
       printf("\nEnter the number of input you want to enter: ");
       scanf("%d",&n);
       for(i = 1; i<= n; i++) {
           printf("Do you wanna enter data which is binary/image/exe: (y/n)");
           scanf("%c", option);
           if(option == 'y') { 
             readbinaryinput();
             continue;
           } else if(option =='n') {
              size_t len = 10;
              char *buf = readinput(&len);
              if( buf && len) {
                 writeToFile(buf,len);
              }
           } else {
             printf("Invalid Option:%c\n",option);
             i--;
           }
       }
    }
    return 0;
}

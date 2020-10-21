#include <stdio.h>
#include <stdbool.h>
#define FILENAME "arbitrarydata.txt"
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
int main()
{
    int n = 0,i;
    printf("Program to read arbitrary data and write to a file\n");
    while(1) {
       printf("\nEnter the number of input you want to enter: ");
       scanf("%d",&n);
       for(i = 1; i<= n; i++) {
           printf("\nEnter your %dth data: ",i);
           size_t len = 10;
           char *buf = readinput(&len);
           if( buf && len) {
               writeToFile(buf,len);
           }
       }
    }
    return 0;
}

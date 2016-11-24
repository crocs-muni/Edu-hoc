#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common.h"
int main (void)
{
  FILE *nodes;
  FILE *check;
  FILE *inputFiles[MAX_NODES];
  int i = 0;
  nodes = fopen("motePaths.txt", "r");
  check = fopen("check.txt", "w");
  char filename[256];
  while (fgets (filename, 256, nodes)) {
      if(strlen(filename) >2 && filename[0] != '\n'  && filename[0] != '#'){
         //printf(filename);
         char subbuff[strlen(filename)-4];
         strncpy(subbuff,filename+5,strlen(filename)-3);
         subbuff[strlen(filename)-6] = '\0';
         //printf(subbuff);
         inputFiles[i] = fopen(subbuff, "w");
         //printf(subbuff);
         i++;
      }
  }
  fclose(nodes);
  char c=getchar();
  srand(c);
  long counter = 0;
  FILE *f;
  f = fopen("messageText.txt", "r");
  char buf[MAX_MESSAGE_LENGTH + 2];
  while (fgets (buf, sizeof(buf)-2, f)) {
      if(strlen(buf) > 15 && buf[0] != '\0'){
        if(buf[strlen(buf)-1] == '\n' ){
          fprintf( inputFiles[counter % i],"#%ld%ld#%s",counter,rand()%10, buf);
          fprintf( check,"#%ld#%ld#%s#",counter,rand()%100000, buf);
        } else {
          fprintf( inputFiles[counter % i],"#%ld%ld#%s\n",counter,rand()%10,buf);
          fprintf( check,"#%ld%ld#%s#\n",counter,rand()%10,buf);
        }
         counter++;
      }
  }

  fclose(f);
  fclose(check);
  for(int j = 0; j < i; j++){
      fclose(inputFiles[j]);
  }

  return 0;
}

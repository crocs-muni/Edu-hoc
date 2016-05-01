#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common.h"
int main (void)
{
  FILE *nodes;
  FILE *inputFiles[MAX_NODES];
  int i = 0;
  nodes = fopen("motePaths.txt", "r");
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


  long counter = 0;
  FILE *f;
  f = fopen("messageText.txt", "r");
  char buf[MAX_MESSAGE_LENGTH + 2 -10];
  while (fgets (buf, sizeof(buf), f)) {
      if(strlen(buf) > 10 && buf[0] != '\0'){
        if(buf[strlen(buf)-1] == '\n'){
          fprintf( inputFiles[counter % i],"%s", buf);
        } else {
          fprintf( inputFiles[counter % i],"%s\n", buf);
        }
         counter++;
      }
  }

  fclose(f);

  for(int j = 0; j < i; j++){
      fclose(inputFiles[j]);
  }

  return 0;
}

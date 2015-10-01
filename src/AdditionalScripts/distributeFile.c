#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main (void)
{
  FILE *nodes;
  FILE *inputFiles[26];
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
  if (ferror(stdin)) {
    fprintf(stderr,"Oops, error reading stdin\n");
    abort();
  }
  fclose(nodes);

  
  long counter = 0;
  FILE *f;
  f = fopen("messageText.txt", "r");
  char buf[256];
  while (fgets (buf, sizeof(buf), f)) {
      if(strlen(buf) >2 && buf[0] != '\n'){
         
         fprintf( inputFiles[counter % i],"line: %s", buf);
         counter++;
      }
  }
  if (ferror(stdin)) {
    fprintf(stderr,"Oops, error reading stdin\n");
    abort();
  }
  
  fclose(f);
  
  for(int j = 0; j < i; j++){
      fclose(inputFiles[j]);
  }
  
  return 0;
}
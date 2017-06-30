#include <stdio.h>

int UCO_LEN = 32;
long uco[] = {
  396515,448419,448426,448413,448414,448427,448428,410158,448420,448387,396278,
  448389,454317,448384,448429,448382,448383,394036,448385,448381,448390,448415,
  448421,448423,448411,453033,448291,448417,409910,448418,448416,396555
};
char* secret[] = {
  "andrei","apeman","ahchoo","airbus","abdias","averno","aganus","annals","aghast",
  "arpent","aliner","accent","anglic","adabel","aerial","almost","aornum","ahmadi",
  "artist","agonal","ararat","amiens","alayne","andrsy","amadan","awaken","assiut",
  "aurist","avalon","asleep","apollo","afflux"
};

int main(){
  for(int i = 0; i < UCO_LEN; i++){
      printf("%ld - %s\n", uco[i], secret[i]);
  }
  return 0;
}

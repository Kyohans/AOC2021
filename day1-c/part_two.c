#include <stdio.h>
#include <stdlib.h>

#define BUFFERSIZE 100
#define WINDOWSIZE 3

int main(void) {
  char buffer[BUFFERSIZE];
  int window[WINDOWSIZE + 1];

  for(int i = 0; i < 3; ++i) {
    fgets(buffer, BUFFERSIZE, stdin);
    window[i] = atoi(buffer);
  }

  int ans = 0;
  while(fgets(buffer, BUFFERSIZE, stdin)) {
    window[3] = atoi(buffer);

    if(window[0] + window[1] + window[2] < window[1] + window[2] + window[3]) ans++;
    window[0] = window[1];
    window[1] = window[2];
    window[2] = window[3];
  }
  
  printf("%d\n", ans);
  return 0;
}

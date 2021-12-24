#include <stdio.h>
#include <stdlib.h>

#define BUFFERSIZE 100

int main(int argc, char *argv[]) {
  int prev, current, count = 0;
  char buffer[BUFFERSIZE];

  prev = atoi(fgets(buffer, BUFFERSIZE, stdin));
  while(fgets(buffer, BUFFERSIZE, stdin)) {
    current = atoi(buffer);
    if(current > prev) count++;

    prev = current;
  }

  printf("%d", count);
  return 0;
}

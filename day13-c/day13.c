#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 255

#if 0
#define IFILE "input"
#else
#define IFILE "example"
#endif

int max(int a, int b) {
  if(a >= b) {
    return a;
  }

  return b;
}

void part_one() {
  FILE *getsize;
  getsize = fopen(IFILE, "r");

  char line[MAXSIZE];
  char *p = NULL;

  int maxrows = INT_MIN, maxcols = INT_MIN;
  while(fgets(line, MAXSIZE, getsize)) {
    if(line[0] != 'f') {
      p = strtok(line, ",");
      while(p != NULL) {
        maxrows = max(maxrows, atoi(p));
        p = strtok(NULL, "");
        maxcols = max(maxcols, atoi(p));
        p = strtok(NULL, "");
      } 
    } else {
      break;
    }
  }
  fclose(getsize);


  FILE *fp;
  fp = fopen(IFILE, "r");

  char grid[maxrows][maxcols];
  memset(grid, '.', sizeof grid);

  int x, y;
  while(fgets(line, MAXSIZE, fp)) {
    if(line[0] != 'f') {
      p = strtok(line, ",");
      while(p != NULL) {
        x = atoi(p);
        p = strtok(NULL, "");
        y = atoi(p);
        p = strtok(NULL, "");

        grid[x][y] = '#';
      }
    }
  }

  for(int x = 0; x < maxrows - 1; ++x) {
    for(int y = 0; y < maxcols - 1; ++y) {
      printf("%c ", grid[x][y]);
    }
    printf("\n");
  }

  printf("%d, %d\n", maxrows, maxcols);
}

int main(void) {
  part_one();
}

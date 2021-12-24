#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXSPACES 10
#define DIESIZE 100
#define BUFFERSIZE 35

void part_one(char * filename) {
  int p1_score = 0, p2_score = 0;
  int p1_pos = 0, p2_pos = 0;
  int die_rolls = 0;

  FILE * f;
  f = fopen(filename, "r");
  if(f == NULL) {
    printf("File not found!\n");
    abort();
  }

  char * buffer = (char *) malloc(sizeof(char) * BUFFERSIZE);
  while(fgets(buffer, BUFFERSIZE, f)) {
    if(!p1_pos) p1_pos = (int) buffer[28] - '0';
    else p2_pos = (int) buffer[28] - '0';
  }
  fclose(f);


  bool p1_turn = true;
  int i = 1, move = 0, upper = 0;
  while(p1_score < 1000 && p2_score < 1000) {
    move = 0;
    upper = i + 3;
    for(int j = i; j < upper; j++) {
      if(i > DIESIZE) i = 1;

      move += i;
      i++;
      die_rolls++;
    }

    if(p1_turn) {
      if(p1_pos + move > MAXSPACES) p1_pos = (p1_pos + move) % MAXSPACES;
      else p1_pos = p1_pos + move;

      if(p1_pos == 0) p1_pos = 10;

      p1_score += p1_pos;
      p1_turn = false;
    } else {
      if(p2_pos + move > MAXSPACES) p2_pos = (p2_pos + move) % MAXSPACES;
      else p2_pos = p2_pos + move;

      if(p2_pos == 0) p2_pos = 10;

      p2_score += p2_pos;
      p1_turn = true;
    }
  }
   printf("Die Rolls: %d\nP1 Score: %d\nP2 Score: %d\n", die_rolls, p1_score, p2_score);

  if(p1_score < p2_score) printf("Answer: %d\n", p1_score * die_rolls);
  else printf("Answer %d\n\n", p2_score * die_rolls);
}

int p1, p2;
int * p1_uni = &p1, * p2_uni = &p2;
int roll_die(int, int, int, int);

void part_two(char * filename) {
  int p1_score = 0, p2_score = 0;
  int p1_pos = 0, p2_pos = 0;

  FILE * f;
  f = fopen(filename, "r");
  if(f == NULL) {
    printf("File not found!\n");
    abort();
  }

  char * buffer = (char *) malloc(sizeof(char) * BUFFERSIZE);
  while(fgets(buffer, BUFFERSIZE, f)) {
    if(!p1_pos) p1_pos = (int) buffer[28] - '0';
    else p2_pos = (int) buffer[28] - '0';
  }
  fclose(f);

  printf("Player One: %d\n", roll_die(p1_score, p1_pos, 1, 1) + roll_die(p1_score, p1_pos, 2, 1) + roll_die(p1_score, p1_pos, 3, 1));
  // printf("Player Two: %d\n", roll_die(p2_score, p2_pos, 1) + roll_die(p2_score, p2_pos, 2) + roll_die(p2_score, p2_pos, 3));
  printf("%d\n", *p1_uni);
}

int roll_die(int score, int pos, int roll, int p1_turn) {
  if(p1_turn) *(p1_uni++);
  else *(p2_uni++);

  if(score >= 21) return 0;

  int move = pos + roll;
  if(move > MAXSPACES) move = move % MAXSPACES;

  score += move;

  return roll_die(score, move, 1, p1_turn) + roll_die(score, move, 2, p1_turn) + roll_die(score, move, 3, p1_turn);
}

int main(void) {
  //part_one("example");
  //part_one("input");
  part_two("example");

  return 0;
}

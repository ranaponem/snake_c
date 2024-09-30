#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <stdlib.h>
#include <stdbool.h>
#include "constants.h"

#define INITIAL_SNAKE_SIZE GRID_SIZE / 10
#define MAX_SNAKE_SIZE MAP_W*MAP_H

typedef struct{
  int direction;
  block_t body[MAX_SNAKE_SIZE];
  int size;
} snake_t;

extern snake_t snake;
extern block_t apple;

void initSnake();
void moveSnake();
bool isEatingApple();
void sizeUpSnake();
bool isSnakeOOB();
bool isInsideSnake(block_t b, int start);
bool isSnakeCollided();
void newApple();

#endif

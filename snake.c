#include "snake.h"

snake_t snake;
block_t apple;

void initSnake(){
  snake.direction = LEFT;
  snake.size = INITIAL_SNAKE_SIZE;
  for(int i = 0 ; i < snake.size ; i++){
    snake.body[i].x = MAP_W / 2 + i;
    snake.body[i].y = MAP_H / 2;
  }
}

void moveSnake(){
  block_t temp1, temp2;

  temp1.x = snake.body[0].x;
  temp1.y = snake.body[0].y;

  switch(snake.direction){
    case UP:
      snake.body[0].y--;
      break;
    case DOWN:
      snake.body[0].y++;
      break;
    case LEFT:
      snake.body[0].x--;
      break;
    case RIGHT:
      snake.body[0].x++;
      break;
  }

  for(int i = 1 ; i < snake.size ; i++){
    temp2.x = snake.body[i].x;
    temp2.y = snake.body[i].y;
    snake.body[i].x = temp1.x;
    snake.body[i].y = temp1.y;
    temp1.x = temp2.x;
    temp1.y = temp2.y;
  }
}

bool isEatingApple(){
  return apple.x == snake.body[0].x && apple.y == snake.body[0].y;
}

void sizeUpSnake(){
  int s = snake.size++;
  snake.body[s].x = snake.body[s-1].x;
  snake.body[s].y = snake.body[s-1].y;
}

bool isSnakeOOB(){
  return snake.body[0].x >= MAP_W || snake.body[0].x < 0 ||
         snake.body[0].y >= MAP_H || snake.body[0].y < 0;
}

bool isInsideSnake(block_t b, int start){
  int i = start;
  for(i = start ; i < snake.size ; i++){
    if(b.x == snake.body[i].x && b.y == snake.body[i].y) return true;
  }

  return false;
}

bool isSnakeCollided(){
  return isInsideSnake(snake.body[0], 1);
}

void newApple(){
  do{
    apple.x = rand() % MAP_W;
    apple.y = rand() % MAP_H;
  } while(isInsideSnake(apple, 0));
}

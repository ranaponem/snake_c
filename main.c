#include "constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

// variable init
float tick_time = 0.3;
uint32_t last_time = 0;
SDL_Window* w;
SDL_Renderer* r;
uint8_t map[MAP_W][MAP_H] = {MAP_EMPTY};
bool running = true;
int curClickedDirection = LEFT;

typedef struct{
  int x, y;
  bool active;
} block_t;

typedef struct{
  int direction;
  block_t body[MAX_SNAKE_SIZE];
  int size;
} snake_t;

// snake and apple
block_t apple;
snake_t snake;

bool isInsideSnake(block_t b, int start){
  int i = start;
  while(snake.body[i].active == true){
    if(b.x == snake.body[i].x && b.y == snake.body[i].y) return true;
    i++;
  }

  return false;
}

void newApple(){
  do{
    apple.x = rand() % MAP_W;
    apple.y = rand() % MAP_H;
  } while(isInsideSnake(apple, 0));
}

void init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        fprintf(stderr, "E: Couldn't initialize SDL\n");

    w = SDL_CreateWindow(
        "Snake",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCR_W, SCR_H,
        SDL_WINDOW_SHOWN
    );

    if(w == 0)
        fprintf(stderr, "E: Couldn't initialize SDL window\n");

    r = SDL_CreateRenderer(w, -1, 0);

    // Rand time generation
    srand(time(NULL));

    //init snake
    {
      int i = 0;
      snake.direction = LEFT;
      snake.size = INITIAL_SNAKE_SIZE;
      for( ; i < INITIAL_SNAKE_SIZE ; i++){
        snake.body[i].active = true;
        snake.body[i].x = MAP_W / 2 + i;
        snake.body[i].y = MAP_H / 2;
      }

      for( ; i < MAX_SNAKE_SIZE ; i++){
        snake.body[i].active = false;
        snake.body[i].x = -1;
        snake.body[i].y = -1;
      }
    }


    //init apple
    apple.active = true;
    newApple();
}

void keydown(SDL_Event e){
    switch(e.key.keysym.sym){
        case SDLK_ESCAPE:
            tick_time = 0; 
            running = false;
            break;
    }
}

void keyup(SDL_Event e){
    switch(e.key.keysym.sym){
        case SDLK_UP:
        case SDLK_w:
        case SDLK_k:
            curClickedDirection = UP;
            break;
        case SDLK_RIGHT:
        case SDLK_d:
        case SDLK_l:
            curClickedDirection = RIGHT;
            break;
        case SDLK_DOWN:
        case SDLK_s:
        case SDLK_j:
             curClickedDirection = DOWN;
            break;
        case SDLK_LEFT:
        case SDLK_a:
        case SDLK_h:
            curClickedDirection = LEFT;
            break;
    }
}

void process_input(){
    SDL_Event e;

    while(SDL_PollEvent(&e)){
        switch(e.type){
            case SDL_KEYDOWN:
                keydown(e);
                break;
            case SDL_KEYUP:
                keyup(e);
                break;
            case SDL_QUIT:
                tick_time = 0;
                running = false;
                return;

            default:
                break;
        }
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
  snake.body[s].active = true;
}

bool isSnakeOOB(){
  return snake.body[0].x >= MAP_W || snake.body[0].x < 0 ||
         snake.body[0].y >= MAP_H || snake.body[0].y < 0;
}

bool isSnakeCollided(){
  return isInsideSnake(snake.body[0], 1);
}

void update(){
    uint32_t now = SDL_GetTicks();
    float deltaT = (now - last_time) / 1000.0f;

    if(deltaT >= tick_time){
      last_time = now;

      // CHANGE DIRECTION

      switch(curClickedDirection){
          case UP:
              if(snake.direction != DOWN) snake.direction = UP;
              break;
          case RIGHT:
              if(snake.direction != LEFT) snake.direction = RIGHT;
              break;
          case DOWN:
              if(snake.direction != UP) snake.direction = DOWN;
              break;
          case LEFT:
              if(snake.direction != RIGHT) snake.direction = LEFT;
              break;
      }

      // MOVE SNAKE

      moveSnake();

      // CHECK FOR APPLE
      
      if(isEatingApple()){
        newApple();
        sizeUpSnake();
      }

      // CHECK FOR GAMEOVER

      if(isSnakeOOB() || isSnakeCollided()){
        running = false;
      }

      // CHECK FOR WIN

      if(snake.size == MAX_SNAKE_SIZE){
        running = false;
      }
    }
}

void render(){
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    SDL_RenderClear(r);
    SDL_Rect renderRect;

    // RENDER GRID

    SDL_SetRenderDrawColor(r, 100, 100, 100, 255);
    for(int i = GRID_SIZE ; i < SCR_W ; i+= GRID_SIZE)
      SDL_RenderDrawLine(r, i, 0, i, SCR_H);

    for(int i = GRID_SIZE ; i < SCR_H ; i+= GRID_SIZE)
      SDL_RenderDrawLine(r, 0, i, SCR_W, i);

    // RENDER APPLE
    
    SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
    renderRect.x = apple.x * GRID_SIZE;
    renderRect.y = apple.y * GRID_SIZE;
    renderRect.w = GRID_SIZE;
    renderRect.h = GRID_SIZE;
    SDL_RenderFillRect(r, &renderRect);

    // RENDER SNAKE

    {
      int i = 0;

      while(snake.body[i].active){
        SDL_SetRenderDrawColor(r, 0, 255 - ((200/snake.size) * i), 0,255);
        renderRect.x = snake.body[i].x * GRID_SIZE;
        renderRect.y = snake.body[i].y * GRID_SIZE;
        SDL_RenderFillRect(r, &renderRect);
        i++;
      }
    }

    SDL_RenderPresent(r);
}

void quit(){
  SDL_DestroyRenderer(r);
  SDL_DestroyWindow(w);
  SDL_Quit();
}

int main(void){
  // window and renderer init
  init();

  while(running){
    process_input();
    update();
    render();
  }

  quit();

  return 0;
}

#include "constants.h"
#include "render.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <time.h>

// variable init
float tick_time = 0.1;
uint32_t last_time = 0;
SDL_Window* w;
SDL_Renderer* r;
uint8_t map[MAP_W][MAP_H] = {MAP_EMPTY};
bool running = true;
int curClickedDirection = LEFT;
int curGameState = GAME_MENU;

void init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        fprintf(stderr, "E: Couldn't initialize SDL\n");

    IMG_Init(IMG_INIT_PNG);

    w = SDL_CreateWindow(
        TITLE,
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

    initSnake();
    newApple();
}

void pressedSpace(){
  switch (curGameState) {
    case GAME_MENU:
      curGameState = GAME_PLAYING;
      break;
    case GAME_OVER:
      running = false;
      break;
    case GAME_PLAYING:
      curGameState = GAME_PAUSED;
      break;
    case GAME_PAUSED:
      curGameState = GAME_PLAYING;
      break;
    case GAME_WON:
      running = false;
      break;
  }
}

void keydown(SDL_Event e){
    switch(e.key.keysym.sym){
        case SDLK_ESCAPE:
            tick_time = 0; 
            running = false;
            break;
        case SDLK_SPACE:
            pressedSpace();
            break;
    }
}

void keyup(SDL_Event e){
  if(curGameState == GAME_PLAYING){
    switch(e.key.keysym.sym){
        case SDLK_UP:
        case SDLK_w:
            curClickedDirection = UP;
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            curClickedDirection = RIGHT;
            break;
        case SDLK_DOWN:
        case SDLK_s:
             curClickedDirection = DOWN;
            break;
        case SDLK_LEFT:
        case SDLK_a:
            curClickedDirection = LEFT;
            break;
    }
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

void update(){
  if(curGameState == GAME_PLAYING){
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
        curGameState = GAME_OVER;
      }

      // CHECK FOR WIN

      if(snake.size == MAX_SNAKE_SIZE){
        curGameState = GAME_WON;
      }
    }
  }
}

void render(){
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    SDL_RenderClear(r);

    switch(curGameState){
      case GAME_MENU:
        renderGameMenu(r);
        break;
      case GAME_PLAYING:
        renderGamePlaying(r);
        break;
      case GAME_OVER:
        renderGameOver(r);
        break;
      case GAME_PAUSED:
        renderGamePaused(r);
        break;
      case GAME_WON:
        renderGameWon(r);
        break;
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

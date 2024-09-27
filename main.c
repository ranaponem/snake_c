#include "constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

// variable init
int tick_time = 3000;
uint32_t last_time = 0;
SDL_Window* w;
SDL_Renderer* r;
uint8_t map[MAP_W][MAP_H] = {MAP_EMPTY};
bool running = true;

typedef struct{
  int x, y;
  bool active;
} block;

// snake and apple
block snake[MAX_SNAKE_SIZE];
block apple;

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

    //init apple
    apple.active = true;
    apple.x = rand() % MAP_W;
    apple.y = rand() % MAP_H;
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


void update(){
    uint32_t now = SDL_GetTicks();
    float deltaT = (now - last_time) / 1000.0f;
    last_time = now;
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

    // RENDER PLAYER
    // SDL_Rect playerRect = {(int)p.x, (int)p.y, (int)p.sizeX, (int)p.sizeY};
    // SDL_RenderCopy(r, playerTexture, NULL, &playerRect);

    // RENDER UI

    //SDL_SetRenderDrawColor(renderer, 130, 130, 130, 255);
    //SDL_Rect uiBg = {0,0,WIDTH,UI_HEIGHT};
    //SDL_RenderFillRect(renderer, &uiBg);

    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    //for(int i = 0 ; i < lifes ; i++){
    //    SDL_Rect lifeRect = {30 + (40+5)*i, 30, 40, 40};
    //    SDL_RenderFillRect(renderer, &lifeRect);
    //}
    //
    //char buf[20];
    //sprintf(buf, "%ld", score);
    //fontTexture(mainFont, buf, WIDTH/2 + WIDTH/4, 30);

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

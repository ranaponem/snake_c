#include "render.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

void renderGameMenu(SDL_Renderer *r){
  // TODO: 
}

void getSpriteTexture(SDL_Renderer* r, const char* filepath, SDL_Rect rect){
  SDL_Surface* surface = IMG_Load(filepath);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(r, surface);
  SDL_FreeSurface(surface);
  SDL_RenderCopy(r, texture, NULL, &rect);
  SDL_DestroyTexture(texture);
}

void renderGamePlaying(SDL_Renderer *r){
  
  SDL_Rect renderRect;
  renderRect.h = GRID_SIZE; renderRect.w = GRID_SIZE;

  // RENDER GRID

  int curColor;

  for(int y = 0 ; y < MAP_H ; y++){
    curColor = y % 2;

    for(int x = 0 ; x < MAP_W ; x++){
      if(curColor == 0){
        SDL_SetRenderDrawColor(r, BKG_COLOR_1);
        curColor = 1;
      }
      else{
        SDL_SetRenderDrawColor(r, BKG_COLOR_2);
        curColor = 0;
      }

      renderRect.x = x * GRID_SIZE;
      renderRect.y = y * GRID_SIZE;

      SDL_RenderFillRect(r, &renderRect);
    }
  }

  // RENDER APPLE
  // TODO: MAKE APPLE LOAD ITS SPRITE
  
  SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
  renderRect.x = apple.x * GRID_SIZE;
  renderRect.y = apple.y * GRID_SIZE;
  SDL_RenderFillRect(r, &renderRect);

  // RENDER SNAKE
  // TODO: MAKE SNAKE SEGMENTS LOAD SPRITES

  for(int i = 0 ; i < snake.size ; i++){
    renderRect.x = snake.body[i].x * GRID_SIZE;
    renderRect.y = snake.body[i].y * GRID_SIZE;
    char *filepath = i == 0 ? "./sprites/snake_head.png" : "./sprites/snake_body.png";
    getSpriteTexture(r, filepath, renderRect);
  }
}

void renderGamePaused(SDL_Renderer *r){
  // TODO
}

void renderGameOver(SDL_Renderer *r){
  // TODO
}

void renderGameWon(SDL_Renderer *r){
  // TODO
}

#ifndef __RENDER_H__
#define __RENDER_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "constants.h"
#include "colors.h"
#include "snake.h"

void renderGameMenu(SDL_Renderer *r);
void getSpriteTexture(SDL_Renderer* r, const char* filepath, SDL_Rect rect);
void renderGamePlaying(SDL_Renderer *r);
void renderGamePaused(SDL_Renderer *r);
void renderGameOver(SDL_Renderer *r);
void renderGameWon(SDL_Renderer *r);

#endif

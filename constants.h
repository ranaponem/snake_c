#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

// WINDOW INIT MACROS
#define SCR_W 1000
#define SCR_H 500
#define TITLE "Snake"

// MAP MACROS
#define GRID_SIZE 50
#define MAP_W SCR_W/GRID_SIZE
#define MAP_H SCR_H/GRID_SIZE
#define MAP_EMPTY 0
#define MAP_SNAKE 1
#define MAP_APPLE 2

// DIRECTIONS
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

// CELL STRUCT
typedef struct{
  int x, y;
} block_t;

#endif

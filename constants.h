#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#define SCR_W 1000
#define SCR_H 500

#define GRID_SIZE 50

#define MAP_W SCR_W/GRID_SIZE
#define MAP_H SCR_H/GRID_SIZE
#define MAP_EMPTY 0
#define MAP_SNAKE 1
#define MAP_APPLE 2

#define INITIAL_SNAKE_SIZE 3
#define MAX_SNAKE_SIZE MAP_W*MAP_H

#endif

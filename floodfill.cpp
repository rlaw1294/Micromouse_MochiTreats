#include "floodfill.h"

enum compass_direction {NORTH, SOUTH, EAST, WEST};

extern Maze g_maze;


void maze_floodfill(int cheatx, int cheaty, int x, int y, int cur_dist) {
  if (y < 15 && (g_maze.maze[y+1][x]).south==0 ) maze_floodfill(cheatx, cheaty, x, y+1, cur_dist+1);
  if (y > 0 && (g_maze.maze[y-1][x]).north==0 ) maze_floodfill(cheatx, cheaty, x, y-1, cur_dist+1);
  if (x < 15 && (g_maze.maze[y][x+1]).east==0 ) maze_floodfill(cheatx, cheaty, x+1, y, cur_dist+1);
  if (x > 0 && (g_maze.maze[y][x-1]).west==0 ) maze_floodfill(cheatx, cheaty, x-1, y, cur_dist+1);

  //break out conditions
  if (x==7 && y ==8) {
    //update something based on what cheatx cheaty are, and what the current mouse position is
    g_maze.floodfill_next_x = cheatx;
    g_maze.floodfill_next_y = cheaty;
    return;
  }
  if ( (g_maze.maze[y][x]).dist != -1) { return; }
  
  //utilizing cheats!
  if (cur_dist == 1) {
    cheatx = x;
    cheaty = y;
  }
  
  (g_maze.maze[y][x]).dist = cur_dist;
  
  
  

  
}

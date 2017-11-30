#include <StackArray.h>

int r = 4;
int c = 3;

// ROBOT MUST START FACING NORTH
int NORTH = 0;
int EAST = 1;
int SOUTH = 2;
int WEST = 3;
int dir = NORTH;

/* Initialize current location maze array
*  0 means unvisited
*  1 means visited
*/
boolean visited[5][4] = {
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,1}};
  
/* Set maze walls
*  For each grid space, wall locations are represented with a string of 4 binary digits:
*  [bit0 bit1 bit2 bit3 \0] ==> [N E S W \0]
*  N (north wall) = "1000"
*  E (east wall)  = "0100"
*  S (south wall) = "0010"
*  W (west wall)  = "0001"
*  For example: A grid that has a wall to the north and east would have a
*  wall location of "1100"
*/
char detected_wall_loc[5][4][5] = {
  {"1001","1000","1000","1100"},
  {"0001","0000","0000","0100"},
  {"0001","0000","0000","0100"},
  {"0001","0000","0000","0100"},
  {"0011","0010","0010","0110"}};

/**
 * Returns true if the entire maze has been navigated, false otherwise.
 * Uses a DFS search algorithm to find the next dir the robot needs to go and rotates the robot to that dir
 */
void dfs() {
  // detect new walls for current square
  visited[r][c] = 1;
  detectWalls();

  // decide on next dir to go
  if (notDone()) {
    if (r > 0 && detected_wall_loc[r][c][NORTH] == '0' && visited[r-1][c] != 1) {
      faceRobot(NORTH);                                                                                              
      stack.push(dir);
    }
    else if (c < 3 && detected_wall_loc[r][c][EAST] == '0' && visited[r][c+1] != 1) {
      faceRobot(EAST);
      stack.push(dir);
    }
    else if (r < 4 && detected_wall_loc[r][c][SOUTH] == '0' && visited[r+1][c] != 1) {
      faceRobot(SOUTH);
      stack.push(dir);
    }
    else if (c > 0 && detected_wall_loc[r][c][WEST] == '0' && visited[r][c-1] != 1) {
      faceRobot(WEST);
      stack.push(dir);
    }
    else {
      int newDir = (stack.pop() + 2) % 4;
      faceRobot(newDir);
    }
    updatePosition();
  }
  else {
    left.write(94);
    right.write(90);
    while (true) {};
  }
}

void detectWalls() {
  int dirF = dir;
  int dirR = (dir + 1) % 4;
  int dirL = (dir + 3) % 4;
  
  if (dirF == NORTH) {
    if (analogRead(wallSensorF) >= frontThresh) {
      detected_wall_loc[r][c][NORTH] = '1';
      if (r > 0) detected_wall_loc[r-1][c][SOUTH] = '1';
    }
    if (analogRead(wallSensorR) >= sideThresh) {
      detected_wall_loc[r][c][EAST] = '1';
      if (c < 3) detected_wall_loc[r][c+1][WEST] = '1';
    }
    if (analogRead(wallSensorL) >= sideThresh) {
      detected_wall_loc[r][c][WEST] = '1';
      if (c > 0) detected_wall_loc[r][c-1][EAST] = '1';
    }
  }
  else if (dirF == EAST) {
    if (analogRead(wallSensorL) >= sideThresh) {
      detected_wall_loc[r][c][NORTH] = '1';
      if (r > 0) detected_wall_loc[r-1][c][SOUTH] = '1';
    }
    if (analogRead(wallSensorF) >= frontThresh) {
      detected_wall_loc[r][c][EAST] = '1';
      if (c < 3) detected_wall_loc[r][c+1][WEST] = '1';
    }
    if (analogRead(wallSensorR) >= sideThresh) {
      detected_wall_loc[r][c][SOUTH] = '1';
      if (r < 4) detected_wall_loc[r+1][c][NORTH] = '1';
    }
  }
  else if (dirF == SOUTH) {
    if (analogRead(wallSensorF) >= frontThresh) {
      detected_wall_loc[r][c][SOUTH] = '1';
      if (r < 4) detected_wall_loc[r+1][c][NORTH] = '1';
    }
    if (analogRead(wallSensorR) >= sideThresh) {
      detected_wall_loc[r][c][WEST] = '1';
      if (c > 0) detected_wall_loc[r][c-1][EAST] = '1';
    }
    if (analogRead(wallSensorL) >= sideThresh) {
      detected_wall_loc[r][c][EAST] = '1';
      if (c < 3) detected_wall_loc[r][c+1][WEST] = '1';
    }
  }
  else if (dirF == WEST) {
    if (analogRead(wallSensorF) >= frontThresh) {
      detected_wall_loc[r][c][WEST] = '1';
      if (c > 0) detected_wall_loc[r][c-1][EAST] = '1';
    }
    if (analogRead(wallSensorR) >= sideThresh) {
      detected_wall_loc[r][c][NORTH] = '1';
      if (r > 0) detected_wall_loc[r-1][c][SOUTH] = '1';
    }
    if (analogRead(wallSensorL) >= sideThresh) {
      detected_wall_loc[r][c][SOUTH] = '1';
      if (r < 4) detected_wall_loc[r+1][c][WEST] = '1';
    }
  }
}

/**
 * Returns true if there exists an unvisited square adjacent to a visited square, without a wall separating them.
 */
boolean notDone() {
  for (int R = 0; R < 5; R++) {
    for (int C = 0; C < 4; C++) {
      if (visited[R][C] == 0 && 
         ((detected_wall_loc[R][C][NORTH] == '0' && R > 0 && visited[R-1][C] == 1) || 
         (detected_wall_loc[R][C][EAST] == '0' && C < 3 && visited[R][C+1] == 1) || 
         (detected_wall_loc[R][C][SOUTH] == '0' && R < 4 && visited[R+1][C] == 1) || 
         (detected_wall_loc[R][C][WEST] == '0' && C > 0 && visited[R][C-1] == 1)))  {
        return true;
      }
    }
  }
  return false;
}

void updatePosition() {
    // update robot position and squares visited
    if (dir == NORTH) {
      r -= 1;
      //visited[r+1][c] = 1;
    }
    else if (dir == SOUTH) {
      r += 1;
      //visited[r-1][c] = 1;
    }
    else if (dir == EAST) {
      c += 1;
      //visited[r][c-1] = 1;
    }
    else if (dir == WEST) {
      c -= 1;
      //visited[r][c+1] = 1;
    }
}


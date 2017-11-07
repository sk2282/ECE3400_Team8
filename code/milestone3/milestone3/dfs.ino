#include <StackArray.h>

StackArray<int> stack;
int r = 4;
int c = 3;

// ROBOT MUST START FACING NORTH
int NORTH = 0;
int EAST = 1;
int SOUTH = 2;
int WEST = 3;
int direction = NORTH;

/* Initialize current location maze array
*  1 means unvisited
*  0.5 means visited
*  0 is the robot's current location
*/
int visited[5][4] = {
  {1,1,1,1},
  {1,1,1,1},
  {1,1,1,1},
  {1,1,1,1},
  {1,1,1,1}};
  
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
 * Uses a DFS search algorithm to find the next direction the robot needs to go and rotates the robot to that direction
 */
boolean dfs() {
  // update robot position and squares visited
  if (direction == NORTH) {
    r -= 1;
    visited[r+1][c] = 0.5;
  }
  else if (direction == SOUTH) {
    r += 1;
    visited[r-1][c] = 0.5;
  }
  else if (direction == EAST) {
    c += 1;
    visited[r][c-1] = 0.5;
  }
  else if (direction == WEST) {
    c -= 1;
    visited[r][c+1] = 0.5;
  }

  // detect new walls for current square
  detectWalls();

  // decide on next direction to go
  if (!stack.isEmpty() && notDone()) {
    if (r > 0 && detected_wall_loc[r][c][NORTH] == 0 && visited[r-1][c] != 0.5) {
      faceRobot(NORTH);
      stack.push(direction);
    }
    else if (c < 3 && detected_wall_loc[r][c][EAST] == 0 && visited[r][c+1] != 0.5) {
      faceRobot(EAST);
      stack.push(direction);
    }
    else if (r < 4 && detected_wall_loc[r][c][SOUTH] == 0 && visited[r+1][c] != 0.5) {
      faceRobot(SOUTH);
      stack.push(direction);
    }
    else if (c > 0 && detected_wall_loc[r][c][WEST] == 0 && visited[r][c-1] != 0.5) {
      faceRobot(WEST);
      stack.push(direction);
    }
    else {
      int newDir = (stack.pop() + 2) % 4;
      faceRobot(newDir);
    }
    return true;
  }
  else {
    return false;
  }
}

void detectWalls() {
  int dirF = direction;
  int dirR = (direction + 1) % 4;
  int dirL = (direction - 1) % 4;
  if (dirF == NORTH) {
    if (digitalRead(wallSensorF) == LOW) {  // the Schmitt trigger reversed the outputs
      detected_wall_loc[r][c][NORTH] = 1;   // for now HIGH is changed to LOW to take this into consideration
      if (r > 0) detected_wall_loc[r-1][c][SOUTH] = 1;
    }
    if (digitalRead(wallSensorR) == LOW) {
      detected_wall_loc[r][c][EAST] = 1;
      if (c < 3) detected_wall_loc[r][c+1][WEST] = 1;
    }
    if (digitalRead(wallSensorL) == LOW) {
      detected_wall_loc[r][c][WEST] = 1;
      if (c > 0) detected_wall_loc[r][c-1][EAST] = 1;
    }
  }
  else if (dirF == EAST) {
    if (digitalRead(wallSensorL) == LOW) {
      detected_wall_loc[r][c][NORTH] = 1;
      if (r > 0) detected_wall_loc[r-1][c][SOUTH] = 1;
    }
    if (digitalRead(wallSensorF) == LOW) {
      detected_wall_loc[r][c][EAST] = 1;
      if (c < 3) detected_wall_loc[r][c+1][WEST] = 1;
    }
    if (digitalRead(wallSensorR) == LOW) {
      detected_wall_loc[r][c][SOUTH] = 1;
      if (r < 4) detected_wall_loc[r+1][c][NORTH] = 1;
    }
  }
  else if (dirF == SOUTH) {
    if (digitalRead(wallSensorF) == LOW) {
      detected_wall_loc[r][c][SOUTH] = 1;
      if (r < 4) detected_wall_loc[r+1][c][NORTH] = 1;
    }
    if (digitalRead(wallSensorR) == LOW) {
      detected_wall_loc[r][c][WEST] = 1;
      if (c > 0) detected_wall_loc[r][c-1][EAST] = 1;
    }
    if (digitalRead(wallSensorL) == LOW) {
      detected_wall_loc[r][c][EAST] = 1;
      if (c < 3) detected_wall_loc[r][c+1][WEST] = 1;
    }
  }
  else if (dirF == WEST) {
    if (digitalRead(wallSensorF) == LOW) {
      detected_wall_loc[r][c][WEST] = 1;
      if (c > 0) detected_wall_loc[r][c-1][EAST] = 1;
    }
    if (digitalRead(wallSensorR) == LOW) {
      detected_wall_loc[r][c][NORTH] = 1;
      if (r > 0) detected_wall_loc[r-1][c][SOUTH] = 1;
    }
    if (digitalRead(wallSensorL) == LOW) {
      detected_wall_loc[r][c][SOUTH] = 1;
      if (r < 4) detected_wall_loc[r+1][c][WEST] = 1;
    }
  }
}

/**
 * Returns true if there exists an unvisited square adjacent to a visited square, without a wall separating them.
 */
boolean notDone() {
  for (int R = 0; R < 5; R++) {
    for (int C = 0; C < 4; C++) {
      if (visited[R][C] == 1 && 
         ((!detected_wall_loc[R][C][NORTH] && R > 0 && visited[R-1][C] == 0.5) || 
         (!detected_wall_loc[R][C][EAST] && C < 3 && visited[R][C+1] == 0.5) || 
         (!detected_wall_loc[R][C][SOUTH] && R < 4 && visited[R+1][C] == 0.5) || 
         (!detected_wall_loc[R][C][WEST] && C > 0 && visited[R][C-1] == 0.5)))  {
        return true;
      }
    }
  }
  return false;
}


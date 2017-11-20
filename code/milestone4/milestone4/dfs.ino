#include <StackArray.h>

/**
 * Returns true if the entire maze has been navigated, false otherwise.
 * Uses a DFS search algorithm to find the next dir the robot needs to go and rotates the robot to that dir
 */
void dfs() {
  // detect new walls for current square
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

void updatePosition() {
    // update robot position and squares visited
    if (dir == NORTH) {
      r -= 1;
      visited[r+1][c] = 1;
    }
    else if (dir == SOUTH) {
      r += 1;
      visited[r-1][c] = 1;
    }
    else if (dir == EAST) {
      c += 1;
      visited[r][c-1] = 1;
    }
    else if (dir == WEST) {
      c -= 1;
      visited[r][c+1] = 1;
    }
}


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
int visited[5][4] = {
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
boolean dfs() {
  Serial.print("coordinate: ");
  Serial.print(r);
  Serial.print(","); 
  Serial.println(c);
  // detect new walls for current square
  detectWalls();

  if(stack.isEmpty()) {
    Serial.println("stack empty");
  }
  else {
    Serial.print("stack entry ");
    Serial.println(stack.peek());
  }
  // decide on next dir to go
  if (notDone()) {
    if (r > 0 && detected_wall_loc[r][c][NORTH] == '0' && visited[r-1][c] != 1) {
      Serial.println("go north");
      Serial.println(detected_wall_loc[r][c]);
      Serial.print(detected_wall_loc[r][c][NORTH]);
      Serial.print(detected_wall_loc[r][c][EAST]);
      Serial.print(detected_wall_loc[r][c][SOUTH]);
      Serial.println(detected_wall_loc[r][c][WEST]);
      faceRobot(NORTH);
      stack.push(dir);
    }
    else if (c < 3 && detected_wall_loc[r][c][EAST] == '0' && visited[r][c+1] != 1) {
      Serial.println("go east");
      faceRobot(EAST);
      stack.push(dir);
    }
    else if (r < 4 && detected_wall_loc[r][c][SOUTH] == '0' && visited[r+1][c] != 1) {
      Serial.println("go south");
      faceRobot(SOUTH);
      stack.push(dir);
    }
    else if (c > 0 && detected_wall_loc[r][c][WEST] == '0' && visited[r][c-1] != 1) {
      Serial.println("go west");
      faceRobot(WEST);
      stack.push(dir);
    }
    else {
      Serial.println("turn around");
      int newDir = (stack.pop() + 2) % 4;
      faceRobot(newDir);
    }
    updatePosition();
    return true;
  }
  else {
    Serial.println(stack.peek());
    return false;
  }
}

void detectWalls() {
  int dirF = dir;
  int dirR = (dir + 1) % 4;
  int dirL = (dir + 3) % 4;
  if (dirF == NORTH) {
    if (digitalRead(wallSensorF) == LOW) {
      Serial.println("see wall");
      Serial.println(detected_wall_loc[r][c]);
      detected_wall_loc[r][c][NORTH] = '1';
      if (r > 0) detected_wall_loc[r-1][c][SOUTH] = '1';
    }
    if (digitalRead(wallSensorR) == LOW) {
      detected_wall_loc[r][c][EAST] = '1';
      if (c < 3) detected_wall_loc[r][c+1][WEST] = '1';
    }
    if (digitalRead(wallSensorL) == LOW) {
      detected_wall_loc[r][c][WEST] = '1';
      if (c > 0) detected_wall_loc[r][c-1][EAST] = '1';
    }
  }
  else if (dirF == EAST) {
    if (digitalRead(wallSensorL) == LOW) {
      detected_wall_loc[r][c][NORTH] = '1';
      if (r > 0) detected_wall_loc[r-1][c][SOUTH] = '1';
    }
    if (digitalRead(wallSensorF) == LOW) {
      detected_wall_loc[r][c][EAST] = '1';
      if (c < 3) detected_wall_loc[r][c+1][WEST] = '1';
    }
    if (digitalRead(wallSensorR) == LOW) {
      detected_wall_loc[r][c][SOUTH] = '1';
      if (r < 4) detected_wall_loc[r+1][c][NORTH] = '1';
    }
  }
  else if (dirF == SOUTH) {
    if (digitalRead(wallSensorF) == LOW) {
      detected_wall_loc[r][c][SOUTH] = '1';
      if (r < 4) detected_wall_loc[r+1][c][NORTH] = '1';
    }
    if (digitalRead(wallSensorR) == LOW) {
      detected_wall_loc[r][c][WEST] = '1';
      if (c > 0) detected_wall_loc[r][c-1][EAST] = '1';
    }
    if (digitalRead(wallSensorL) == LOW) {
      detected_wall_loc[r][c][EAST] = '1';
      if (c < 3) detected_wall_loc[r][c+1][WEST] = '1';
    }
  }
  else if (dirF == WEST) {
    if (digitalRead(wallSensorF) == LOW) {
      detected_wall_loc[r][c][WEST] = '1';
      if (c > 0) detected_wall_loc[r][c-1][EAST] = '1';
    }
    if (digitalRead(wallSensorR) == LOW) {
      detected_wall_loc[r][c][NORTH] = '1';
      if (r > 0) detected_wall_loc[r-1][c][SOUTH] = '1';
    }
    if (digitalRead(wallSensorL) == LOW) {
      detected_wall_loc[r][c][SOUTH] = '1';
      if (r < 4) detected_wall_loc[r+1][c][WEST] = '1';
    }
  }
  Serial.println("final");
  Serial.println(detected_wall_loc[r][c]);
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
        Serial.println("TRUE");
        return true;
      }
    }
  }
  Serial.println("FALSE");
  return false;
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
    Serial.print("update pos:");
    Serial.print(r);
    Serial.print(",");
    Serial.println(c);
}


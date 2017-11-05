void de2bi(int number) {
  int result = number;
  uint8_t bitsCount = sizeof(number)*8;
  char str[bitsCount+1];
  itoa(result,str,2);
  wall_bin = str;
}

void detectWalls() {
// Updates walls as seen by the robot
  int dirF = direction;
  int dirR = (direction + 1) % 4;
  int dirL = (direction - 1) % 4;
  
  if (dirF == 0) { // faces north
    if (analogRead(wallSensorF) == HIGH && !wall_bin[0]) {
      detected_wall_loc[r][c] += 1;
    }
    if (analogRead(wallSensorR) == HIGH && !wall_bin[1]) {
      detected_wall_loc[r][c] += 2;
    }
    if (analogRead(wallSensorL) == HIGH && !wall_bin[3]) {
      detected_wall_loc[r][c] += 8;
    }
  }
  else if (dirF == 1) { // faces east
    if (analogRead(wallSensorF) == HIGH && !wall_bin[1]) {
      detected_wall_loc[r][c] += 2;
    }
    if (analogRead(wallSensorR) == HIGH && !wall_bin[2]) {
      detected_wall_loc[r][c] += 4;
    }
    if (analogRead(wallSensorL) == HIGH && !wall_bin[0]) {
      detected_wall_loc[r][c] += 0;
    }
  }
  else if (dirF == 2) { // faces south
    if (analogRead(wallSensorF) == HIGH && !wall_bin[2]) {
      detected_wall_loc[r][c] += 4;
    }
    if (analogRead(wallSensorR) == HIGH && !wall_bin[3]) {
      detected_wall_loc[r][c] += 8;
    }
    if (analogRead(wallSensorL) == HIGH && !wall_bin[1]) {
      detected_wall_loc[r][c] += 2;
    }
  }
  else if (dirF == 3) { // faces west
    if (analogRead(wallSensorF) == HIGH && !wall_bin[3]) {
      detected_wall_loc[r][c] += 8;
    }
    if (analogRead(wallSensorR) == HIGH && !wall_bin[0]) {
      detected_wall_loc[r][c] += 1;
    }
    if (analogRead(wallSensorL) == HIGH && !wall_bin[2]) {
      detected_wall_loc[r][c] += 4;
    }
  }
}

boolean notDone(int visited[][4], int detected_wall_loc[][4]) {
    for (int r = 0; r < 5; r++) { 
        for (int c = 0; c < 4; c++) {
            de2bi(&detected_wall_loc(r,c));
            if (visited[r][c] == 1) {
                if ((wall_bin[1] == 0 && r > 1 && visited[r-1][c] == 0.5) || 
                    (wall_bin[2] == 0 && r < 5 && visited[r+1][c] == 0.5) ||
                    (wall_bin[3] == 0 && c < 4 && visited[r][c+1] == 0.5) ||
                    (wall_bin[4] == 0 && c > 1 && visited[r][c-1] == 0.5)) {
                    return true;
                }
            }
        }
    }
    return false;
}

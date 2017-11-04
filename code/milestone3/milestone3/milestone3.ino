#include <Servo.h>

Servo left;
Servo right;
int roboStop = 0;     // robot stops moving
int leftLine = 0;     // Pin for left line detector
int rightLine = 1;    // Pin for right line detector
int leftWide = 2;     // Pin for left intersection detector
int rightWide = 3;    // Pin for right intersection detector
int thresh   = 800;     // Threshold for black line detection
int detectCooldown = 0;
int DETECT_COOLDOWN = 50;

int wallSensorF = 11;
int wallSensorR = 12;
int wallSensorL = 13;

// N = 0, E = 1, S = 2, W = 3
// ROBOT MUST START FACING NORTH
int direction = 0;



  /* Initialize current location maze array
   *  1 means unvisited
   *  0.5 means visited
   *  0 is the robot's current location
   */
  int curr_loc[5][4] = {
    {1,1,1,1},
    {1,1,1,1},
    {1,1,1,1},
    {1,1,1,1},
    {1,1,1,0}};

  int visited[5][4] = {
    {1,1,1,1},
    {1,1,1,1},
    {1,1,1,1},
    {1,1,1,1},
    {1,1,1,1}};

  /* Set maze walls
   *  For each grid space, wall locations are represented with 4 bits:
   *  [bit3 bit2 bit1 bit0] ==> [W E S N]
   *  N (north wall) = 0001 in binary or 1 in decimal
   *  S (south wall) = 0010 in binary or 2 in decimal'
   *  E (east wall)  = 0100 in binary or 4 in decimal
   *  W (west wall)  = 1000 in binary or 8 in decimal
   *  For example: A grid that has a wall to the north and east would have a
   *  wall location of 0101 in binary or 5 in decimal
*/
  int detected_wall_loc[5][4] = {
    {9,1,1,5},
    {8,0,0,4},
    {8,0,0,4},
    {8,0,0,4},
    {10,2,2,6}};

void setup() {
  Serial.begin(9600);
  pinMode(wallSensorL, INPUT);
  pinMode(wallSensorR, INPUT);
  pinMode(wallSensorF, INPUT);
  left.attach(5);
  right.attach(6);
}

void loop() {
  int lRead = analogRead(leftLine);
  int rRead = analogRead(rightLine);
  int lwRead = analogRead(leftWide);
  int rwRead = analogRead(rightWide);

  if((lwRead >= thresh || rwRead >= thresh) && detectCooldown == 0){
    dfs(visited,curr_loc);
    detectCooldown = DETECT_COOLDOWN;
  }
  else{
    detectCooldown--;
    if (detectCooldown < 0) {
      detectCooldown = 0;
    }
  }

  if(lRead<=thresh && rRead<=thresh || roboStop){     // stop
    left.write(90);
    right.write(90);
  }
  else{
    if(lRead<thresh){  // left side is out of line
      left.write(170);
      right.write(86);
    }
    else if(rRead<thresh){   // right side is out of line
      left.write(94);
      right.write(10);
    }
    else{     // go straight
      left.write(100);
      right.write(80);
    }
  }
  //algorithm

}

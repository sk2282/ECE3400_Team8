#include <Servo.h>
#include <StackArray.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

StackArray<int> stack;
Servo left;
Servo right;
int leftLine = 2; //10; //0;     // Pin for left line detector
int rightLine = 3; //11; //1;    // Pin for right line detector
int leftWide = 4; //12; //2;     // Pin for left intersection detector
int rightWide = 7; //13; //3;    // Pin for right intersection detector
//int thresh   = 500;     // Threshold for black line detection
int detectCooldown = 0;
int DETECT_COOLDOWN = 300;

int wallSensorF = 0; //11; // front wall sensor
int wallSensorR = 1; //12; // right wall sensor
int wallSensorL = 2; //13; // left wall sensor
int frontThresh = 500; // threshold value for front wall sensor 
int sideThresh = 375; // threshold value for side wall sensor threshold

/*
int lRead;
int rRead;
int lwRead;
int rwRead;
*/

int frontRead; // for wall sensors
int leftRead;
int rightRead;

int r = 4;
int c = 3;

// ROBOT MUST START FACING NORTH
int NORTH = 0;
int EAST = 1;
int SOUTH = 2;
int WEST = 3;
int dir = NORTH;

/* Initialize current location maze array
   0 means unvisited
   1 means visited
*/
boolean visited[5][4] = {
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,1},
};

/* Set maze walls
   For each grid space, wall locations are represented with a string of 4 binary digits:
   [bit0 bit1 bit2 bit3 \0] ==> [N E S W \0]
   N (north wall) = "1000"
   E (east wall)  = "0100"
   S (south wall) = "0010"
   W (west wall)  = "0001"
   For example: A grid that has a wall to the north and east would have a
   wall location of "1100"
*/
char detected_wall_loc[5][4][5] = {
  {"1001", "1000", "1000", "1100"},
  {"0001", "0000", "0000", "0100"},
  {"0001", "0000", "0000", "0100"},
  {"0001", "0000", "0000", "0100"},
  {"0011", "0010", "0010", "0110"}
};

/**
   Returns true if there exists an unvisited square adjacent to a visited square, without a wall separating them.
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

void setup() {
  Serial.begin(9600);
  /*
  pinMode(wallSensorL, INPUT);
  pinMode(wallSensorR, INPUT);
  pinMode(wallSensorF, INPUT);
  */
  pinMode(leftLine, INPUT);
  pinMode(rightLine, INPUT);
  pinMode(leftWide, INPUT);
  pinMode(rightWide, INPUT);
  left.attach(5);
  right.attach(6);
  Serial.begin(115200); // use the serial port
  TIMSK0 = 0; // turn off timer0 for lower jitter
  ADCSRA = 0xe5; // set the adc to free running mode
  ADMUX = 0x40; // use adc0
  DIDR0 = 0x01; // turn off the digital input for adc0
}

void loop() {
  // INTERSECTION DETECTION
  if ((digitalRead(leftWide) == LOW && digitalRead(rightWide) == LOW) && detectCooldown <= 0) {
    detectCooldown = DETECT_COOLDOWN;
    if (!notDone()) halt();
    else dfs();
  }
  else {
    detectCooldown--;
    if (detectCooldown < 0) detectCooldown = 0;
  }

  // Read for treasures
  treasureRead();
  
  followLine();
}


#include <Servo.h>
#include <StackArray.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
//#include <FFT.h>
#include <avr/interrupt.h>
#include <stdlib.h>

StackArray<int> stack;
Servo left;
Servo right;
int leftLine = 2;      // Pin for left line detector
int rightLine = 3; //0?; change for interrupts    // Pin for right line detector
int leftWide = 4;      // Pin for left intersection detector
int rightWide = 7; // 1?; change for interrupts    // Pin for right intersection detector
//int thresh   = 500;     // Threshold for black line detection
int detectCooldown = 0;
int DETECT_COOLDOWN = 300;

int wallSensorF = 3; //11; // front wall sensor
int wallSensorR = 1; //12; // right wall sensor
int wallSensorL = 2; //13; // left wall sensor
int frontThresh = 300; //375; // threshold value for front wall sensor 
int sideThresh = 300; //375; // threshold value for side wall sensor threshold

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

int start = 0;

//int tempADCSRA = ADCSRA;
//int tempDIDR0 = DIDR0;

// TREASURE INTERRUPT STUFF
  int period=0;
  unsigned char treas=0;
  volatile boolean triggered = false;

//unsigned char treas = 0;
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
  digitalWrite(8, HIGH);  
//  halt();
  return false;
}

/** RADIO SENDER STUFF */
// Hardware configuration
RF24 radio(9,10); // Set up nRF24L01 radio on SPI bus plus pins 9 & 10
//
//// Topology
const uint64_t pipes[2] = { 0x0000000016LL, 0x0000000017LL }; // radio pipe addresses for the 2 nodes to communicate
//
//// Role management
//// Set up role.  This sketch uses the same software for all the nodes
//// in this system.  Doing so greatly simplifies testing.
//
typedef enum { role_ping_out = 1, role_pong_back } role_e; // the various roles supported by this sketch
const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"}; // the debug-friendly names of those roles
role_e role = role_ping_out; // the role of the current running sketch


void setup() {
//  Serial.begin(9600);
  Serial.begin(57600);
  printf_begin();
  /** RADIO SENDER SETUP: setup and configure rf radio */
  radio.begin();
//
//  // optionally, increase the delay between retries & # of retries
  radio.setRetries(15,15);
  radio.setAutoAck(true);
  radio.setChannel(0x50); // set the channel
  radio.setPALevel(RF24_PA_MIN); // set the power
  radio.setDataRate(RF24_250KBPS);
//
//  // Open pipes to other nodes for communication
//  // This simple sketch opens two pipes for these two nodes to communicate
//  // back and forth.
//  // Open 'our' pipe for writing
//  // Open the 'other' pipe for reading, in position #1 (we can have up to 5 pipes open for reading)
//
  if ( role == role_ping_out )
  {
    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1,pipes[1]);
  }
  else
  {
    radio.openWritingPipe(pipes[1]);
    radio.openReadingPipe(1,pipes[0]);
  }

//  radio.startListening(); // start listening
  pinMode(8, OUTPUT);
  pinMode(leftLine, INPUT);
  pinMode(rightLine, INPUT);
  pinMode(leftWide, INPUT);
  pinMode(rightWide, INPUT);
  //Serial.begin(115200); // use the serial port
//  TIMSK0 = 0; // turn off timer0 for lower jitter
//  ADCSRA = 0xe5; // set the adc to free running mode
//  ADMUX = 0x40; // use adc0
//  DIDR0 = 0x01; // turn off the digital input for adc0
  left.attach(5);
//  right.attach(3); // need digital 6 for comparator
  right.attach(6);
  left.write(90);
  right.write(90);
  stack.push(19);
  digitalWrite(8, LOW);
 // analogWrite(A5, 0);

   Serial.begin(57600);
  
  //treasure interrupt
  TCCR2B = 2; // running with clock divided by 8 TCCR@A=0; // All other functions disabled
  TCCR2A = 0; // Turn off other timer2 functions
  TCNT2 = 0; // Initialize the counter
  sei();
  ACSR = (1<<ACIE) | (1<<ACIS1) | (1<<ACIS0);
}

ISR(ANALOG_COMP_vect){
  triggered = true;
  period=TCNT2;
  TCNT2=0;
}


void loop() {
  // INTERSECTION DETECTION
//  while(analogRead(4)<900);
  if ((digitalRead(leftWide) == LOW && digitalRead(rightWide) == LOW) && detectCooldown <= 0) {
   // analogWrite(A5, 255);
    detectCooldown = DETECT_COOLDOWN;
    if (!notDone()) {
      radioSend(); // send data for last square
      halt();
    }
    else {
//      radioSend();
//      stopDelay(500);
//      printf("in else\n");
      dfs();
//      printf("after dfs\n");
      left.write(100);
      right.write(80);
      //
    }
  }
  else {
    detectCooldown--;
    if (detectCooldown < 0) {
      detectCooldown = 0;
   //   analogWrite(A5, 0);
    }
  }

  followLine();
  
}


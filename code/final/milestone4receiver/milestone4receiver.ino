#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

//
// Hardware configuration
//

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10

RF24 radio(9,10);

//
// Topology
//

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0x0000000016LL, 0x0000000017LL };

//
// Role management
//
// Set up role.  This sketch uses the same software for all the nodes
// in this system.  Doing so greatly simplifies testing.
//

// The various roles supported by this sketch
typedef enum { role_ping_out = 1, role_pong_back } role_e;

// The debug-friendly names of those roles
const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};

// The role of the current running sketch
role_e role = role_pong_back;

void setup(void)
{
  // setup pins
  pinMode(8, OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);
  
  
  //
  // Print preamble
  //

  Serial.begin(57600);
//  Serial.begin(9600);
  printf_begin();
  printf("\n\rRF24/examples/GettingStarted/\n\r");
  printf("ROLE: %s\n\r",role_friendly_name[role]);
  printf("*** PRESS 'T' to begin transmitting to the other node\n\r");

  //
  // Setup and configure rf radio
  //

  radio.begin();

  // optionally, increase the delay between retries & # of retries
  radio.setRetries(15,15);
  radio.setAutoAck(true);
  // set the channel
  radio.setChannel(0x50);
  // set the power
  // RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_MED=-6dBM, and RF24_PA_HIGH=0dBm.
  radio.setPALevel(RF24_PA_MIN);
  //RF24_250KBPS for 250kbs, RF24_1MBPS for 1Mbps, or RF24_2MBPS for 2Mbps
  radio.setDataRate(RF24_250KBPS);

  // optionally, reduce the payload size.  seems to
  // improve reliability
  //radio.setPayloadSize(8);

  //
  // Open pipes to other nodes for communication
  //

  // This simple sketch opens two pipes for these two nodes to communicate
  // back and forth.
  // Open 'our' pipe for writing
  // Open the 'other' pipe for reading, in position #1 (we can have up to 5 pipes open for reading)

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

  //
  // Start listening
  //

  radio.startListening();

  //
  // Dump the configuration of the rf unit for debugging
  //

  radio.printDetails();
}


void loop(void) {
  //
  // Pong back role.  Receive each packet, dump it out, and send it back
  //
  //sprintf("loop");
  if ( role == role_pong_back )
  {
    // if there is data ready
    if ( radio.available() )
    {
      // Dump the payloads until we've gotten everything
      // RECEIVER SIDE
      unsigned int got_data;
      bool done = false;
      while (!done)
      {
        // Fetch the payload, and see if this was the last one.
        done = radio.read(&got_data, sizeof(int) );
        
        // Send to FPGA
        String x = String(got_data, BIN);
        while (x.length() < 12) {
          x = '0' + x;
        }
        int got_data_bin[12];
        dec2bin(got_data,got_data_bin);
        digitalWrite(8, got_data_bin[8]); // x msb
        digitalWrite(7, got_data_bin[7]); // x lsb
        digitalWrite(6, got_data_bin[11]); // y msb
        digitalWrite(5, got_data_bin[10]); // y
        digitalWrite(4, got_data_bin[9]); // y lsb
        digitalWrite(3, got_data_bin[5]); // treasure msb
        digitalWrite(2, got_data_bin[4]); // treasure lsb
        digitalWrite(A4,got_data_bin[6]); // done
//        digitalWrite(A4,0);
        
        digitalWrite(A3, got_data_bin[0]); // wallN
        digitalWrite(A2, got_data_bin[1]); // wallE
        digitalWrite(A1, got_data_bin[2]); // wallS
        digitalWrite(A0, got_data_bin[3]); // wallW

        // Spew it
        printf("Got payload %d...\n",got_data); // display decimal
        Serial.println(x);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c\n",x[0],x[1],x[2],x[3],x[4],x[5],x[6],x[7],x[8],x[9],x[10],x[11]);
        printf("done: %i, x: %i%i, y: %i%i%i, treasure: %i%i, walls: %i%i%i%i \n",got_data_bin[5],got_data_bin[3],got_data_bin[4],got_data_bin[0],got_data_bin[1],got_data_bin[2],got_data_bin[6],got_data_bin[7],got_data_bin[11],got_data_bin[10],got_data_bin[9],got_data_bin[8]);
        

        // Delay just a little bit to let the other unit
        // make the transition to receiver
        delay(20);

      }

      // First, stop listening so we can talk
      radio.stopListening();

      // Send the final one back.
      radio.write(&got_data, sizeof(int) );
//      printf("Sent response.\n\r");

      // Now, resume listening so we catch the next packets.
      radio.startListening();
    }
  }
}

void dec2bin(int data, int out[12]) {
  int data_tmp = data;
  for (int tmp=11; tmp >= 0; tmp--) {
    if (data_tmp >= pow(2,tmp) && data_tmp < pow(2,tmp+1)) {
      out[tmp] = HIGH;
      data_tmp -= pow(2,tmp);
    }
    else {
      out[tmp] = LOW;
    }
  }
}


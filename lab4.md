# Lab 4: 

## Objective:

## Team Division:
* Radio: Rohit Krishnakumar, Alice Song, Victoria Tu
* FPGA: Meghan Chen, Serena Krech, Michael Yee

## Radio Team:
### Materials Used:
* 2 Nordic nRF24L01+ transceivers
* 2 Arduino Unos (one must be shared with the other sub-team)
* 2 USB A/B cables
* 2 radio breakout boards with headers

### Procedure:

#### 1. Download the RF24 Arduino library add to Arduino library directory
#### 2. Download Getting Started Sketch from the course repository and replaced Getting Started Sketch from RF24 library
#### 3. Changed identifier numbers for 2 pipes based on our team (22, 23)
##### a. Used formula from lab4 website page 2(3D+N)+X
##### b. Set the channel numbers for our team by modifying the Arduino code
#### 4. Programmed both Arduino boards with the Getting Started example
##### a. Plug both Arduinos to the laptop
##### b. Select one Arduino to be the transmitter by typing “T” in the serial monitor
##### c. Switched between the serial monitors of each Arduino to see that one was receiving what the other was transmitting
#### 5. Modify code to send the maze as a single packet
##### a. Defined the maze
```c
    // Define maze
    unsigned char maze[4][5] =
    {
      3, 3, 3, 3, 3,
      3, 1, 1, 1, 3,
      3, 2, 0, 1, 2,
      3, 1, 3, 1, 3,
      //3, 0, 3, 1, 0
    };
```
##### b. Modified sender/transmit side
```c
    // Send maze in single payload
    printf("Now sending the maze!\n");
    bool ok = radio.write( maze, sizeof(maze) );

    if (ok)
      printf("ok...");
    else
      printf("failed.\n\r");
```
##### c. Modified receiver side
```c
      // Dump the payloads until we've gotten everything
      unsigned char got_maze[4][5];
      bool done = false;
      while (!done)
      {
        // Fetch the payload, and see if this was the last one.
        done = radio.read( got_maze, sizeof(got_maze) );

        // Print the maze
        for (int i=0; i < 4; i++) {
          for (int j=0; j < 5; j++) {
            printf("%d ", got_maze[i][j]);
          }
          printf("\n");
        }

        // Spew it
        printf("Got payload %lu...",got_time);

        // Delay just a little bit to let the other unit
        // make the transition to receiver
        delay(20);

      }
```
##### d. The serial monitor shows what we expect. The transmitting Arduino sends the payload, and the receiving Arduino gets the maze. 

Transmit: 

<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Lab4/TransmitWholeMaze.png" height="100" />

Receive:

<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Lab4/ReceiveWholeMaze.png" height="100" />

##### e. The RFK library has an Auto-ACK feature
#### 6. Modify code to send new data 
##### a. Send 3 pieces of information: x-coordinate, y-coordinate, state of current position
##### b. Maze is 4x5, so we define the orientation so that the x-coordinate needs 3 bits, and the y-coordinate needs 2 bits.
##### c. There are 4 different states (unvisited, no wall, wall, treasure), so the data needs 2 bits.
##### d. On the transmitter side, we packed the bits together on using left shift and sent the package as a single payload.
```c
    // SENDER SIDE
    // Define maze
    unsigned char new_data;
    // pack bits as follows:
    // x-coor | y-coor | data
    // 3 bits | 2 bits | 2 bits

    // test
    unsigned char x = 4;
    unsigned char y = 3;
    unsigned char d = 3;

    // shift bits in order to pack bits, then or them together
    new_data = x << 4 | y << 2 | d;
    // (4, 3, 3) should give 1001111 or 79 in decimal

    // Send maze in single payload
    printf("Now sending new map data!\n");
    bool ok = radio.write(&new_data, sizeof(unsigned char) );

    if (ok)
      printf("ok...");
    else
      printf("failed.\n\r");

    // Now, continue listening
    radio.startListening();
```
##### e. The receiver side can then unpack the bits.
```c
      // RECEIVER SIDE
      unsigned char got_data;
      bool done = false;
      while (!done)
      {
        // Fetch the payload, and see if this was the last one.
        done = radio.read(&got_data, sizeof(unsigned char) );

        // Spew it
        printf("Got payload %d...",got_data); // display decimal

        // Delay just a little bit to let the other unit
        // make the transition to receiver
        delay(20);

      }
```
##### f. The serial monitor verified what we expected, which was to send/receive payload 79 (1001111).

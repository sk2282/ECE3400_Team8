# Milestone 4: Maze-mapping Robot

## Objective: 
* The goal of this milestone is to have a functioning system that has the robot map the maze and display it on the VGA.

### 1. Treasure Detection Integration
* Changed FFT to 128 to reduce memory use
* This is the treasure read function:

```c

unsigned char treasureRead() {
  cli();        // UDRE interrupt slows this way down on arduino1.0
  for (int i = 0 ; i < FFT_N*2 ; i += 2) {      // save 256 samples
    while(!(ADCSRA & 0x10)); // wait for adc to be ready
    ADCSRA = 0xf5;        // restart adc
    byte m = ADCL;        // fetch adc data
    byte j = ADCH;
    int k = (j << 8) | m; // form into an int
    k -= 0x0200;          // form into a signed int
    k <<= 6;              // form into a 16b signed int
    fft_input[i] = k;     // put real data into even bins
    fft_input[i+1] = 0;   // set odd bins to 0
  }
  fft_window();           // window the data for better frequency response
  fft_reorder();          // reorder the data before doing the fft
  fft_run();              // process the data in the fft
  fft_mag_log();          // take the output of the fft
  sei();

  int max_7k = max_in_range(44/2,48/2);
  int max_12k = max_in_range(78/2,82/2);
  int max_17k = max_in_range(112/2,116/2);
  int RATIO_THRESH = 2.6;

  if (max_7k/30 > RATIO_THRESH) return 1;
  else if (max_12k/30 > RATIO_THRESH) return 2;
  else if (max_17k/30 > RATIO_THRESH) return 3;
  else return 0;
}
```

### 2. VGA Display
#### Sending Data
* We based our code on the radio communication code used in Lab 4. In lab 4, the code included both sender and receiver functionality.
* For this milestone, we divided the code up so that one Arduino (robot) has the sender code while the other Arduino (base station) has the receiver code
* Another thing that was changed was in the sender code. In lab 4, we represented the data with 2 bits. Now, we represent data with 7 bits as follows: 3 bits for x-coordinate, 2 bits for y-coordinate, 1 bit for done, 2 bits for treasure detection, and 4 bits for wall detection.
* To package the data, we followed lab 4 similarly. Instead of shifting x and y by 4 and 2 bits, we are now shifting them by 9 and 7 bits, respectively.

```c
// shift bits in order to pack bits, then or them together
new_data = x << 9 | y << 7 | d;
// (4, 3, 1011001) should give 100111011000 or 2520 in decimal
//  x  ||  y ||   done  | treasure | wall
// 100 || 11 ||    1    |    01    | 1000

```

* We also had to modify the types of some variables to take into consideration the fact that we now have more bits represented in data. Previously, they were char rather than int.

```c
unsigned int new_data;
...
bool ok = radio.write(&new_data, sizeof(int) );
...
radio.read( &got_time, sizeof(int) );
```

* We then checked the new code on the 2 Arduinos with the following values: x = 4, y = 3, data = B1011000. The serial monitor confirmed our answer, as the receiver printed that it received payload 2520, which is 100111011000 in decimal. 

#### Integrating Radio Communication with Maze-Mapping Code
* We added the necessary header files and set-up code to our maze-mapping code from milestone 3
* We created a new tab to include the sender radio code, which we modified to get information from our milestone 3 code

```c
void radioSend() {
    unsigned char row = r;
    unsigned char col = c;
    unsigned char d = !notDone() << 6 | treasureRead() << 4 | detected_wall_loc[r][c];
}
```

* Each time our robot reads new information about the maze, it will update its row and column coordinates as well as “data,” which contains information about the progress of the robot, the treasures, and the walls.  

```c
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
    radioSend();
  }
}
```

#### FPGA
* Now we will connect the base-station Arduino with the FPGA.


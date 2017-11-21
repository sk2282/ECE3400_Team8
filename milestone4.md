# Milestone 4: Maze-mapping Robot

## Objective:

### VGA Display
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
* Each time our robot reads new information about the maze, it will update its x and y coordinates as well as “data,” which contains information about the progress of the robot, the treasures, and the walls.  

```c
void radioSend(unsigned char x, unsigned char y, unsigned char d) {

}
```

#### FPGA



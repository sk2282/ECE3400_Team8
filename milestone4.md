# Milestone 4: Maze-mapping Robot

## Objective:

### VGA Display
#### Sending Data
* We based our code on the radio communication code used in Lab 4. In lab 4, the code included both sender and receiver functionality.
* For this milestone, we divided the code up so that one Arduino (robot) has the sender code while the other Arduino (base station) has the receiver code
* Another thing that was changed was in the sender code. In lab 4, we represented the data with 2 bits. Now, we represent data with 7 bits as follows: 3 bits for x-coordinate, 2 bits for y-coordinate, 1 bit for done, 2 bits for treasure detection, and 4 bits for wall detection.
* To package the data, we followed lab 4 similarly. Instead of shifting x and y by 4 and 2 bits, we are now shifting them by 9 and 7 bits, respectively. [code]
* We then checked the new code on the 2 Arduinos with the following values: x = 4, y = 3, data = B1011000. The serial monitor confirmed our answer, as the receiver printed that it received payload 2520, which is 100111011000 in decimal. 

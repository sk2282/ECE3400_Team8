# Lab 4: 

## Objective:

## Team Division:
* Radio: Rohit Krishnakumar, Alice Song, Victoria Tu
* FPGA: Meghan Chen, Serena Krech, Michael Yee

## Radio Team:
### Materials Used:

### Procedure:

#### 1.

code snippet 1
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

code snippet 2
```c
    // Send maze in single payload
    printf("Now sending the maze!\n");
    bool ok = radio.write( maze, sizeof(maze) );

    if (ok)
      printf("ok...");
    else
      printf("failed.\n\r");
```

code snippet 3
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

code snippet 4
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

code snippet 5
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
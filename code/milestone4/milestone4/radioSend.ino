void radioSend(unsigned char x, unsigned char y, unsigned char d) {
  //
  // Ping out role.  Repeatedly send the current time
  //

  if (role == role_ping_out)
  {
    // First, stop listening so we can talk.
    radio.stopListening();

    // SENDER SIDE
    // Define maze
    unsigned int new_data;
    // pack bits as follows:
    // x-coor | y-coor | data
    // 3 bits | 2 bits | 7 bits

    // data example:
    //  done   treasure    wall
    //    1       01       1001

    // test
//    unsigned char x = 4;
//    unsigned char y = 3;
//    unsigned char d = B1011000;

    // shift bits in order to pack bits, then or them together
    new_data = x << 9 | y << 7 | d;
    // (4, 3, 1011001) should give 100111011000 or 2520 in decimal
    //  x  ||  y ||   done  | treasure | wall
    // 100 || 11 ||    1    |    01    | 1000

    // Send maze in single payload
    printf("Now sending new map data!\n");
    bool ok = radio.write(&new_data, sizeof(int) ); //sizeof(unsigned char)

    if (ok)
      printf("ok...");
    else
      printf("failed.\n\r");

    // Now, continue listening
    radio.startListening();

    // Wait here until we get a response, or timeout (250ms)
    unsigned long started_waiting_at = millis();
    bool timeout = false;
    while ( ! radio.available() && ! timeout )
      if (millis() - started_waiting_at > 200 )
        timeout = true;

    // Describe the results
    if ( timeout )
    {
      printf("Failed, response timed out.\n\r");
    }
    else
    {
      // Grab the response, compare, and send to debugging spew
      unsigned long got_time;
      radio.read( &got_time, sizeof(int) ); //sizeof(unsigned long)

      // Spew it
      printf("Got response %lu, round-trip delay: %lu\n\r",got_time,millis()-got_time);
    }

    // Try again 1s later
    delay(1000);
  }
}


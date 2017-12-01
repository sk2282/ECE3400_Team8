void radioSend() {
  //
  // Ping out role.  Repeatedly send the current time
  //
  Serial.println(F("radio send"));
  radio.startListening(); // moved from setup
  if (role == role_ping_out)
  {
    // First, stop listening so we can talk.
    radio.stopListening();

    // SENDER SIDE
    // Define maze
    unsigned int new_data;
    // pack bits as follows:
    //  row   | column | data
    // 3 bits | 2 bits | 7 bits

    // data example:
    //  done   treasure    wall
    //    1       01       1001

    // test
    unsigned char row = r;
    unsigned char col = c;
    unsigned char d = !notDone() << 6 | treas << 4 | detected_wall_loc[r][c][NORTH] << 3 | detected_wall_loc[r][c][EAST] << 2 | detected_wall_loc[r][c][SOUTH] << 1 | detected_wall_loc[r][c][WEST];
//    unsigned char d = !notDone() << 6 | 00 << 4 | detected_wall_loc[r][c][NORTH] << 3 | detected_wall_loc[r][c][EAST] << 2 | detected_wall_loc[r][c][SOUTH] << 1 | detected_wall_loc[r][c][WEST];

    // shift bits in order to pack bits, then or them together
//    new_data = col << 7 | row << 9 | d;
    new_data = row << 9 | col << 7 | d;
    // (4, 3, 1011000) should give 100111011000 or 2520 in decimal
    //  r  ||  c ||   done  | treasure | wall
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
    while ( ! radio.available() && ! timeout ) {
      if (millis() - started_waiting_at > 200 )
        timeout = true;
    }
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
    radio.stopListening();
    // Try again 1s later
    //delay(1000);
  }
}


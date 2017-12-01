/*
fft_adc_serial.pde
guest openmusiclabs.com 7.7.14
example sketch for testing the fft library.
it takes in data on ADC0 (Analog0) and processes them
with the fft. the data is sent out over the serial
port at 115.2kb.
*/

#define LOG_OUT 1 // use the log output function
#define FFT_N 128 // set to 128 point fft

#include <FFT.h> // include the library

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

//    Serial.println("");
  for (int i=0; i < FFT_N; i++) {
//      Serial.println(fft_log_out[i]);
  }
  /*
  7kHz: [44,49]
  12kHz: [78,82]
  17kHz: [112,116]
  */
  int max_7k = max_in_range(44/2,48/2);
  int max_12k = max_in_range(78/2,82/2);
  int max_17k = max_in_range(112/2,116/2);
  int RATIO_THRESH = 2.6;

  if (max_7k/30 > RATIO_THRESH) {
//    Serial.println("7k 7k 7k 7k 7k 7k 7k 7k 7k 7k 7k 7k 7k 7k 7k 7k 7k");
    return 1;
  }
  else if (max_12k/30 > RATIO_THRESH) {
//    Serial.println("12k   12k   12k   12k   12k   12k   12k   12k   12k");
    return 2;
  }
  else if (max_17k/30 > RATIO_THRESH) {
//    Serial.println("17k     17k     17k     17k     17k     17k     17k");
    return 3;
  }
  else {
//    Serial.println("No Signal");
    return 0;
  }   
}

int max_in_range(int start, int end0) {
    int the_max = 0;
    for (int i=start; i <= end0; i++) {
      int fft_val = fft_log_out[i];
      if (fft_val > the_max) {
        the_max = fft_val;
      }
    }
    return the_max;
  }


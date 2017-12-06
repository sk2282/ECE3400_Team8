#define LOG_OUT 1 // use the log output function
#define FFT_N 128 // set to 128 point fft
//
#include <FFT.h> // include the library

boolean micRead() {

 // cli();        // UDRE interrupt slows this way down on arduino1.0
  for (int i = 0 ; i < 256 ; i += 2) {
      fft_input[i] = analogRead(A5); // <-- NOTE THIS LINE
      fft_input[i+1] = 0;
    }
  fft_window();           // window the data for better frequency response
  fft_reorder();          // reorder the data before doing the fft
  fft_run();              // process the data in the fft
  fft_mag_log();          // take the output of the fft
//  sei();
  Serial.println("Start");

if(fft_log_out[9] > 70 && fft_log_out[10] > 70){
  return true;
} else {
  return false;
}
}


//#define LOG_OUT 1 // use the log output function
//#define FFT_N 128 // set to 128 point fft
////
//#include <FFT.h> // include the library
//
//unsigned char treasRead() {
//
//  for (int i = 0 ; i < 256 ; i += 2) {
//      fft_input[i] = analogRead(A4); // <-- NOTE THIS LINE
//      fft_input[i+1] = 0;
//  }
//
//  fft_window();           // window the data for better frequency response
//  fft_reorder();          // reorder the data before doing the fft
//  fft_run();              // process the data in the fft
//  fft_mag_log();          // take the output of the fft
////  Serial.println("Start");
//
//  if(fft_log_out[25] > 60 && fft_log_out[26] > 60){
//    return 1; // 7k
//  } 
//  else if(fft_log_out[25] > 60 && fft_log_out[26] > 60){
//    return 2; // 12k
//  }
//  else if(fft_log_out[25] > 60 && fft_log_out[26] > 60){
//    return 3; // 17k
//  }
//  else {
//    return 0; // no treasure
//  }
//
//  
//}


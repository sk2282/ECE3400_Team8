#include <avr/interrupt.h>
#include <stdlib.h>

unsigned char treasureInterrupt() {
  if (triggered) {
    triggered = false;
    Serial.println("triggered");
    Serial.println(period);
  }
//  Serial.println(period);

  if (1/period <= 1/100 && 1/period >= 1/200) {
    treas = 1;
    Serial.println("7k 7k 7k 7k 7k 7k 7k 7k 7k 7k");
  }
  else if (1/period <= 1/10 && 1/period > 1/50) {
    treas = 2;
    Serial.println("12k 12k 12k 12k 12k 12k 12k 12k");
  }
}



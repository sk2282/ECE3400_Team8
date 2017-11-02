# Milestone 2: Treasure and Wall Detection

## Objective:
The goal of this milestone is to implement treasure detection at three frequencies (7kHz, 12kHz, 17kHz) and add wall detection to our robot by using IR sensors.

## Treasure Detection:
* To implement treasure detection, we first built a non-inverting amplifier for the phototransistor.
* To do this we used a [LM-358AN Op Amp IC](http://www.ti.com/lit/ds/symlink/lm158-n.pdf)
* The schematic for this circuit is pictured below  

 <img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Milestone2/Treasure_detection_circuit_diagram.png?raw=true" height="300" />  

* We first tested the amplifier with the function generator. The results can be seen below  

<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Milestone2/100_1_noninverting_FG.bmp?raw=true" height="300" />  

* When we first tested the circuit using the phototransistor we forgot to include the pull down resistor so it did not work properly  
* Once we added the resistor, we were able to amplify the signal
* The FFT data for this is pictured below  

<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Milestone2/FFTOutput.PNG?raw=true" height="300" />

#### 7kHz From 1.5" Away:
<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Milestone2/7kHz_15inAway.bmp?raw=true" height="300" />  

#### 12kHz From 2" Away:
<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Milestone2/12kHz_2inAway.bmp?raw=true" height="300" />   

#### 17kHz From 2" Away:
<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Milestone2/17kHz_2inAway.bmp?raw=true" height="300" />   

* The amplifier gave us a gain of about 4  
* Below is the code we used to identify the frequencies  
* We checked the bins and compared their averages so if there was a maximum, the program would identify the frequency  

```c
 while(1) {     // reduces jitter
    cli();        // UDRE interrupt slows this way down on arduino1.0
    for (int i = 0 ; i < 512 ; i += 2) {      // save 256 samples
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
    /*
    7kHz: [44,49]
    12kHz: [78,82]
    17kHz: [112,116]
    */
    int max_7k = max_in_range(44,49);
    int max_12k = max_in_range(78,82);
    int max_17k = max_in_range(112,116);
    int RATIO_THRESH = 2.5;

    if (max_7k/30 > RATIO_THRESH) {
      Serial.println("7k 7k 7k 7k 7k 7k 7k 7k 7k 7k 7k 7k 7k 7k 7k 7k 7k");
    }
    else if (max_12k/30 > RATIO_THRESH) {
      Serial.println("12k   12k   12k   12k   12k   12k   12k   12k   12k");
    }
    else if (max_17k/30 > RATIO_THRESH) {
      Serial.println("17k     17k     17k     17k     17k     17k     17k");
    }
    else {
      Serial.println("No Signal");
    }   
  }
```

[The final circuit with amplifier was able to detect each frequency from around 2 inches away](https://youtu.be/L_e-veB9L3M)


## Wall Detection:
* We first tested three IR sensors:  
    * [Short range IR](http://www.sharp-world.com/products/device/lineup/data/pdf/datasheet/gp2y0a41sk_e.pdf)  
    * [Regular IR](https://www.sparkfun.com/datasheets/Components/GP2Y0A21YK.pdf)  
    * [Long range IR](https://www.sparkfun.com/datasheets/Sensors/Infrared/gp2y0a02yk_e.pdf)  
* We connected the IR sensors to an anolog pin on the Arduino and used analogRead() to obtain the data from the sensors
* We then printed readings from the sensors at three different distances from a wall: 2, 6, and 12 inches  
	* The results from this test is displayed in a table below
    * We determined which IR sensors would work best for our robot, prioritizing the best range for the distances that our robot would interact with  
    * We decided to use two short range sensors on the sides and one regular sensor on the front  

    | IR Sensor| Distance | Arduino Reading |
    | -------- | :--------: | :---------------: |
    | Long Range| 2" | 1000+ |
    | Long Range | 6" |500 - 550 |
    | Long Range | 12" |370 - 380 |
    | Regular | 2" | 620 - 630 |
    | Regular | 6" | 310 - 330 |
    | Regular | 12" | 170 - 190 |
    | Short Range | 2" | 390 - 405 |
    | Short Range |6" |130 - 170 |
    | Short Range | 12" | 60 - 90 |

* We wrote some code to test wall detection  
    * To test the implementation, we mounted one short range sensor on the robot's right side  
    * [The robot should follow a straight line until the sensor detects a wall and stop when the wall is detected](https://youtu.be/_vbiJvubCpY)

```c

void loop() {

  // go straight when threshold has not been reached
  while (analogRead(wallRightSide) <= threshSide) {
    int lRead = analogRead(leftLine);
    int rRead = analogRead(rightLine);
    int lwRead = analogRead(leftWide);
    int rwRead = analogRead(rightWide);

    if(lRead<=thresh && rRead<=thresh){     // stop
      left.write(90);
      right.write(90);
    }
    else{
      if(lRead<thresh){  // left side is out of line
        left.write(170);
        right.write(89);
      }
      else if(rRead<thresh){   // right side is out of line
        left.write(91);
        right.write(10);
      }
      else{     // go straight
        left.write(100);
        right.write(80);
      }
    }
  }

//   else stop when wall is detected
  left.write(90);
  right.write(90);

}
```

## Final Robot of Milestone 2:
<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Milestone2/milestone2robot.jpg?raw=true" height="300" />

## Update 10/28/17
We added a capacitor to the treasure detection circuit to remove DC bias from the signal.  This way, we could increase the gain and thereby increase the range of the treasure sensor.

<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Milestone2/Treasure_detection_circuit_diagram_NEW.png?raw=true" height="300" />

Now, the gain is about 22, and [the circuit can detect the treasure up to 9 inches away](https://www.youtube.com/watch?v=mYrdaRs9rtg).

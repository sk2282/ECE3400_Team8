# Lab 2: Analog Circuitry and FFTs

## Objective:
The objective of this lab was to test and familiarize ourselves with the sensors and signal processing needed for our robot to detect the acoustic and optical signals. We split into two subteams, one that worked with a microphone circuit to detect a 660 Hz whistle and another to work with an IR sensor to detect a treasure blinking at different frequencies. Both subteams used the Arduino Open Music Lab FFT library to process the data given by the sensors and create a filter allowing us to analyze the data.

## Team Division:
* Audio: Serena Krech, Alice Song, Victoria Tu
* Treasure: Meghan Chen, Rohit Krishnakumar, Michael Yee

## Audio Team:
### Materials used:
* Arduino Uno
* Electret microphone
* 1 µF capacitor
* 300 Ω resistors
* ~3 kΩ resistor

### Procedure:
1. Read over FFT library
2. Tested an example using function generator at 660Hz and other frequencies
3. Used single mic - tested with clapping and a tone generator
4. Build an amplifier (2)
5. Switched to adafruit mic - built in amplification
6. Tested mic at different distances

#### 1. Read Over FFT Library:
* We read [documentation](http://www.atmel.com/Images/Atmel-42735-8-bit-AVR-Microcontroller-ATmega328-328P_Datasheet.pdf) about the FFT library
* We used fft_adc_serial as an example to see how the adc worked as well as fourier transforms

#### 2. Tested Example Code fft_adc_serial:
* Initially, we ran the code by using just the function generator and Arduino without the microphone [code snippet]
* fft_adc_serial saves a total of 256 data points because even though the for loop is  i<512, it increments i by 2 and sets the odd bins to zero. After all the data is taken, it is reordered and processed in the fft
* We set the function generator at 660Hz and 1.5Vpp with an offset of 750mV  
<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Lab2/signal_generator.JPG?raw=true" height="300" />
* We used the oscilloscope to verify our implementation  
<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Lab2/amp4.bmp?raw=true" height="300" />
* We plotted the data generated from the code in Excel
* We repeated the process with different frequency values (multiples of 660Hz)  
<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Lab2/lab2_frequencyRange.PNG?raw=true" height="300" />
* The plot illustrates reasonable results, disregarding the first few points

#### 3. Testing with Microphone #1:
* We then built a circuit to connect the microphone to the Arduino
* We tested the FFT with a single microphone without any amplifying
* We used a tone generator app (Function Generator) to generate 660Hz for the microphone
* The results shown by the oscilloscope indicate a response, though the waveform amplitude was relatively small  
<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Lab2/oscilloscope.JPG?raw=true" height="300" />
* We also tested the microphone by clapping to see if the oscilloscope output reflected the change in sound

#### 4. Building Amplifier #1:
* We first attempted to build a simple non-inverting amplifier for our microphone
* We used resistance values of 1000Ω and 10kΩ in order to achieve a gain of 10

#### 5. Using New Microphone:
* After attempting to build our own amplifier, we tried using [Adafruit’s Electret Microphone Amplifier with Adjustable Gain](https://www.adafruit.com/product/1063). From the [datasheet](https://cdn-shop.adafruit.com/datasheets/MAX4465-MAX4469.pdf) we learned that the board had a small trimmer potentiometer that we could adjust using a screwdriver. The potentiometer could adjust the gain from 25 times the original up to 125 times the original. The circuit that supports the op amp can be seen below.  
<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Lab2/lab2MicAmplifier.PNG?raw=true" height="300" />
* In the graph below, the dark light blue line represents the output from the function generator at 660 Hz. The green line represents the output from the Adafruit microphone. The peak in bin five is the 660Hz Tone. This measurement was taken when the tone was played very closely to the microphone. When played further away, the dark blue line, the peak in bin five was less obvious, but still there. For this reason, we may attempt building another amplifier or filter for the circuit later on.  
<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Lab2/lab2_zomedIn.PNG?raw=true" height="300" />

#### 6. Testing Microphone at Different Distances:
* We also tested our circuit by placing the microphone at different distances to see how it affected our results
* We noticed that the tone was detected correctly, but the amplitude was much smaller (refer to graph above)

## Treasure Team:
### Materials used:
* Arduino Uno
* IR receiver
* 300 Ω resistors
* 2 kΩ resistor
* Treasure board
* Solderless breadboard

### Procedure:
1. Read over FFT library documentation
2. Assemble circuit with phototransistor
3. Test frequency adjustments of treasure board
4. Test IR sensors
5.
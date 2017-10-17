# Lab 3: FPGA

## Objective:
The objective of this lab is to work with an FPGA to begin the monitor display for the final robot as well as having the robot generate a "tune" using at least 3 tones.

## Team Division:
* Graphics: Rohit Krishnakumar, Alice Song, Victoria Tu
* Audio: Meghan Chen, Serena Krech, Michael Yee

## Graphics Team:
### Materials Used:
* FPGA
* VGA switch
* Monitor
* Arduino
* Resistors: 1.7kOhms and 3.3kOhms

### Procedure:
1. Download example code on the FPGA
2. Modify code to display a 2x2 grid
3. Modify code to change grid color depending from the two switches

#### 1. Download example code on the FPGA:
* Used VGA connector to connect the FPGA GPIO pins to the VGA switch
* Example code showed green screen on monitor and flashed green LED

<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Lab3/GraphicsGreenScreen.jpg?raw=true" height="300" />

* Modified code to display a different color on the monitor (red) 8'b111_000_00
* Drew a green square on a yellow background on the display 

<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Lab3/GraphicsSquare.jpg?raw=true" height="300" />



#### 2. Modify code to display a 2x2 grid:
* Created a 2x2 register array with each value as 8 bits called grid_array which stores the colors
* Check which grid a pixel is in and assign the grid whichever color corresponds to it in grid_array
* Set PIXEL_COLOR to the corresponding color in grid_array depending on what grid_coord_x and grid_coord_y are (00, 01, 10, 11) 

```v
	 	//2-by-2 array of bits
		reg [7:0] grid_array [1:0][1:0]; //[rows][columns]
		reg [1:0] grid_coord_x; //Index x into the array
		reg [1:0] grid_coord_y; //Index y into the array
		// current highlighted square
		 wire highlighted_x;
		 wire highlighted_y;	 
		//Switch input through GPIO pins
		 assign highlighted_x = GPIO_0_D[33];
		 assign highlighted_y = GPIO_0_D[31];
```

<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Lab3/BothGrids.png?raw=true" height="300" />

* Set PIXEL_COLOR to background color if pixel is not within the 2x2 grids


#### 3. Modify code to change grid color from the two switches:
* Use highlighted_x and highlighted_y to modify the colors in grid_array

```v
		always @ (*) begin
			if (highlighted_x==0 && highlighted_y==0) begin
				grid_array[0][0]<=8'b111_000_00;
				grid_array[0][1]<=8'b000_111_00;
				grid_array[1][0]<=8'b000_111_00;
				grid_array[1][1]<=8'b000_111_00;
			end
			if (highlighted_x==0 && highlighted_y==1) begin
				grid_array[0][0]<=8'b000_111_00;
				grid_array[0][1]<=8'b111_000_00;
				grid_array[1][0]<=8'b000_111_00;
				grid_array[1][1]<=8'b000_111_00;
			end
			if (highlighted_x==1 && highlighted_y==0) begin
				// etc... not shown for sake of briefness
			end
			if (highlighted_x==1 && highlighted_y==1) begin
				// etc
			end
		end
```

* First tested this by manually changing values of highlighted_x and highlighted_y
* Next, we wired up a circuit connecting the FPGA to an Arduino with 2 switches so that toggling the switches would modify the grid on the VGA display by setting highlighted_x and y based on these switches
* We wrote a simple Arduino sketch to output 5V when the switch is 1 and 0V when the switch is 0

```c
int readSwitch1 = 11;
int writeSwitch1 = 10;
int readSwitch2 = 2;
int writeSwitch2 = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(readSwitch1, INPUT);
  pinMode(writeSwitch1, OUTPUT);
  pinMode(readSwitch2, INPUT);
  pinMode(writeSwitch2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(readSwitch1) == 1) {
    digitalWrite(writeSwitch1, HIGH);
  }
  else if (digitalRead(readSwitch1) == 0) {
    digitalWrite(writeSwitch1, LOW);
  }
  if (digitalRead(readSwitch2) == 1) {
    digitalWrite(writeSwitch2, HIGH);
  }
  else if (digitalRead(readSwitch2) == 0) {
    digitalWrite(writeSwitch2, LOW);
  }

}
```


* Before testing the code, we first tested the voltage divider and two switches with a multimeter to verify our circuit
* The switch tells the arduino what to output which is then sent through the voltage divider and connected to the FPGA to set the highlighted_x and highlighted_y values. 
* Initially we didn’t ground everything properly, so our display was a bit strange, but once we fixed that our [screen](https://youtu.be/8U0nGZCbZIM) showed the highlighted square changing grids when the switches were toggled.


## Audio Team:
### Materials Used:
* FPGA
* Arduino
* Lab Speaker
* Stereo Phone Jack Socket
* 8-bit R2R DAC

### Procedure:
1. Generate and play a square wave of a desired frequency
2. Generate a more complicated waveform and play sound using the 8-bit DAC
3. Turn on/off your sound with an enable signal
4. Make a tune with at least three frequencies that plays when you receive a done signal from the Arduino

#### 1. Generate and play a square wave of a desired frequency
This was done by using one GPIO pin. We toggled this pin high and low (0 and 1) based on a clock input. We chose to to create a 1kHz Square wave. The FPGA’s clock runs at 50MHz and the example code showed us how to set up a 25MHz clock by toggling a variable every other time. We used the 25MHz clock and used a clock divider to get our desired frequency and set up a 1kHz clock.

```verilog
// Local parameter
localparam CLKDIVIDER_1k = 25000000/1000;

// Sound variables
reg square_1k;                    
assign GPIO_0_D[7:0] = signal;
reg [15:0] counter;

// Sound state machine
always @ (posedge CLOCK_25) begin
  if (counter == 0) begin
    counter    <= CLKDIVIDER_1k - 1; 
    square_1k <= ~square_1k;   
  end
  else begin
    counter    <= counter - 1;
    square_1k <= square_1k;
  end
end
```

Above is the code we used to create the square wave. Every time a change was detected in the 1kHz clock, the output would be toggled so a square wave would be generated. Pictured below is our waveform. 

<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Lab3/1kHz_square_wave.bmp?raw=true" height="300" />

#### 2. Generate a more complicated waveform and play sound using the 8-bit DAC
For a more complicated waveform, we chose to make a 1kHz  triangle wave. To do this we set up an 8 bit output signal and started at 0. Then when we reached a peak, we decremented back to zero and started again. The code and waveform for this is pictured below. 

```verilog
// 1000 Hz square wave
    localparam CLKDIVIDER_1k = 25000000/1000;

    reg square_1k;
	 reg [7:0] signal;
	 assign GPIO_0_D[7:0] = signal;
	 reg [15:0] counter;
	 
	 always @(posedge CLOCK_25) begin
		if (counter == 0)
			begin
			counter <= CLKDIVIDER_1k - 1;
			signal <= signal + 1;
			end
		else if (counter <= CLKDIVIDER_1k / 2)
			begin
			counter <= counter - 1;
			signal <= signal - 1;
			end
		else
			begin
			counter <= counter - 1;
			signal <= signal + 1;
			end
    end
```

<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Lab3/1kHz_triangle_wave.bmp?raw=true" height="300" />

The Digital to Analog Converter (DAC) we used has 8 inputs. Each of these correspond to a bit. The DAC takes these bits and creates an 8 bit analog signal, which is then output through one pin as a varying voltage.

<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Lab3/DAC.jpg?raw=true" height="300" />

This voltage is connected to the input to the audio jack, which  in turn makes the speakers play.

#### 3. Turn on/off your sound with an enable signal


#### 4. Make a tune with at least three frequencies that plays when you receive a done signal from the Arduino


# Lab 3: FPGA

## Objective:

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

<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Lab3/GraphicsGreenScreen.HEIC?raw=true" height="300" />

* Modified code to display a different color on the monitor (red) 8'b111_000_00
* Drew a green square on a yellow background on the display 

<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Lab3/GraphicsSquare.HEIC?raw=true" height="300" />



#### 2. Modify code to display a 2x2 grid:
* Created a 2x2 register array with each value as 8 bits called grid_array which stores the colors
* Check which grid a pixel is in and assign the grid whichever color corresponds to it in grid_array
* Set PIXEL_COLOR to the corresponding color in grid_array depending on what grid_coord_x and grid_coord_y are (00, 01, 10, 11) 

```c
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
* First tested this by manually changing values of highlighted_x and highlighted_y
* Next, we wired up a circuit connecting the FPGA to an Arduino with 2 switches so that toggling the switches would modify the grid on the VGA display by setting highlighted_x and y based on these switches
* We wrote a simple Arduino sketch to output 5V when the switch is 1 and 0V when the switch is 0



* Before testing the code, we first tested the voltage divider and two switches with a multimeter to verify our circuit
* The switch tells the arduino what to output which is then sent through the voltage divider and connected to the FPGA to set the highlighted_x and highlighted_y values. 
* Initially we didn’t ground everything properly, so our display was a bit strange, but once we fixed that our [screen] (https://youtu.be/8U0nGZCbZIM) showed the highlighted square changing grids when the switches were toggled.



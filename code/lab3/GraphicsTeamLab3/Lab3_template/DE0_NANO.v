//=======================================================
// ECE3400 Fall 2017
// Lab 3: Template top-level module
//
// Top-level skeleton from Terasic
// Modified by Claire Chen for ECE3400 Fall 2017
//=======================================================

`define ONE_SEC 25000000

module DE0_NANO(

	//////////// CLOCK //////////
	CLOCK_50,

	//////////// LED //////////
	LED,

	//////////// KEY //////////
	KEY,

	//////////// SW //////////
	SW,

	//////////// GPIO_0, GPIO_0 connect to GPIO Default //////////
	GPIO_0_D,
	GPIO_0_IN,

	//////////// GPIO_0, GPIO_1 connect to GPIO Default //////////
	GPIO_1_D,
	GPIO_1_IN,
);

	 //=======================================================
	 //  PARAMETER declarations
	 //=======================================================

	 localparam ONE_SEC = 25000000; // one second in 25MHz clock cycles
	 
	 //=======================================================
	 //  PORT declarations
	 //=======================================================

	 //////////// CLOCK //////////
	 input 		          		CLOCK_50;

	 //////////// LED //////////
	 output		     [7:0]		LED;

	 /////////// KEY //////////
	 input 		     [1:0]		KEY;

	 //////////// SW //////////
	 input 		     [3:0]		SW;

	 //////////// GPIO_0, GPIO_0 connect to GPIO Default //////////
	 inout 		    [33:0]		GPIO_0_D;
	 input 		     [1:0]		GPIO_0_IN;

	 //////////// GPIO_0, GPIO_1 connect to GPIO Default //////////
	 inout 		    [33:0]		GPIO_1_D;
	 input 		     [1:0]		GPIO_1_IN;

    //=======================================================
    //  REG/WIRE declarations
    //=======================================================
    reg         CLOCK_25;
    wire        reset; // active high reset signal 

    wire [9:0]  PIXEL_COORD_X; // current x-coord from VGA driver
    wire [9:0]  PIXEL_COORD_Y; // current y-coord from VGA driver
    reg [7:0]  PIXEL_COLOR;   // input 8-bit pixel color for current coords
	 
	 reg [24:0] led_counter; // timer to keep track of when to toggle LED
	 reg 			led_state;   // 1 is on, 0 is off
	 
    // Module outputs coordinates of next pixel to be written onto screen
    VGA_DRIVER driver(
		  .RESET(reset),
        .CLOCK(CLOCK_25),
        .PIXEL_COLOR_IN(PIXEL_COLOR),
        .PIXEL_X(PIXEL_COORD_X),
        .PIXEL_Y(PIXEL_COORD_Y),
        .PIXEL_COLOR_OUT({GPIO_0_D[9],GPIO_0_D[11],GPIO_0_D[13],GPIO_0_D[15],GPIO_0_D[17],GPIO_0_D[19],GPIO_0_D[21],GPIO_0_D[23]}),
        .H_SYNC_NEG(GPIO_0_D[7]),
        .V_SYNC_NEG(GPIO_0_D[5])
    );
	 
	 assign reset = ~KEY[0]; // reset when KEY0 is pressed
	 
	
	 assign LED[0] = led_state;
	 
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
		 
		 
    //=======================================================
    //  Structural coding
    //=======================================================
		// always @ (*) begin 
		//	 grid_array[0][0]<=8'b111_000_00;
			// grid_array[0][1]<=8'b000_111_00;
  			//grid_array[1][0]<=8'b000_111_00;
			// grid_array[1][1]<=8'b000_111_00;
		 //end
		 
		 always @ (*) begin 
		  if(PIXEL_COORD_X <= 10'd50 && PIXEL_COORD_Y <= 10'd50) begin
			 grid_coord_x[0]<=0;
			 grid_coord_y[0]<=0;
			 grid_coord_x[1]<=0;
			 grid_coord_y[1]<=0;
		  end
		  else if(PIXEL_COORD_X > 10'd50 && PIXEL_COORD_X <= 10'd100 && PIXEL_COORD_Y <= 10'd50) begin
			 grid_coord_x[0]<=1;
			 grid_coord_y[0]<=0;
			 grid_coord_x[1]<=0;
			 grid_coord_y[1]<=0;
		  end
		 else if(PIXEL_COORD_Y > 10'd50 && PIXEL_COORD_Y <= 10'd100 && PIXEL_COORD_X <= 10'd50) begin
			 grid_coord_x[0]<=0;
			 grid_coord_y[0]<=1;
			 grid_coord_x[1]<=0;
			 grid_coord_y[1]<=0;
		  end
		  else if(PIXEL_COORD_X > 10'd50 && PIXEL_COORD_X <= 10'd100 && PIXEL_COORD_Y > 10'd50 && PIXEL_COORD_Y <= 10'd100) begin
			 grid_coord_x[0]<=1;
			 grid_coord_y[0]<=1;
			 grid_coord_x[1]<=0;
			 grid_coord_y[1]<=0;
		  end
		  else begin
			 grid_coord_x[1]<=1;
			 grid_coord_y[1]<=1;
		  end
		end
		
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
				grid_array[0][0]<=8'b000_111_00;
				grid_array[0][1]<=8'b000_111_00;
				grid_array[1][0]<=8'b111_000_00;
				grid_array[1][1]<=8'b000_111_00;
			end
			if (highlighted_x==1 && highlighted_y==1) begin
				grid_array[0][0]<=8'b000_111_00;
				grid_array[0][1]<=8'b000_111_00;
				grid_array[1][0]<=8'b000_111_00;
				grid_array[1][1]<=8'b111_000_00;
			end
		end
		
		always @ (*) begin
			if (grid_coord_x[1]==0 && grid_coord_y[1]==0)begin
			
				if(grid_coord_x[0]==0 && grid_coord_y[0]==0) begin
						PIXEL_COLOR<=grid_array[0][0];
				end
				
				else if(grid_coord_x[0]==1 && grid_coord_y[0]==0) begin
						PIXEL_COLOR<=grid_array[1][0];
				end
				
				else if(grid_coord_x[0]==0 && grid_coord_y[0]==1) begin
						PIXEL_COLOR<=grid_array[0][1];
				end
				
				else if(grid_coord_x[0]==1 && grid_coord_y[0]==1) begin
						PIXEL_COLOR<=grid_array[1][1];
				end
			end
			else if (grid_coord_x[1]==1 && grid_coord_y[1]==1) begin
						PIXEL_COLOR<=8'b000_000_11;
			end
		end
	 
	 // Generate 25MHz clock for VGA, FPGA has 50 MHz clock
    always @ (posedge CLOCK_50) begin
        CLOCK_25 <= ~CLOCK_25; 
    end // always @ (posedge CLOCK_50)
	
	 // Simple state machine to toggle LED0 every one second
	 always @ (posedge CLOCK_25) begin
		  if (reset) begin
				led_state   <= 1'b0;
				led_counter <= 25'b0;
		  end
		  
		  if (led_counter == ONE_SEC) begin
				led_state   <= ~led_state;
				led_counter <= 25'b0;
		  end
		  else begin	
				led_state   <= led_state;
				led_counter <= led_counter + 25'b1;
		  end // always @ (posedge CLOCK_25)
	 end
	 

endmodule

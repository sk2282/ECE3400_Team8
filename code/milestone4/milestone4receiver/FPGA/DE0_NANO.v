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
	 reg			 CLK_1s;
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
		reg [7:0] grid_array [8:0][10:0]; //[columns][rows]
		reg [9:0] grid_coord_x; //Index x into the array
		reg [9:0] grid_coord_y; //Index y into the array
		// current highlighted square
		 wire [1:0] highlighted_x;
		 wire [2:0] highlighted_y;	 
		//Switch input through GPIO pins
		 assign highlighted_x = GPIO_0_D[33:32];
		 assign highlighted_y = GPIO_0_D[31:29];
		 assign done = GPIO_0_D[28];
		 assign treasure = GPIO_0_D[27:26];
		 assign walls = GPIO_0_D[25:22];
		 
    //=======================================================
    //  Structural coding
    //=======================================================
		 
		 localparam [9:0] GRID_SIZE = 10'd100;
		 reg [9:0] x_tmp;
		 reg [9:0] y_tmp;
		 always @ (*) begin
			grid_coord_x = 0;
			grid_coord_y = 0;
			x_tmp = PIXEL_COORD_X;
			y_tmp = PIXEL_COORD_Y;
			while (grid_coord_x <= 4'd8 && x_tmp >= GRID_SIZE) begin
				grid_coord_x = grid_coord_x + 4'd1;
				x_tmp = x_tmp - GRID_SIZE;
			end
			while (grid_coord_y <= 4'd10 && y_tmp >= GRID_SIZE) begin
				grid_coord_y = grid_coord_y + 4'd1;
				y_tmp = y_tmp - GRID_SIZE;
			end
		 end
		 		
		wire [7:0] RED = 8'b111_000_00; // current location
		wire [7:0] GREEN = 8'b000_111_00; // visited
		wire [7:0] BLUE = 8'b000_000_11; // unexplorable
		wire [7:0] BLACK = 8'b000_000_00; // not visited/not a wall
		wire [7:0] YELLOW = 8'b111_111_00; // treasure 7k
		wire [7:0] ORANGE = 8'b111_011_00; // treasure 12k
		wire [7:0] PINK = 8'b111_001_10; // treasure 17k
		wire [7:0] WHITE = 8'b111_111_11; // walls
		
		reg [2:0] x;
		reg [2:0] y;
		
		reg [1:0] xmarks [3:0][4:0];

		reg [2:0] last_coord_x;
		reg [2:0] last_coord_y;
		
		initial
		begin
			xmarks[0][0] = 2'd0;
			xmarks[0][1] = 2'd0;
			xmarks[0][2] = 2'd0;
			xmarks[0][3] = 2'd0;
			xmarks[0][4] = 2'd0;
			xmarks[1][0] = 2'd0;
			xmarks[1][1] = 2'd0;
			xmarks[1][2] = 2'd0;
			xmarks[1][3] = 2'd0;
			xmarks[1][4] = 2'd0;
			xmarks[2][0] = 2'd0;
			xmarks[2][1] = 2'd0;
			xmarks[2][2] = 2'd0;
			xmarks[2][3] = 2'd0;
			xmarks[2][4] = 2'd0;
			xmarks[3][0] = 2'd0;
			xmarks[3][1] = 2'd0;
			xmarks[3][2] = 2'd0;
			xmarks[3][3] = 2'd0;
			xmarks[3][4] = 2'd0;
		end

		always @ (highlighted_x, highlighted_y) begin

			// treasure and prev coordinate update
			if (xmarks[last_coord_x >> 1][last_coord_y >> 1] == 2'd1) begin
				grid_array[last_coord_x][last_coord_y] <= YELLOW; // 7k treasure
			end
			else if (xmarks[last_coord_x >> 1][last_coord_y >> 1] == 2'd2) begin
				grid_array[last_coord_x][last_coord_y] <= ORANGE; // 12k treasure
			end
			else if (xmarks[last_coord_x >> 1][last_coord_y >> 1] == 2'd3) begin
				grid_array[last_coord_x][last_coord_y] <= PINK; // 17k treasure
			end
			else begin
				grid_array[last_coord_x][last_coord_y] <= GREEN; // no treasure
			end

			// wall detection update
			if (walls[3]) begin
				grid_array[highlighted_x][highlighted_y-1] <= WHITE;
			end
			else begin
				grid_array[highlighted_x][highlighted_y-1] <= BLACK;
			end
			if (walls[2]) begin
				grid_array[highlighted_x-1][highlighted_y] <= WHITE;
			end
			else begin
				grid_array[highlighted_x-1][highlighted_y] <= BLACK;
			end
			if (walls[1]) begin
				grid_array[highlighted_x][highlighted_y+1] <= WHITE;
			end
			else begin
				grid_array[highlighted_x][highlighted_y+1] <= BLACK;
			end
			if (walls[0]) begin
				grid_array[highlighted_x+1][highlighted_y] <= WHITE;
			end
			else begin
				grid_array[highlighted_x+1][highlighted_y] <= BLACK;
			end

			// update treasure tracker
			xmarks[highlighted_x >> 1][highlighted_y >> 1] <= treasure;
			// update prev coordinate tracker
			last_coord_x = highlighted_x;
			last_coord_y = highlighted_y;

			// current location
			grid_array[highlighted_x][highlighted_y] <= RED;

		end

		always @ (done) begin

			// play sound

		end
		
		
//		always @ (posedge CLK_1s) begin
//			for (x=3'b0; x<=3'd3; x=x+3'b1) begin
//				for (y=3'b0; y <= 3'd4; y=y+3'b1) begin
//					if (x == highlighted_x && y == highlighted_y) begin
//						grid_array[x][y] <= RED;
//						visited[x][y] <= 1'b0;
//					end
//					else if (visited[x][y] == 1'b0) begin
//						grid_array[x][y] <= GREEN;
//						visited[x][y] <= visited[x][y];
//					end
//					else if (data == 2'b11) begin
//						grid_array[x][y] <= YELLOW;
//						visited[x][y] <= 1'b0;
//					end
//					else begin
//						grid_array[x][y] <= BLACK;
//						visited[x][y] <= visited[x][y];
//					end
//				end
//			end
//			//grid_array[highlighted_x][highlighted_y] = RED;
//			//grid_array[last_coord_x][last_coord_y] = GREEN;
//		end
		
		
		always @ (grid_coord_x,grid_coord_y) begin
			if (grid_coord_x <= 10'd8 && grid_coord_y <= 10'd10)begin
				PIXEL_COLOR <= grid_array[grid_coord_x][grid_coord_y];
			end
			else begin
				PIXEL_COLOR<=BLUE;
			end
		end
	 
	 
	 
	 // Generate 25MHz clock for VGA, FPGA has 50 MHz clock
    always @ (posedge CLOCK_50) begin
        CLOCK_25 <= ~CLOCK_25; 
    end // always @ (posedge CLOCK_50)
	
	localparam secDiv = 25000000/2;
	 reg [24:0] counter_1s;
	 
	 always @(posedge CLOCK_25) begin
		if(counter_1s == 0) begin
			counter_1s <= secDiv-1;
			CLK_1s <= ~CLK_1s;
		end
		else begin
			counter_1s <= counter_1s - 1;
			CLK_1s <= CLK_1s;
		end
	 end
	
	
//	 // Simple state machine to toggle LED0 every one second
//	 always @ (posedge CLOCK_25) begin
//		  if (reset) begin
//				led_state   <= 1'b0;
//				led_counter <= 25'b0;
//		  end
//		  
//		  if (led_counter == ONE_SEC) begin
//				led_state   <= ~led_state;
//				led_counter <= 25'b0;
//		  end
//		  else begin	
//				led_state   <= led_state;
//				led_counter <= led_counter + 25'b1;
//		  end // always @ (posedge CLOCK_25)
//	 end
	 

endmodule

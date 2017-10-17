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
    wire [7:0]  PIXEL_COLOR;   // input 8-bit pixel color for current coords
	 
	 reg [24:0] led_counter; // timer to keep track of when to toggle LED
	 reg 			led_state;   // 1 is on, 0 is off
	 
    // Module outputs coordinates of next pixel to be written onto screen
//    VGA_DRIVER driver(
//		  .RESET(reset),
//        .CLOCK(CLOCK_25),
//        .PIXEL_COLOR_IN(PIXEL_COLOR),
//        .PIXEL_X(PIXEL_COORD_X),
//        .PIXEL_Y(PIXEL_COORD_Y),
//        .PIXEL_COLOR_OUT({GPIO_0_D[9],GPIO_0_D[11],GPIO_0_D[13],GPIO_0_D[15],GPIO_0_D[17],GPIO_0_D[19],GPIO_0_D[21],GPIO_0_D[23]}),
//        .H_SYNC_NEG(GPIO_0_D[7]),
//        .V_SYNC_NEG(GPIO_0_D[5])
//    );
	 
	 assign reset = ~KEY[0]; // reset when KEY0 is pressed
	 
	 assign PIXEL_COLOR = 8'b000_111_00; // Green
	 assign LED[0] = led_state;
	 
    //=======================================================
    //  Structural coding
    //=======================================================
 
	 // Generate 25MHz clock for VGA, FPGA has 50 MHz clock
    always @ (posedge CLOCK_50) begin
        CLOCK_25 <= ~CLOCK_25; 
    end // always @ (posedge CLOCK_50)
	 
	 localparam CLKDIVIDER_1k = 25000000/1000/255;
	 localparam CLKDIVIDER_1250 = 25000000/1250/255;
	 localparam CLKDIVIDER_1500 = 25000000/1500/255;
	 reg [7:0] counter_1500;
	 reg [7:0] counter_1250;
	 reg [7:0] counter_1k;
	 reg CLK_1k;
	 reg CLK_1250;
	 reg CLK_1500;
	 
	 localparam secDiv = 25000000/2;
	 reg [24:0] counter_1s;
	 
	 always @(posedge CLOCK_25) begin
		if (counter_1k == 0) begin
		  counter_1k <= CLKDIVIDER_1k - 1;
		  CLK_1k <= ~CLK_1k;
		end
		else begin
			counter_1k <= counter_1k - 1;
			CLK_1k <= CLK_1k;
		end
		if(counter_1s == 0) begin
			counter_1s <= secDiv-1;
			CLK_1s <= ~CLK_1s;
		end
		else begin
			counter_1s <= counter_1s - 1;
			CLK_1s <= CLK_1s;
		end
		if (counter_1250 == 0) begin
			counter_1250 <= CLKDIVIDER_1250 - 1;
			CLK_1250 <= ~CLK_1250;
		end
		else begin
			counter_1250 <= counter_1250 - 1;
			CLK_1250 <= CLK_1250;
		end
		if (counter_1500 == 0) begin
			counter_1500 <= CLKDIVIDER_1500 - 1;
			CLK_1500 <= ~CLK_1500;
		end
		else begin
			counter_1500 <= counter_1500 - 1;
			CLK_1500 <= CLK_1500;
		end
	 end
	 
	 reg [7:0] sin [255:0];
	 reg [7:0] signal;
	 reg [7:0] signal2;
	 reg [7:0] signal3;
	 reg [7:0] counter;
	 reg [7:0] counter2;
	 reg [7:0] counter3;
	 reg [7:0] out;
	 assign GPIO_0_D[7:0] = out;
	 reg complete;
	 
	 always @(soundCount) begin
		if (soundCount == 3'b1) out = signal;
		else if (soundCount == 3'd2) out = signal2;
		else if (soundCount == 3'd3) out = signal3;
		else out = 8'b0;
	 end
	 
	 initial
	 begin
		soundCount <= 3'b0;
		out <= signal;
		counter <= 8'd255;
		sin[0]<=8'd128;
		sin[1]<=8'd134;
		sin[2]<=8'd141;
		sin[3]<=8'd147;
		sin[4]<=8'd153;
		sin[5]<=8'd159;
		sin[6]<=8'd165;
		sin[7]<=8'd171;
		sin[8]<=8'd177;
		sin[9]<=8'd183;
		sin[10]<=8'd189;
		sin[11]<=8'd194;
		sin[12]<=8'd199;
		sin[13]<=8'd205;
		sin[14]<=8'd209;
		sin[15]<=8'd214;
		sin[16]<=8'd219;
		sin[17]<=8'd223;
		sin[18]<=8'd227;
		sin[19]<=8'd231;
		sin[20]<=8'd235;
		sin[21]<=8'd238;
		sin[22]<=8'd241;
		sin[23]<=8'd244;
		sin[24]<=8'd246;
		sin[25]<=8'd249;
		sin[26]<=8'd251;
		sin[27]<=8'd252;
		sin[28]<=8'd254;
		sin[29]<=8'd255;
		sin[30]<=8'd255;
		sin[31]<=8'd255;
		sin[32]<=8'd255;
		sin[33]<=8'd255;
		sin[34]<=8'd255;
		sin[35]<=8'd254;
		sin[36]<=8'd253;
		sin[37]<=8'd252;
		sin[38]<=8'd250;
		sin[39]<=8'd248;
		sin[40]<=8'd246;
		sin[41]<=8'd243;
		sin[42]<=8'd240;
		sin[43]<=8'd237;
		sin[44]<=8'd234;
		sin[45]<=8'd230;
		sin[46]<=8'd226;
		sin[47]<=8'd222;
		sin[48]<=8'd218;
		sin[49]<=8'd213;
		sin[50]<=8'd208;
		sin[51]<=8'd203;
		sin[52]<=8'd198;
		sin[53]<=8'd193;
		sin[54]<=8'd187;
		sin[55]<=8'd181;
		sin[56]<=8'd176;
		sin[57]<=8'd170;
		sin[58]<=8'd164;
		sin[59]<=8'd158;
		sin[60]<=8'd152;
		sin[61]<=8'd145;
		sin[62]<=8'd139;
		sin[63]<=8'd133;
		sin[64]<=8'd126;
		sin[65]<=8'd120;
		sin[66]<=8'd114;
		sin[67]<=8'd108;
		sin[68]<=8'd101;
		sin[69]<=8'd95;
		sin[70]<=8'd89;
		sin[71]<=8'd83;
		sin[72]<=8'd77;
		sin[73]<=8'd72;
		sin[74]<=8'd66;
		sin[75]<=8'd61;
		sin[76]<=8'd55;
		sin[77]<=8'd50;
		sin[78]<=8'd45;
		sin[79]<=8'd41;
		sin[80]<=8'd36;
		sin[81]<=8'd32;
		sin[82]<=8'd28;
		sin[83]<=8'd24;
		sin[84]<=8'd20;
		sin[85]<=8'd17;
		sin[86]<=8'd14;
		sin[87]<=8'd11;
		sin[88]<=8'd9;
		sin[89]<=8'd7;
		sin[90]<=8'd5;
		sin[91]<=8'd3;
		sin[92]<=8'd2;
		sin[93]<=8'd1;
		sin[94]<=8'd1;
		sin[95]<=8'd1;
		sin[96]<=8'd1;
		sin[97]<=8'd1;
		sin[98]<=8'd1;
		sin[99]<=8'd2;
		sin[100]<=8'd3;
		sin[101]<=8'd4;
		sin[102]<=8'd6;
		sin[103]<=8'd8;
		sin[104]<=8'd11;
		sin[105]<=8'd13;
		sin[106]<=8'd16;
		sin[107]<=8'd20;
		sin[108]<=8'd23;
		sin[109]<=8'd27;
		sin[110]<=8'd31;
		sin[111]<=8'd35;
		sin[112]<=8'd39;
		sin[113]<=8'd44;
		sin[114]<=8'd49;
		sin[115]<=8'd54;
		sin[116]<=8'd59;
		sin[117]<=8'd65;
		sin[118]<=8'd70;
		sin[119]<=8'd76;
		sin[120]<=8'd82;
		sin[121]<=8'd88;
		sin[122]<=8'd94;
		sin[123]<=8'd100;
		sin[124]<=8'd106;
		sin[125]<=8'd112;
		sin[126]<=8'd119;
		sin[127]<=8'd125;
		sin[128]<=8'd131;
		sin[129]<=8'd137;
		sin[130]<=8'd144;
		sin[131]<=8'd150;
		sin[132]<=8'd156;
		sin[133]<=8'd162;
		sin[134]<=8'd168;
		sin[135]<=8'd174;
		sin[136]<=8'd180;
		sin[137]<=8'd186;
		sin[138]<=8'd191;
		sin[139]<=8'd197;
		sin[140]<=8'd202;
		sin[141]<=8'd207;
		sin[142]<=8'd212;
		sin[143]<=8'd217;
		sin[144]<=8'd221;
		sin[145]<=8'd225;
		sin[146]<=8'd229;
		sin[147]<=8'd233;
		sin[148]<=8'd236;
		sin[149]<=8'd240;
		sin[150]<=8'd243;
		sin[151]<=8'd245;
		sin[152]<=8'd248;
		sin[153]<=8'd250;
		sin[154]<=8'd252;
		sin[155]<=8'd253;
		sin[156]<=8'd254;
		sin[157]<=8'd255;
		sin[158]<=8'd255;
		sin[159]<=8'd255;
		sin[160]<=8'd255;
		sin[161]<=8'd255;
		sin[162]<=8'd255;
		sin[163]<=8'd254;
		sin[164]<=8'd253;
		sin[165]<=8'd251;
		sin[166]<=8'd249;
		sin[167]<=8'd247;
		sin[168]<=8'd245;
		sin[169]<=8'd242;
		sin[170]<=8'd239;
		sin[171]<=8'd236;
		sin[172]<=8'd232;
		sin[173]<=8'd228;
		sin[174]<=8'd224;
		sin[175]<=8'd220;
		sin[176]<=8'd215;
		sin[177]<=8'd211;
		sin[178]<=8'd206;
		sin[179]<=8'd201;
		sin[180]<=8'd195;
		sin[181]<=8'd190;
		sin[182]<=8'd184;
		sin[183]<=8'd179;
		sin[184]<=8'd173;
		sin[185]<=8'd167;
		sin[186]<=8'd161;
		sin[187]<=8'd155;
		sin[188]<=8'd148;
		sin[189]<=8'd142;
		sin[190]<=8'd136;
		sin[191]<=8'd130;
		sin[192]<=8'd123;
		sin[193]<=8'd117;
		sin[194]<=8'd111;
		sin[195]<=8'd104;
		sin[196]<=8'd98;
		sin[197]<=8'd92;
		sin[198]<=8'd86;
		sin[199]<=8'd80;
		sin[200]<=8'd75;
		sin[201]<=8'd69;
		sin[202]<=8'd63;
		sin[203]<=8'd58;
		sin[204]<=8'd53;
		sin[205]<=8'd48;
		sin[206]<=8'd43;
		sin[207]<=8'd38;
		sin[208]<=8'd34;
		sin[209]<=8'd30;
		sin[210]<=8'd26;
		sin[211]<=8'd22;
		sin[212]<=8'd19;
		sin[213]<=8'd16;
		sin[214]<=8'd13;
		sin[215]<=8'd10;
		sin[216]<=8'd8;
		sin[217]<=8'd6;
		sin[218]<=8'd4;
		sin[219]<=8'd3;
		sin[220]<=8'd2;
		sin[221]<=8'd1;
		sin[222]<=8'd1;
		sin[223]<=8'd1;
		sin[224]<=8'd1;
		sin[225]<=8'd1;
		sin[226]<=8'd1;
		sin[227]<=8'd2;
		sin[228]<=8'd4;
		sin[229]<=8'd5;
		sin[230]<=8'd7;
		sin[231]<=8'd10;
		sin[232]<=8'd12;
		sin[233]<=8'd15;
		sin[234]<=8'd18;
		sin[235]<=8'd21;
		sin[236]<=8'd25;
		sin[237]<=8'd29;
		sin[238]<=8'd33;
		sin[239]<=8'd37;
		sin[240]<=8'd42;
		sin[241]<=8'd47;
		sin[242]<=8'd51;
		sin[243]<=8'd57;
		sin[244]<=8'd62;
		sin[245]<=8'd67;
		sin[246]<=8'd73;
		sin[247]<=8'd79;
		sin[248]<=8'd85;
		sin[249]<=8'd91;
		sin[250]<=8'd97;
		sin[251]<=8'd103;
		sin[252]<=8'd109;
		sin[253]<=8'd115;
		sin[254]<=8'd122;
		sin[255]<=8'd128;
	 end
	 
	 	 
	 always @(posedge CLK_1k)
	 begin
	   if (soundCount == 3'd1) begin
			if (counter > 0)
			begin
				signal <= sin[counter];
				counter <= counter - 1;
			end
			else
			begin
				signal <= 8'd0;
				counter <= 8'd255;
			end
		end
		else begin
			signal <= 8'b0;
			counter <= counter;
		end
	 end
	 
	 always @(posedge CLK_1250)
	 begin
	   if (soundCount == 3'd2) begin
			if (counter2 > 0)
			begin
				signal2 <= sin[counter2];
				counter2 <= counter2 - 1;
			end
			else
			begin
				signal2 <= 8'd0;
				counter2 <= 8'd255;
			end
		end
		else begin
			signal2 <= 8'b0;
			counter2 <= counter2;
		end
	 end
	 
	 always @(posedge CLK_1500)
	 begin
	   if (soundCount == 3'd3) begin
			if (counter3 > 0)
			begin
				signal3 <= sin[counter3];
				counter3 <= counter3 - 1;
			end
			else
			begin
				signal3 <= 8'd0;
				counter3 <= 8'd255;
			end
		end
		else begin
			signal3 <= 8'b0;
			counter3 <= counter3;
		end
	 end
	 
//	 always @(posedge CLK_1k)
//	 begin
//	   if (soundCount == 2'd1) begin
//			if (counter > 0)
//			begin
//				signal <= sin[counter];
//				counter <= counter - 1;
//			end
//			else
//			begin
//				signal <= 8'd0;
//				counter <= 8'd255;
//			end
//		end
//		else begin
//			signal <= 8'b0;
//			counter <= counter;
//		end
//	 end
//	 
//	 always @(posedge CLK_1k)
//	 begin
//	   if (soundCount == 2'd2) begin
//			if (counter > 0)
//			begin
//				signal <= sin[counter];
//				counter <= counter - 1;
//			end
//			else
//			begin
//				signal <= 8'd0;
//				counter <= 8'd255;
//			end
//		end
//		else begin
//			signal <= 8'b0;
//			counter <= counter;
//		end
//	 end
	 
	 reg [9:0] oneSec;
	 reg CLK_1s;
	 reg [2:0] soundCount;
	 
	 // Sets the counds for each sound to play for one second
//	 always @(posedge CLK_1k)
//	 begin
//		if(reset) begin
//			oneSec = 10'b0;
//			CLK_1s = 0;
//		end
//		else if (oneSec < 10'd1000 && soundCount < 4) begin
//			oneSec = oneSec + 1;
//			CLK_1s = CLK_1s;
//		end
//		else begin
//			oneSec = 10'b0;
//			CLK_1s = ~CLK_1s;
//		end
//	 end
	 
	 always @(posedge CLK_1s) begin
		if (GPIO_0_IN[0] || (soundCount > 3'b0 && soundCount <= 3'd3)) begin
			if (soundCount <= 3'd3) begin
				soundCount <= soundCount + 1;
			end
			else begin
				soundCount <= soundCount;
			end
		end
		
		else begin
			soundCount <= 3'b0;
		end
	 end
	 
	 // 1000 Hz square wave
//    localparam CLKDIVIDER_1k = 25000000/1000;
//
//    reg square_1k;
//	 reg [7:0] signal;
//	 assign GPIO_0_D[7:0] = signal;
//	 reg [15:0] counter;
//	 
//	 always @(posedge CLOCK_25) begin
//		if (counter == 0)
//			begin
//			counter <= CLKDIVIDER_1k - 1;
//			signal <= signal + 1;
//			end
//		else if (counter <= CLKDIVIDER_1k / 2)
//			begin
//			counter <= counter - 1;
//			signal <= signal - 1;
//			end
//		else
//			begin
//			counter <= counter - 1;
//			signal <= signal + 1;
//			end
//    end


	
	 /*// Simple state machine to toggle LED0 every one second
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
	 end*/
	 

endmodule

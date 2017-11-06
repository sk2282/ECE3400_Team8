function [new] = detectWalls( r, c, detected_wall_loc, wall_loc)
% Updates walls as seen by the robot
    new = detected_wall_loc;
    wall_bin_real = de2bi(wall_loc(r,c), 4, 'right-msb');
    wall_bin_detected = de2bi(detected_wall_loc(r,c), 4, 'right-msb');
    
    if (wall_bin_real(1) == 1 && wall_bin_detected(1) == 0)
        new(r,c) = new(r,c) + 1;
        new(r-1,c) = new(r-1,c) + 2;
    end
    
    if (wall_bin_real(2) == 1 && wall_bin_detected(2) == 0)
        new(r,c) = new(r,c) + 2;
        new(r+1,c) = new(r+1,c) + 1;
    end
    
    if (wall_bin_real(3) == 1 && wall_bin_detected(3) == 0)
        new(r,c) = new(r,c) + 4;
        new(r,c+1) = new(r,c+1) + 8;
    end
    
    if (wall_bin_real(4) == 1 && wall_bin_detected(4) == 0)
        new(r,c) = new(r,c) + 8;
        new(r,c-1) = new(r,c-1) + 4;
    end


end


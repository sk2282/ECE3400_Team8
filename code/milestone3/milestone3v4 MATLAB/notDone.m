function notDone = notDone(visited, wall_loc)
% Returns true if the robot is done navigating, false otherwise
    notDone = false;
    for r = 1:5
        for c = 1:4
            wall_bin = de2bi(wall_loc(r,c), 4, 'right-msb');
            if (visited(r,c) == 1)
                if ((wall_bin(1) == 0 && r > 1 && visited(r-1,c) == 0.5) || ...
                     (wall_bin(2) == 0 && r < 5 && visited(r+1,c) == 0.5) || ...
                     (wall_bin(3) == 0 && c < 4 && visited(r,c+1) == 0.5) || ...
                     (wall_bin(4) == 0 && c > 1 && visited(r,c-1) == 0.5))
                    notDone = true;
                end
            end
        end
    end


end


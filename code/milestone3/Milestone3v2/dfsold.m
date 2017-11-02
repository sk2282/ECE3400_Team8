function dfsold(visited, curr_loc, wall_loc)

    s = CStack(); % create stack
    r = 5;
    c = 4;
    loc = 19;
    visited(r,c) = 0.5; % set starting point to "visited"
    curr_loc(r,c) = 0.5;
    s.push(loc); % push first element, figure out numbering later
    
    while (s.size() ~= 0) 
        % get unvisted node from top of stack
        wall_bin = de2bi(wall_loc(r,c), 4, 'right-msb');
        % pick first direction that doesn't have a wall or visited

        if (r > 1 && wall_bin(1) ~= 1 && visited(r-1,c) ~= 0.5) % NORTH wall
            % go north
%             curr_loc(r,c) = 1; % set old to not curr location
            curr_loc(r-1,c) = 0; % set new curr location
            imagesc(curr_loc); % display new current location?
            imagesc(visited);
            pause(0.5);            
            visited(r-1,c) = 0.5; % set new visited
%             curr_loc(r-1,c) = 0.5;
            s.push(loc-5);
            r = r-1;

        elseif (r < 4 && wall_bin(2) ~= 1 && visited(r+1,c) ~= 0.5) % SOUTH wall
            % go south
%             curr_loc(r,c) = 1;
            curr_loc(r+1,c) = 0;
            imagesc(curr_loc);
            imagesc(visited);
            pause(0.5);
            visited(r+1,c) = 0.5;
%             curr_loc(r+1,c) = 0.5;
            s.push(loc+5);
            r = r+1;

        elseif (c<5 && wall_bin(3) ~= 1 && visited(r,c+1) ~= 0.5) % EAST wall
            % go east
%             curr_loc(r,c) = 1;
            curr_loc(r,c+1) = 0;
            imagesc(curr_loc);
            imagesc(visited);
            pause(0.5);
            
            visited(r,c+1) = 0.5;
            s.push(loc+1);
            c = c+1;

        elseif (c>1 && wall_bin(4) ~= 1 && visited(r,c-1) ~= 0.5) % WEST wall
            % go west
%             curr_loc(r,c) = 1;
            curr_loc(r,c-1) = 0;
            imagesc(curr_loc);
            imagesc(visited);
            pause(0.5);
            visited(r,c-1) = 0.5;
            s.push(loc-1);
            c = c-1;

        else
            loc = s.pop();
            % get r, c based on loc
%             [r,c] = getrc(loc); % might be unecessary
            % mark visited
%             visited(r,c) = 0.5;
        end
    end
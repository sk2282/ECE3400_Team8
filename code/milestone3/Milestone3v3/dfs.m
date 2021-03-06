function dfs(visited,curr_loc, wall_loc)

    s = CStack(); % create stack
    r = 5;
    c = 4;
    loc = 19;
	visited(r,c) = 0.5; % set starting point to "visited"
    curr_loc(r,c) = 0.5;
    s.push(loc); % push first element, figure out numbering later
    
    while (s.size() ~= 0 && notDone(visited, wall_loc)) 
        % get unvisted node from top of stack
        wall_bin = de2bi(wall_loc(r,c), 4, 'right-msb');
        % pick first direction that doesn't have a wall or visited
%          %disp (curr_loc(r,c));
%          %disp (loc);
%          %disp (" ");
        %disp(loc); %disp(s.content())
        %disp("")
        if (r > 1 && wall_bin(1) ~= 1 && curr_loc(r-1,c) ~= 0.5) % NORTH wall
            %disp("go north")
%             curr_loc(r,c) = 1; % set old to not curr location
            curr_loc(r-1,c) = 0; % set new curr location
            hold on; imagesc(curr_loc); draw_walls(wall_loc); % %display new current location?
%             hold on; imagesc(visited);
            pause(0.5);
            visited(r-1,c) = 0.5; % set new visited
            curr_loc(r-1,c) = 0.5;
            loc=loc-4;
            s.push(loc);
            r = r-1;

        elseif (r < 5 && wall_bin(2) ~= 1 && curr_loc(r+1,c) ~= 0.5) % SOUTH wall
            %disp("go south")
%             curr_loc(r,c) = 1;
            curr_loc(r+1,c) = 0;
            hold on; imagesc(curr_loc); draw_walls(wall_loc);
            pause(0.5);
            visited(r+1,c) = 0.5;
            curr_loc(r+1,c) = 0.5;
            loc=loc+4;
            s.push(loc);
            r = r+1;

        elseif (c<4 && wall_bin(3) ~= 1 && curr_loc(r,c+1) ~= 0.5) % EAST wall
            %disp("go east")
%             curr_loc(r,c) = 1;
            curr_loc(r,c+1) = 0;
            hold on; imagesc(curr_loc); draw_walls(wall_loc);
            pause(0.5);
            visited(r,c+1) = 0.5;
            curr_loc(r,c+1) = 0.5;
            loc=loc+1;
            s.push(loc);
            c = c+1;

        elseif (c>1 && wall_bin(4) ~= 1 && curr_loc(r,c-1) ~= 0.5) % WEST wall
            %disp("go west")
%             curr_loc(r,c) = 1;
            curr_loc(r,c-1) = 0;
            hold on; imagesc(curr_loc); draw_walls(wall_loc);
            pause(0.5);
            visited(r,c-1) = 0.5;
            curr_loc(r,c-1) = 0.5;
            loc=loc-1;
            s.push(loc);
            c = c-1;

        else
            loc = s.pop();
            %disp("dead end")
            %disp(loc)
            %disp(s.content())
            % get r, c based on loc
            [r,c] = getrc(loc); % might be unecessary
            curr_loc(r,c)=0;
            hold on; imagesc(curr_loc); draw_walls(wall_loc);
            pause(0.5);
            curr_loc(r,c)=0.5;
            wall_bin = de2bi(wall_loc(r,c), 4, 'right-msb');
            if ((r > 1 && wall_bin(1) ~= 1 && curr_loc(r-1,c) ~= 0.5)...
                || (r < 5 && wall_bin(2) ~= 1 && curr_loc(r+1,c) ~= 0.5)...
                || (c<4 && wall_bin(3) ~= 1 && curr_loc(r,c+1) ~= 0.5)...
                || (c>1 && wall_bin(4) ~= 1 && curr_loc(r,c-1) ~= 0.5))
                s.push(loc);
            end
             %curr_loc(r,c) = .5;
            % mark visited
            visited(r,c) = 0.5;
        end
    end
    disp("done");
    
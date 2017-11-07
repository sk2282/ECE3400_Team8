# Milestone 3: Maze Navigation Algorithm

## Objective:
The goal of this milestone is to begin developing an algorithm for mave navigation by first simulating our algorithm in MATLAB and then moving it to the robot.

## MATLAB Simulation

### Version 1
* First, we implemented a solution similar to Team Alpha, where we use a DFS to navigate the maze.  
* We first found a stack implementation for MATLAB [online](https://www.mathworks.com/matlabcentral/fileexchange/28922-list--queue--stack?focused=5187765&tab=function).
* We use a 5x4 matrix to keep track of which squares the robot has visited, and we use a stack to traverse the maze.  
* We push maze coordinates to the stack to keep track of the robot’s path and pop coordinates from the stack when we want the robot to retrace its steps (e.g. to go back to an intersection that has unexplored forks).  The robot knows it’s done (prints ‘done’) when it tries to pop from an empty stack.  This means the robot will always go back to the start square before stopping the algorithm.
* For this version of the algorithm, we determine the direction the robot will go in by checking in this order: North, South, East, then West.

```Matlab
if (r > 1 && wall_bin(1) ~= 1 && curr_loc(r-1,c) ~= 0.5) % NORTH wall
    curr_loc(r-1,c) = 0; % set new curr location
    hold on; imagesc(curr_loc); draw_walls(detected_wall_loc); % display new current location
    pause(0.5);
    visited(r-1,c) = 0.5; % set new visited
    curr_loc(r-1,c) = 0.5;
    loc=loc-4;
    s.push(loc);
    r = r-1;
elseif (r < 5 && wall_bin(2) ~= 1 && curr_loc(r+1,c) ~= 0.5) % SOUTH wall
	% not including rest of code for sake of briefness
elseif (c<4 && wall_bin(3) ~= 1 && curr_loc(r,c+1) ~= 0.5) % EAST wall
	% ...
elseif (c>1 && wall_bin(4) ~= 1 && curr_loc(r,c-1) ~= 0.5) % WEST wall
	% ...
```

* [The first simulation displays the whole maze, and the robot maps it and ends where it started.](https://youtu.be/MxFL3VIOMlE)
* Below is a diagram showing a coordinate system and how we index the squares in our maze from 0 to 19.

<img src="https://github.com/sk2282/ECE3400_Team8/blob/master/pictures/Milestone3/Milestone3Coord.png?raw=true" height="300" />


### Version 2 
* Next, we tried to make it so the robot doesn’t have to go back to the start to know when it’s traversed all navigable area in the maze.  
* To do this, we created a separate 5x4 array that keeps track of the walls as the robot sees it.  
* Whenever the robot moves to a new square, this array gets updated.  
* If there exists a visited square that is adjacent to an unvisited square, and there is no wall between these squares, the robot will continue to search the maze.  Otherwise, it has visited all visitable squares and stops navigating.

``` Matlab
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
```

* [This version of the simulation has the robot stop once it's finished mapping all explorable area.](https://youtu.be/MUISAKUdXKQ)



### Final Version of Simulation
* Finally, we tried to tweak the algorithm slightly to more accurately simulate the robot’s movements.  
* In prior steps, the robot determines where to go knowing where every wall is.  
* At any given time, however, the robot can only know the locations of the walls bordering the squares it has visited as well as the walls surrounding the 5x4 maze.  So we created another 5x4 array to keep track of the walls known to the robot. We update this array every time the robot moves to a previously unvisited square.
* [Now, this simulation displays the maze as the robot maps it.](https://youtu.be/FBHg2GErlwE)


## Real-time Maze Mapping
* After finishing our simulation, we began working on our algorithm for real-time maze mapping. Our algorithm remained the same, but we just added code to integrate the robot. 
* We used code from before for line-following and turning, as well as for wall and treasure detection.


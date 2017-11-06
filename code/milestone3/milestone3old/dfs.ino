#include <StackArray.h>

StackArray <int> stack;
int r = 5;
int c = 4;
int loc = 19;
char wall_bin[4];
void dfs(int visited[5][4], int curr_loc[5][4]) {
    visited[r][c] = 0.5; // set starting point to "visited"
    curr_loc[r][c] = 0.5;
    stack.push(loc); // push first element, figure out numbering later
    
    while (!stack.isEmpty() && notDone(visited, detected_wall_loc)) {
        de2bi(detected_wall_loc[r][c]);
        // get unvisted node from top of stack
        detectWalls();
        // pick first direction that doesn't have a wall or visited
        if (r > 1 && wall_bin[0] != 1 && curr_loc[r-1][c] != 0.5) {// NORTH wall
            //disp("go north")
            faceRobot(0);
            curr_loc[r-1][c] = 0; // set new curr location
            visited[r-1][c] = 0.5; // set new visited
            curr_loc[r-1][c] = 0.5;
            loc=loc-4;
            stack.push(loc);
            r = r-1;
        }
        else if (r < 5 && wall_bin[1] != 1 && curr_loc[r+1][c] != 0.5) { // SOUTH wall
            //disp("go south")
            faceRobot(2);
            curr_loc[r+1][c] = 0;
            skipIntersection();
            visited[r+1][c] = 0.5;
            curr_loc[r+1][c] = 0.5;
            loc=loc+4;
            stack.push(loc);
            r = r+1;
        }
        else if (c<4 && wall_bin[2] != 1 && curr_loc[r][c+1] != 0.5) {// EAST wall
            faceRobot(1);
            //disp("go east")
            curr_loc[r][c+1] = 0;
            skipIntersection();
            visited[r][c+1] = 0.5;
            curr_loc[r][c+1] = 0.5;
            loc=loc+1;
            stack.push(loc);
            c = c+1;
        }
        else if (c>1 && wall_bin[3] != 1 && curr_loc[r][c-1] != 0.5) {// WEST wall
            //disp("go west")
            faceRobot(3);
            curr_loc[r][c-1] = 0;
            skipIntersection();
            visited[r][c-1] = 0.5;
            curr_loc[r][c-1] = 0.5;
            loc=loc-1;
            stack.push[loc];
            c = c-1;
        }
        else {
            loc = stack.pop();
            UTurn();
            // get r, c based on loc
            curr_loc[r][c]=0;
            curr_loc[r][c]=0.5;
            de2bi(wall_loc[r][c]);
            if ((r > 1 && wall_bin[0] != 1 && curr_loc[r-1][c] != 0.5) || 
                (r < 5 && wall_bin[1] != 1 && curr_loc[r+1][c] != 0.5) || 
                (c<4 && wall_bin[2] != 1 && curr_loc[r][c+1] != 0.5) || 
                (c>1 && wall_bin[3] != 1 && curr_loc[r][c-1] != 0.5)) {
                stack.push(loc);
            }
            visited[r][c] = 0.5;
        }
    }
    detectWalls();
    disp("done");
}


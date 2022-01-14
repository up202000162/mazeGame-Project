# DESCRIPTION:
 Game developed for Programming subject in 1st year

 
# GROUP_MEMBERS:
- Igor Rodrigues Diniz
- Vinícius Macedo Corrêa
 
# PROGRAM DEVELOPMENT STATE:
We were able to achieve all the objectives of the program and some improvements. 
One of them was to print the winners in alphabetical order, in cases where there was a tie between two or more people. In addition, we made our program create a new file and write the title (Player - Time) and the division (----) if there was not yet a winner file (MAZE_XX_WINNERS) to the XX maze.
As it was not specified in the project file as well, we decided that after the player saw the rules of the game (pressing 1) he would have 2 options: either to play (pressing 2), or to return to the initial menu (pressing 0).

We also didn't know if all the mazes should be in rectangular shapes, or if the shape could be changed. So we created mazes in other formats, such as Z (MAZE_10.TXT) and such as H (MAZE_14.TXT), for example, and made sure that our program was correct for these examples as well. For this, we fixed the lines of the maze and the columns of the maze (first line of the file (N1xN2)) and, if there were any lines in the maze that were less than the value read in N2 (number of characters in the line), we completed with whitespaces, so that we could work with the value of N2 in loops, and this made us a lot easier in cases of maze with strange shapes. Maze columns with values ​​less than N1 did not concern us, as they are already filled with whitespaces automatically in the formation of the maze within the file.

We were able to handle any possible entry error by the player, including a possible wrong input in the winner's name ("12345" for example), however, in the latter case, the teacher of the practical class said it would not be necessary, so we chose not to implement that. In addition, we implemented a 'capitalize' to all the names of the winners, but the teacher of the practical class said that we should print exactly how the user entered his name, that is, the same is in the folder. Initially we made the game with system ("cls") and system ("clear"), but we decided not to use it anymore, since the teacher in the theoretical classes talked about wanting to see the prints step by step and that would make it difficult.

# MAIN DIFICULTIES:
An initial difficulty was making the program switch between possible player choices. For example, go to menu, then see the rules, go back to menu, play, go back to menu when choosing the maze (pressing 0), play again... We managed to get around this problem, making these functions return values, either 'unsigned int' or 'bool'. Applying "return" at specific points in our program also helped us in this matter.

Another problem we had was to store the positions of the robots (row, col) inside a vector of vectors, because we were not able to push_back vectors. A first solution we had was to create a function that would zip two vectors, but that didn't make our code very elegant. The final solution we had was to create a 'Robots' struct that stores the positions in an array of size 2 (x, y), called 'position'. Thus, each robot had its position inserted in this array and, we were able to create a vector that contained elements of the type 'Robots', which facilitated the access to the positions.

Another difficulty was making collisions. The most common mistake was for the 'r' to keep moving, and go back to being 'R', but there were other mistakes as well. We solved this with 5 functions, called: 'bool player_movement', 'void robot_movements', 'bool robot_is_dead', 'bool player_win', 'bool player_lose' and also with some 'return' and 'continue' at specific points in cycles.

Handling input errors was pretty complicated too, but we managed with combinations of 'cin.fail ()', 'cin.peek ()', 'cin.ignore ()' and 'cin.clear ()'.

The last difficulty was in the leaderboard, as there were different behaviors for different compilers in relation to the 'resize ()' method of the string library. When a name entered was less than 15 and we did the resize (15), in Visual Studio everything went smoothly, but in Clion the rest of the characters were filled with 'NULL' and hindered the print of the leaderboard. We get around this by doing resize (15) only for names longer than 15 characters, and adding 'N' whitespaces that were missing to reach 15, where N = 15 - (name size). This worked on both compilers, and we kept it that way, as it brought us more security.

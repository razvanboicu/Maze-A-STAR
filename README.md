# Maze-BFS
The shortest way for the mouse to reach the cheese [A*]
-------------------------------------------------------
Labyrinth problem: 
It is considered a labyrinth represented by a matrix 
in which the walls are marked by −1 and the roads by 0. In the labyrinth a
a mouse in position (x0, y0) and a piece of cheese in position (x1, y1). S se
to make a road (preferably of minimum length) from ³oricel to cheese. it
requires both the location of the matrix in which the path traveled by the mouse is marked, and
And a string of pairs (xi, yi) = the coordinates of the strains representing the road.
The input data is read from the file
Use city-block distance as a cost function,| x1 - x2 | + | y1 - y2 |.

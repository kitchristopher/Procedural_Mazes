# Procedural Mazes
This project randomly generates different types of mazes using a graph-based data structure in a console application using ascii keys.

The following algorithms are used:
- Binary Tree
- Sidewider
- Alduous-Broder
- Wilson's
- Hunt and Kill
- Recursive Backtracker
- Dijkstra's

## Installation
This project contains the entire solution for visual studio. If visual studio is installed, then load up the solution and compile the project. 

## Usage

Once the .exe loads, various options are presented for the user. To select an option, press the number within the brackets and then press enter to confirm.

The first set of options are as follows:

- [0] Clear Cells: This will create a maze with no numbers inside the passageways of the maze.
- [1] All Distances: This will fill each maze passageway with the distance from the top-left corner of the maze.
- [2] Shortest-Path: This will prompt the user to specify a coordinate on the maze, afterwards the the shortest path form the top-left corner to the coordinate will be calculated and the path will be displayed in the maze with a number showing the distance.
- [3] Longest Path: The maze will find a random longest path in the maze and display the distances from the two points.
- [/] Benchmarking: Each maze will be calculated, and the number of dead-ends for each will be shown based on the size of the maze.

Next, the user will be prompted to select which type of maze algorithm to use.

## Learning Outcome
To demonstrate the usage of graphs, the procedural creation of mazes, and the usage of pathfinding to solve the mazes or make them longer.
These algorithms can also be implemented, with minor changes, in game engines such as Unity.

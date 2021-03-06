#include "stdafx.h"
#include "Cell.h"
#include "Grid.h"
#include <iostream>
#include "BinaryTree_Maze.h"
#include "Sidewinder.h"
#include "AldousBroder.h"
#include "Wilsons.h"
#include "HuntAndKill.h"
#include "RecursiveBacktracker.h"
#include <map>
#include <stdlib.h>

using namespace std;

void Display_LongestPath(Distances_Grid* grid);
void Display_All(Distances_Grid* grid);
void Display_ShortestPath(Distances_Grid* grid, int goalX, int goalY);
void Display_ClearGrid(Grid* grid);
string Get_AverageDeadEnds(int width, int height, int runCount);

int main()
{
	bool isLooping = true;
	string inputMaze = "";
	string inputCellBody = "";
	Grid* grid = nullptr;

	int width = 12;
	int height = 12;

	while (isLooping)
	{
		//with numbers or not; longest path, shortest path

		cout << "CELL BODY TYPE\n\n[0] Clear Cells\n[1] All Distances\n[2] Shortest Path\n[3] Longest Path\n[/] Benchmarking\n" << endl;
		cin >> inputCellBody;

		if (grid != nullptr)//clear the old grid
			delete grid;

		if (inputCellBody == "0")//normal grid
			grid = new Grid(width, height);
		else if (inputCellBody == "1" || inputCellBody == "2" || inputCellBody == "3")//show the distances
			grid = new Distances_Grid(width, height);


		system("cls");

		if (inputCellBody != "/")
		{
			cout << "CHOOSE MAZE ALGORITHM\n\n[0] Binary Tree\n[1] Sidewider\n\[2] Aldous-Broder\n[3] Wilson's\n[4] Hunt and Kill\n[5] Recursive Backtracker\n" << endl;
			cin >> inputMaze;

			if (inputMaze == "0")
				BinaryTree_Maze binaryTree_Maze(grid);
			else if (inputMaze == "1")
				Sidewinder sidewinder_Maze(grid);
			else if (inputMaze == "2")
				AldousBroder aldousBroder_Maze(grid);
			else if (inputMaze == "3")
				Wilsons wilsons_Maze(grid);
			else if (inputMaze == "4")
				HuntAndKill huntAndKill_Maze(grid);
			else if (inputMaze == "5")
				RecursiveBacktracker recursiveBacktracker_Maze(grid);
		}

		system("cls");

		if (inputCellBody == "0")
			Display_ClearGrid(grid);
		else if (inputCellBody == "1")
			Display_All(static_cast<Distances_Grid*>(grid));
		else if (inputCellBody == "2")
		{
			int goalX, goalY;
			cout << "Enter goal cell X coord: ";
			cin >> goalX;

			cout << "Enter goal cell Y coord: ";
			cin >> goalY;

			Display_ShortestPath(static_cast<Distances_Grid*>(grid), goalX, goalY);
		}
		else if (inputCellBody == "3")
			Display_LongestPath(static_cast<Distances_Grid*>(grid));
		else if (inputCellBody == "/")
		{
			cout << "Calculating..." << endl;
			string averageDeadEnds = Get_AverageDeadEnds(width, height, 100);
			system("cls");
			cout << averageDeadEnds << endl;
			cin.get();
			cin.get();
		}
	}

	cin.get();
	cin.get();
	return 0;
}


template<typename T>
int CountDeadEndsInMazeType(int width, int height, int runCount)
{
	int result = 0;

	for (size_t i = 0; i < runCount; i++)
	{
		Grid grid(width, height);
		T maze(&grid);

		result += grid.Get_DeadEnds().size();
	}

	return result;
}

string Get_AverageDeadEnds(int width, int height, int runCount)
{
	int mazeSize = width*height;
	string result = "Dead End Counts by Maze (" + to_string(width) + "x" + to_string(height) + ": Cells : " + to_string(mazeSize) + ")\n___________________________\n";

	auto prepareAverage = [](int totalCount, int runCount, int mazeSize)
	{
		int average = totalCount / runCount;

		string percent = to_string(((float)average / (float)mazeSize)*100);
		percent = percent.substr(0, 2);

		return to_string(average) + "/" + to_string(mazeSize) + " (" + percent + "%)\n";
	};

	result += "Binary Tree: " + prepareAverage(CountDeadEndsInMazeType<BinaryTree_Maze>(width, height, runCount), runCount, mazeSize);
	result += "Sidewinder: " + prepareAverage(CountDeadEndsInMazeType<Sidewinder>(width, height, runCount), runCount, mazeSize);
	result += "Aldous-Broder: " + prepareAverage(CountDeadEndsInMazeType<AldousBroder>(width, height, runCount), runCount, mazeSize);
	result += "Wilson's: " + prepareAverage(CountDeadEndsInMazeType<Wilsons>(width, height, runCount), runCount, mazeSize);
	result += "Hunt and Kill: " + prepareAverage(CountDeadEndsInMazeType<HuntAndKill>(width, height, runCount), runCount, mazeSize);
	result += "Recursive Backtracker: " + prepareAverage(CountDeadEndsInMazeType<RecursiveBacktracker>(width, height, runCount), runCount, mazeSize);

	return result;
}

void Display_ClearGrid(Grid* grid)
{
	cout << grid->Print_Grid() << endl;
}


void Display_All(Distances_Grid* grid)
{
	Cell* startCell = grid->Get_Matrix()->operator()(0, 0);//set start node
	auto distances = startCell->Distance();//set grid's distances to be the node's 


	grid->distances = &distances;
	cout << grid->Print_Grid() << endl;
}

void Display_ShortestPath(Distances_Grid* grid, int goalX, int goalY)
{
	Cell* startCell = grid->Get_Matrix()->operator()(0, 0);//set start node
	auto distances = startCell->Distance();//set grid's distances to be the node's 


	grid->distances = &distances;

	distances = distances.Find_ShortestPath(grid->Get_Matrix()->operator()(goalX, goalY));
	grid->distances = &distances;
	cout << grid->Print_Grid() << endl;
}

void Display_LongestPath(Distances_Grid* grid)
{
	Cell* startCell = grid->Get_Matrix()->operator()(0, 0);//set start node
	auto distances = startCell->Distance();//set grid's distances

	auto new_start_It = distances.Find_FurthestCell();//from the starting cell
	Cell* new_start = new_start_It->first;//furthest cell from the original start cell
	float max_distance = new_start_It->second;

	distances = new_start->Distance();//calculate new distances from the furthest cell
	auto goal_It = distances.Find_FurthestCell();
	Cell* newGoal = goal_It->first;


	distances = distances.Find_ShortestPath(newGoal);//find the path to the furthest cell now
	grid->distances = &distances;
	cout << grid->Print_Grid() << endl;
}


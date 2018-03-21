#include "stdafx.h"
#include "Wilsons.h"
#include "Utilities.h"

Wilsons::Wilsons(Grid* grid) : Maze(grid)
{
	Create_Maze();
}


Wilsons::~Wilsons()
{
}

void Wilsons::Create_Maze()
{
	vector<Cell*> unvisisted_Cells(0);

	for (auto it = _grid->Get_Matrix()->begin(); it != _grid->Get_Matrix()->end(); ++it)
		unvisisted_Cells.push_back(*it);//add all the cells as unvisited

	Cell* first = Utilties::Sample_Vector(&unvisisted_Cells);
	vector<Cell*>::iterator firstIndex = find(unvisisted_Cells.begin(), unvisisted_Cells.end(), first);//choose a random cell to start

	unvisisted_Cells.erase(firstIndex);//visit the cell

	while (!unvisisted_Cells.empty())
	{
		Cell* currentCell = Utilties::Sample_Vector(&unvisisted_Cells);//choose a random cell to begin the loop
		vector<Cell*> path{currentCell};

		while (find(unvisisted_Cells.begin(), unvisisted_Cells.end(), currentCell) != unvisisted_Cells.end())//if it contains currentcell. IE loops until it finds a visited cell
		{
			currentCell = Utilties::Sample_Vector(currentCell->Get_NeighborCells());//choose a random neighbor
			vector<Cell*>::iterator position = find(path.begin(), path.end(), currentCell);

			if (position != path.end())//the random neighbor has already been added to the path, thus it has looped around
				path.erase(position + 1, path.end());//erase all the cells after the chosen cell
			else//its a new cell so add it to the path
				path.push_back(currentCell);
		}

		for (auto it = path.begin(); it != path.end() - 1; it++)
		{
			(*it)->Link(*(it + 1));//link all the cells in the path to the one following it

			auto visitedCell = find(unvisisted_Cells.begin(), unvisisted_Cells.end(), (*it));
			
			unvisisted_Cells.erase(visitedCell);//consider the path visited
		}
	}

}

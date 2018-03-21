#include "stdafx.h"
#include "RecursiveBacktracker.h"
#include <stack>
#include <functional>
#include "Utilities.h"

RecursiveBacktracker::RecursiveBacktracker(Grid* grid) : Maze(grid)
{
	Create_Maze();
}


RecursiveBacktracker::~RecursiveBacktracker()
{
}

void RecursiveBacktracker::Create_Maze()
{
	stack<Cell*> cellsStack;
	cellsStack.push(_grid->Find_Random_Cell());
	
	std::function<bool(Cell*)> AddIfUnvisited = [](Cell* cur) {return  (cur->Get_LinkedCells()->empty()); };

	while (!cellsStack.empty())
	{
		Cell* currentCell = cellsStack.top();
		Cell* neighbor;

		vector<Cell*> neighbors = Utilties::Select_From_Vector(currentCell->Get_NeighborCells(), AddIfUnvisited);

		if (neighbors.empty())
			cellsStack.pop();
		else
		{
			neighbor = Utilties::Sample_Vector(&neighbors);
			currentCell->Link(neighbor);
			cellsStack.push(neighbor);
		}
	}
}

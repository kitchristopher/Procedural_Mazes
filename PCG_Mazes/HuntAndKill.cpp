#include "stdafx.h"
#include "HuntAndKill.h"
#include "Utilities.h"
#include <algorithm>
#include <functional>

HuntAndKill::HuntAndKill(Grid* grid) : Maze(grid)
{
	Create_Maze();
}


HuntAndKill::~HuntAndKill()
{
}

void HuntAndKill::Create_Maze()
{
	Cell* currentCell = _grid->Find_Random_Cell();
	Cell* neighborCell = nullptr;

	std::function<bool(Cell*)> AddIfUnvisited = [](Cell* cur) {return  (cur->Get_LinkedCells()->empty()); };
	std::function<bool(Cell*)> AddIfVisited = [](Cell* cur) {return  (!cur->Get_LinkedCells()->empty()); };

	while (currentCell != nullptr)
	{
		vector<Cell*> unvisitedNeighbors = Utilties::Select_From_Vector(currentCell->Get_NeighborCells(), AddIfUnvisited);

		if (!unvisitedNeighbors.empty())
		{
			neighborCell = Utilties::Sample_Vector(&unvisitedNeighbors);
			currentCell->Link(neighborCell);
			currentCell = neighborCell;
		}
		else//my neighbor has visited all its neighbors; i'm boxed in
		{
			currentCell = nullptr;

			for (size_t y = 0; y < _grid->Get_Row_Count(); y++)//Iterate through every cell, starting at top left
			{
				for (size_t x = 0; x < _grid->Get_Column_Count(); x++)
				{
					Cell* selectedCell = _grid->Get_Matrix()->operator()(x, y);

					vector<Cell*> visitedNeighbors = Utilties::Select_From_Vector(selectedCell->Get_NeighborCells(), AddIfVisited);

					if (selectedCell->Get_LinkedCells()->empty() && !visitedNeighbors.empty())//find the first unlinked cell that has some visited neighbors. randomly link to one of them
					{
						currentCell = selectedCell;

						neighborCell = Utilties::Sample_Vector(&visitedNeighbors);
						currentCell->Link(neighborCell);

						break;
					}
				}
			}
		}

	}
}

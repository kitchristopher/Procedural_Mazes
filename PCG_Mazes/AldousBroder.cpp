#include "stdafx.h"
#include "AldousBroder.h"
#include "Utilities.h"

AldousBroder::AldousBroder(Grid* grid) : Maze(grid)
{
	Create_Maze();
}


AldousBroder::~AldousBroder()
{
}

void AldousBroder::Create_Maze()
{
	Cell* currentCell = _grid->Find_Random_Cell();
	int unvisited_Count = _grid->Get_Size() - 1;

	while (unvisited_Count > 0)
	{
		Cell* neighborCell = Utilties::Sample_Vector(currentCell->Get_NeighborCells());

		if (neighborCell->Get_LinkedCells()->empty())
		{
			currentCell->Link(neighborCell);
			--unvisited_Count;
		}

		currentCell = neighborCell;
	}
}

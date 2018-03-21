#pragma once
#include "Maze.h"
class RecursiveBacktracker : public Maze
{
public:
	RecursiveBacktracker(Grid* grid);
	~RecursiveBacktracker();
private:
	virtual void Create_Maze() override;
};


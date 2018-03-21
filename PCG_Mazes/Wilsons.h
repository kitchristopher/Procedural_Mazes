#pragma once
#include "Maze.h"

class Wilsons : public Maze
{
public:
	Wilsons(Grid* grid);
	~Wilsons();

private:
	virtual void Create_Maze() override;
};


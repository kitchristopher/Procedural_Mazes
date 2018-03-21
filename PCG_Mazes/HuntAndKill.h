#pragma once
#include "Maze.h"

class HuntAndKill :public Maze
{
public:
	HuntAndKill(Grid* grid);
	~HuntAndKill();
private:
	virtual void Create_Maze() override;
};


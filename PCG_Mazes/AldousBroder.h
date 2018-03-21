#pragma once
#include "Maze.h"

class AldousBroder : public Maze
{
public:
	AldousBroder(Grid* grid);
	~AldousBroder();
private:
	virtual void Create_Maze() override;
};


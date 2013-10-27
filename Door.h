#pragma once
#include "block.h"

class Door :
	public Block
{
public:
	Door(void);
	Door(unsigned int, string);
	~Door(void);
private:
};


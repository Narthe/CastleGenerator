#pragma once
#include "block.h"

class Door :
	public Block
{
public:
	Door(void);
	Door(unsigned int);
	~Door(void);
private:
	unsigned int m_blockNumber;
	std::string m_type;
};


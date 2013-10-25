
#pragma once
#include "block.h"

class Tower :
	public Block
{
public:
	Tower(void);
	Tower::Tower(unsigned int);
	~Tower(void);
private:
	unsigned int m_blockNumber;
	std::string m_type;
};


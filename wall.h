
#pragma once
#include "block.h"
class Wall:
	public Block
{
	public:
		Wall();
		Wall::Wall(unsigned int n);
		~Wall(void);

	private:
		string m_type;
		unsigned int m_position;
};

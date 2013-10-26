#include "block.h"
#include <iostream>

using namespace std;

Block::Block()
{
}

Block::Block(unsigned int n) : m_position(n)
{
}


Block::~Block(void)
{
}

bool Block::operator < (const Block& b)
{
	return (this->m_position< b.m_position);
}

void Block::toString()
{
	cout << "Bloc num : " << m_position << " de type : " << m_type << endl;
}
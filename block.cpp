#include "block.h"
#include <iostream>

using namespace std;

Block::Block() : m_type("bloc")
{
}

Block::Block(unsigned int n) : m_position(n), m_type("bloc")
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
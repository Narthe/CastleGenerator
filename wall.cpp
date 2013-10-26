#include "wall.h"

Wall::Wall() : m_type("wall")
{
}

Wall::Wall(unsigned int n) : Block(n)//, m_type("wall")
{
	m_type = "wall";
}

Wall::~Wall(void)
{

}

#include "Tower.h"

Tower::Tower(void) : m_type("tower")
{
}

Tower::Tower(unsigned int n) : Block(n), m_type("tower")
{
	//m_type = "tower";
}

Tower::~Tower(void)
{
}

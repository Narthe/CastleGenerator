#include "Tower.h"


Tower::Tower(void) : m_type("tower")
{
}

Tower::Tower(unsigned int n) : m_blockNumber(n) , m_type("tower")
{
}

Tower::~Tower(void)
{
}

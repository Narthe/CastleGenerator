#include "Door.h"


Door::Door(void) : m_type("door")
{
}

Door::Door(unsigned int n) : m_type("door"), m_blockNumber(n)
{
}

Door::~Door(void)
{
}

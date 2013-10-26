#include "Door.h"


Door::Door(void) : m_type("door")
{
}

Door::Door(unsigned int n) : Block(n)//, m_type("door")
{
	m_type = "door";
}

Door::~Door(void)
{
}

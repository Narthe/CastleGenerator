
#pragma once
#include "block.h"
/** Modifier constructeur de la classe parente pour pouvoir passer 
le numero en parametre de chaque bloc**/
class Wall:
	public Block
{
	public:
		Wall();
		Wall::Wall(unsigned int n);
		~Wall(void);

		void Wall::toString();
	private:
		std::string m_type;
};

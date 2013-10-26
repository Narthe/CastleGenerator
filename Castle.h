#pragma once

#include <cmath>
#include <algorithm>
#include <ctime> 
#include "Settings.h"
#include "block.h"
#include "wall.h"
#include "Door.h"
#include "Tower.h"

using namespace std;

class Castle
{
	public:
		Castle(void);
		~Castle(void);
		void generateWall(SETTINGS settings); //génère un mur : renvoit un arbre de "blocs" correspondant aux éléments du mur
		void fillPositions(int n);
		void Castle::toString();

	private:
		vector<Block> m_wall;
		vector<unsigned int> m_positions;
};


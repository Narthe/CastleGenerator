#pragma once

#include <cmath>
#include <algorithm>
#include <ctime> 
#include "Settings.h"
//#include "block.h"
//#include "wall.h"
//#include "Door.h"
//#include "Tower.h"
//#include "Vector2D.h"

#include <windows.h>

#include <time.h>
#include <vector>

using namespace std;

class Castle
{
	public:
		Castle(void);
		Castle(SETTINGS s);
		~Castle(void);
		void generateWall();

		void initMatrice();
		void addRectangles();
		void getPerimeter();
		void drawMatrice();
		int nbNeighbours(int k, int l);
		bool isColliding(RECT r);
		RECT getRandomRect();

		void Castle::toString();

		char **m_matrix;
		SETTINGS m_settings;

	private:
		vector<RECT> m_rectangles;
		vector<POINT> m_pointsToPop;
};


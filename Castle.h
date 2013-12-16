#pragma once
#include <windows.h>
#include <time.h>
#include <cmath>
#include <algorithm>
#include <ctime> 
#include "Settings.h"
#include <vector>

using namespace std;

class Castle
{
	public:
		Castle(void);
		Castle(SETTINGS s);
		~Castle(void);
		void generateWall();
		void regenerateWall();

		void initMatrice();
		void cleanMatrix();
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


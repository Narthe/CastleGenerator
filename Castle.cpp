#include "Castle.h"

Castle::Castle(void)
{
}

Castle::Castle(SETTINGS s)
{
	m_settings = s;
	initMatrice();
}

Castle::~Castle(void)
{
	for (int i = 0; i < m_settings.matrix_width; i++)
		delete[] m_matrix[i];
	delete[] m_matrix;
}

void Castle::generateWall()
{
	addRectangles();
	getPerimeter();
}

void Castle::initMatrice()
{
	m_matrix = new char *[m_settings.matrix_width];
	for (int i = 0; i < m_settings.matrix_width; i++)
	{
		m_matrix[i] = new char[m_settings.matrix_height];
	}

	for (int i = 0; i < m_settings.matrix_width; i++)
	{
		for (int j = 0; j < m_settings.matrix_height; j++)
			m_matrix[i][j] = ' ';
	}
}

RECT Castle::getRandomRect()
{
	int randPosX = m_settings.matrix_width - 1;
	int randPosY = m_settings.matrix_height - 1;

	int maxWidth = 0;
	int maxHeight = 0;

	int randWidth = 0;
	int randHeight = 0;

	srand(time(NULL));

	RECT r;
	r.left = rand() % randPosX;
	r.top = rand() % randPosY;

	maxWidth = randPosX - r.left;
	maxHeight = randPosY - r.top;

	randWidth = rand() % maxWidth + 1;
	randHeight = rand() % maxHeight + 1;

	r.right = r.left + randWidth;
	r.bottom = r.top + randHeight;

	return r;
}

void Castle::addRectangles()
{

	for (int i = 0; i < m_settings.rect_number; i++)
	{
		RECT r = getRandomRect();
		while (!isColliding(r))
			r = getRandomRect();

		m_rectangles.push_back(r);

		for (int j = r.left; j <= r.right; j++)
		{
			if (j == r.left || j == r.right)
			{
				m_matrix[j][r.top] = 'T';
				m_matrix[j][r.bottom] = 'T';
			}
			else
			{
				m_matrix[j][r.top] = 'W';
				m_matrix[j][r.bottom] = 'W';
			}
		}
		for (int k = r.top + 1; k <= r.bottom - 1; k++)
		{
			m_matrix[r.left][k] = 'W';
			m_matrix[r.right][k] = 'W';
		}
	}
}

void Castle::getPerimeter()
{
	for (int j = 0; j < m_settings.matrix_width; j++)
	{
		for (int k = 0; k < m_settings.matrix_height; k++)
		{
			if (m_rectangles.size() > 1 && m_matrix[j][k]){
				for (int l = 0; l < m_rectangles.size(); ++l)
				{
					if ((j > m_rectangles[l].left && j < m_rectangles[l].right) && (k > m_rectangles[l].top && k < m_rectangles[l].bottom))
						m_matrix[j][k] = ' ';
					else{
						if (nbNeighbours(j, k) == 8){
							POINT p;
							p.x = j;
							p.y = k;
							m_pointsToPop.push_back(p);
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < m_pointsToPop.size(); i++)
	{
		m_matrix[m_pointsToPop[i].x][m_pointsToPop[i].y] = NULL;;
	}
}

int Castle::nbNeighbours(int k, int l)
{
	int cpt = 0;
	for (int i = k - 1; i <= k + 1; i++)
	{
		if (i >= 0 && i <= (m_settings.matrix_width - 1))
		{
			for (int j = l - 1; j <= l + 1; j++)
			{
				if (j >= 0 && j <= (m_settings.matrix_height - 1))
				{
					if (m_matrix[i][j] == 'W' || m_matrix[i][j] == 'T')
						cpt++;
				}
			}
		}
	}

	return cpt - 1;
}

bool Castle::isColliding(RECT r)
{
	for (int j = r.left; j <= r.right; j++)
	{
		for (int k = r.top; k <= r.bottom; k++)
		{
			for (int l = 0; l < m_rectangles.size(); l++)
			{
				if ((j > m_rectangles[l].left && j < m_rectangles[l].right) && (k > m_rectangles[l].top && k < m_rectangles[l].bottom))
					return true;
			}
		}
	}
}


void Castle::toString()
{
	char buffer[5];
	for (int i = 0; i < m_settings.matrix_width; i++)
	{
		for (int j = 0; j < m_settings.matrix_height; j++)
		{
			char c = m_matrix[i][j];
			sprintf_s(buffer, 5, "|_%c_", c);
			OutputDebugString(buffer);
		}
		sprintf_s(buffer, 5, "|\n");
		OutputDebugString(buffer);
	}
}
//CLASS BLOCK :
//Correspond � un �l�ment du chateau (mur, porte, tour, etc, ..)

#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Block
{
	public:
		Block();
		Block(unsigned int n, string s);
		~Block(void);
		void toString();
		bool operator < (const Block& b);
	protected:
		string m_type;
		unsigned int m_position;
		
};

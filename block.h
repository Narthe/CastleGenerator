//CLASS BLOCK :
//Correspond à un élément du chateau (mur, porte, tour, etc, ..)

#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Block
{
	public:
		Block();
		Block(unsigned int n);
		~Block(void);
		void toString();
		bool operator < (const Block& b);
	private:
		string m_type;
		unsigned int m_position;
		
};

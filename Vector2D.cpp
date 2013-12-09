// Vector2D.cpp

#include "StdAfx.h"
#include "Vector2D.h"

Vector2D::Vector2D(void)
{
}

Vector2D::Vector2D(float X, float Y){
	this->X = X;
	this->Y = Y;
}

// Returns the length of the vector
float Vector2D::Length(){
	return sqrt(X * X + Y * Y);
}

// Normalizes the vector
Vector2D Vector2D::normalize(){
	Vector2D vector;
	float length = this->Length();

	if (length != 0){
		vector.X = X / length;
		vector.Y = Y / length;
	}

	return vector;
}

Vector2D::~Vector2D(void)
{
}
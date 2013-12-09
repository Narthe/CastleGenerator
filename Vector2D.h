#pragma once

#include <math.h>

class Vector2D
{
public:
	Vector2D(void);
	Vector2D(float X, float Y);
	~Vector2D(void);
	float Length();
	Vector2D normalize();
	float X, Y;
};
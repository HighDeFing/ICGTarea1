#pragma once

#include "Figure.h"
#include <cmath>

class CCircle : public CFigure
{
public:
	CCircle();
	~CCircle();
	void draw_circle(long long int, long long int, long long int, long long int);
	void draw_pixel(long long int, long long int);
	void display();
};

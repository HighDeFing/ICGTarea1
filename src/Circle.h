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
	void draw_fpixel(int, int);
	void draw_bpixel(long long int x, long long int y);
	void display();
	void Horizline(int, int, int);
	void fill();
	void box();
};

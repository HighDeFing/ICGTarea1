#pragma once

#include "Figure.h"


class CTriangle : public CFigure
{
public:
	CTriangle();
	~CTriangle();
	void draw_triangle(long long int, long long int, long long int, long long int, long long int, long long int);
	void draw_pixel(int, int);
	void draw_fpixel(int, int);
	void draw_line(long long int, long long int, long long int, long long int);
	void draw_fline(int, int, int, int);
	void display();
	void fill();
	void box();
};

#pragma once

#include "Figure.h"

class CElipse : public CFigure
{
public:
	CElipse();
	~CElipse();
	void draw_elipse(long long int, long long int, long long int, long long int);
	void draw_pixel(long long int, long long int);
	void draw_bpixel(long long int x, long long int y);
	void display();
	void draw_fpixel(int, int);
	void Horizline(int, int, int);
	void fill();
	void box();
};


#pragma once

#include "Figure.h"

class CLine : public CFigure
{
public:
	CLine();
	~CLine();
	void draw_line(long long int, long long int, long long int, long long int);
	void draw_pixel(long long int, long long int);
	void draw_bpixel(long long int, long long int);
	void display();
	void fill();
	void box();
};


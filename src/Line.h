#pragma once

#include "Figure.h"

class CLine : public CFigure
{
public:
	CLine();
	~CLine();
	void draw_line(int, int, int, int);
	void draw_pixel(int, int);
	void display();
};


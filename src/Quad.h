#pragma once

#include "Figure.h"


class CQuad : public CFigure
{
public:
	CQuad();
	~CQuad();
	void draw_rectangle(int, int, int, int);
	void draw_pixel(int, int);
	void draw_fpixel(int, int);
	void draw_line(int, int, int, int);
	void Horizline(int, int, int);
	void display();
	void fill();
};


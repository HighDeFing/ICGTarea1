#pragma once

#include "Figure.h"


class CQuad : public CFigure
{
public:
	CQuad();
	~CQuad();
	void draw_rectangle(int, int, int, int);
	void draw_pixel(int, int);
	void display();
};


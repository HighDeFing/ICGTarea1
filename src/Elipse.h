#pragma once

#include "Figure.h"

class CElipse : public CFigure
{
public:
	CElipse();
	~CElipse();
	void draw_elipse(long long int, long long int, long long int, long long int);
	void draw_pixel(long long int, long long int);
	void display();
	void fill();
};


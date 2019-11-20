#include "Triangle.h"
#include <math.h> 

CTriangle::CTriangle()
{

	mVertices = new float* [3];
	for (int i = 0; i < 3; ++i)
		mVertices[i] = new float[2];

	mType = TRIANGLE;
}

CTriangle::~CTriangle()
{
	for (int i = 0; i < 3; ++i)
		delete[] mVertices[i];
}


void CTriangle::display()
{
	int x1, x2, y1, y2, x3, y3;
	glColor3fv(mColor);
	x1 = int(mVertices[0][0]); x2 = long long int(mVertices[1][0]); y1 = long long int(mVertices[0][1]); y2 = long long int(mVertices[1][1]);
	x3 = int(mVertices[2][0]); y3 = long long int(mVertices[2][1]);
	draw_triangle(x1, x2, x3, y1, y2, y3);
}

void CTriangle::draw_pixel(long long int x, long long int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void CTriangle::draw_line(long long int x1, long long int x2,long long int y1,long long int y2) {
	long long int dx, dy, i, e;
	long long int incx, incy, inc1, inc2;
	long long int x, y;

	dx = x2 - x1;
	dy = y2 - y1;

	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	incx = 1;
	if (x2 < x1) incx = -1;
	incy = 1;
	if (y2 < y1) incy = -1;
	x = x1; y = y1;
	if (dx > dy) {
		draw_pixel(x, y);
		e = (dy << 1) - dx;
		inc1 = (dy - dx) << 1;
		inc2 = dy << 1;
		for (i = 0; i < dx; i++) {
			if (e >= 0) {
				y += incy;
				e += inc1;
			}
			else
				e += inc2;
			x += incx;
			draw_pixel(x, y);
		}

	}
	else {
		draw_pixel(x, y);
		e = (dx << 1) - dy;
		inc1 = (dx - dy) << 1;
		inc2 = dx << 1;
		for (i = 0; i < dy; i++) {
			if (e >= 0) {
				x += incx;
				e += inc1;
			}
			else
				e += inc2;
			y += incy;
			draw_pixel(x, y);
		}
	}
}


void CTriangle::draw_triangle(long long int x1,long long int x2, long long int x3, long long int y1, long long int y2, long long int y3) {
	draw_line(x1, x2, y1, y2);
	draw_line(x1, x3, y1, y3);
	draw_line(x2, x3, y2, y3);
}

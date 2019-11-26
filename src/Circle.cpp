#include "Circle.h"
#include <cmath>
#include <iostream>

CCircle::CCircle()
{

	mVertices = new float* [2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = CIRCLE;
}

CCircle::~CCircle()
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CCircle::display()
{
	long long int x1, x2, y1, y2;
	glColor3fv(mColor);
	x1 = long long int(mVertices[0][0]); x2 = long long int(mVertices[1][0]); y1 = long long int(mVertices[0][1]); y2 = long long int(mVertices[1][1]);
	draw_circle(x1, x2, y1, y2);
}

void CCircle::draw_pixel(long long int x, long long int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}


void CCircle::draw_circle(long long int x1, long long int x2, long long int y1, long long int y2) {

	long long int midx, midy, x, y, radius, dp;
	radius = sqrt(pow((mVertices[0][0] - mVertices[1][0]), 2) + pow((mVertices[0][1] - mVertices[1][1]), 2));
	/* mid position of x-axis */
	midx = x1;
	/* mid position of y-axis */
	midy = y1;
	dp = 1 - radius;
	x = 0, y = radius;
	/* draws a circle */
	while (x <= y) {
		/*
		 * plot points on all eight octants -
		 * circle centered at (midx, midy)
		 */
		draw_pixel(midx + x, midy + y);             //NE (infinity,1)
		draw_pixel(midx - x, midy + y);				//NW (-infinity,-1)
		draw_pixel(midx + x, midy - y);				//SE (-infinity,-1)
		draw_pixel(midx - x, midy - y);				//SW (infinity,1)
		draw_pixel(midx + y, midy + x);				//NE (1,0)
		draw_pixel(midx - y, midy + x);				//NW (-1,0)
		draw_pixel(midx + y, midy - x);				//SE (-1,0)
		draw_pixel(midx - y, midy - x);				//SW (0,1)
		/*
		 * calculate next points(x, y) - considering
		 * the circle centered on (0, 0).
		 */

		if (dp < 0) {
			dp = dp + (x << 1) + 3;
		}
		else {
			y = y - 1;
			dp = dp + ((x - y) << 1) + 5;
		}
		x = x + 1;
	};


}

void CCircle::fill() {

}
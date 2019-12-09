#include "Circle.h"
#include <cmath>
#include <iostream>
#include <algorithm>

CCircle::CCircle()
{

	mVertices = new float* [2];
	bVertices = new float* [2];
	for (int i = 0; i < 2; ++i) {
		mVertices[i] = new float[2];
		bVertices[i] = new float[2];
	}

	mType = CIRCLE;
}

CCircle::~CCircle()
{
	for (int i = 0; i < 2; ++i) {
		delete[] mVertices[i];
		delete[] bVertices[i];
	}
}

void CCircle::box() {
	int x1, x2, y1, y2;
	x1 = long long int(bVertices[0][0]); x2 = long long int(bVertices[1][0]); y1 = long long int(bVertices[0][1]); y2 = long long int(bVertices[1][1]);
	int xmin = std::min(x1, x2); int xmax = std::max(x1, x2);
	int ymin = std::min(y1, y2); int ymax = std::max(y1, y2);
	for (int i = xmin; i <= xmax; i++) {
		draw_bpixel(i, ymin);
		draw_bpixel(i, ymax);
	}
	for (int i = ymin + 1; i <= ymax - 1; i++) {
		draw_bpixel(xmin, i);
		draw_bpixel(xmax, i);
	}
}

void CCircle::display()
{
	long long int x1, x2, y1, y2;
	x1 = long long int(mVertices[0][0]); x2 = long long int(mVertices[1][0]); y1 = long long int(mVertices[0][1]); y2 = long long int(mVertices[1][1]);
	draw_circle(x1, x2, y1, y2);
	setbColor(0.0f, 0.95294, 0.89411); //set color of bounding box
	if (bbox) {
		box();
	}
}

void CCircle::draw_pixel(long long int x, long long int y) {
	glColor3fv(mColor);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void CCircle::draw_bpixel(long long int x, long long int y) {
	glColor3fv(bColor);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void CCircle::Horizline(int xMin, int yMin, int  xMax) {

	for (int i = xMin; i < xMax; i++)
		draw_fpixel(i, yMin);
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
		if (bfill) {
			Horizline(midx - x, midy + y - 1, midx + x + 1);
			Horizline(midx - y + 1, midy + x, midx + y);
			Horizline(midx - y + 1, midy - x, midx + y);
			Horizline(midx - x, midy - y + 1, midx + x + 1);
		}
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

void CCircle::draw_fpixel(int x, int y) {
	glColor3fv(fColor);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}


void CCircle::fill() {
	
}
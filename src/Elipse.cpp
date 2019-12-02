#include "Elipse.h"
#include <stdlib.h>

CElipse::CElipse()
{

	mVertices = new float* [2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = ELIPSE;
}

CElipse::~CElipse()
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CElipse::display()
{
	int x1, x2, y1, y2;
	x1 = int(mVertices[0][0]); x2 = long long int(mVertices[1][0]); y1 = long long int(mVertices[0][1]); y2 = long long int(mVertices[1][1]);
	draw_elipse(x1, x2, y1, y2);
}

void CElipse::draw_fpixel(int x, int y) {
	glColor3fv(fColor);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void CElipse::draw_pixel(long long int x, long long int y) {
	glColor3fv(mColor);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

long  getmaxx(int x0, int x1) {
	if (x0 > x1) return x0;
	else return x1;
}

long getmaxy(long long int y0,long long int y1) {
	if (y0 > y1) return y0;
	else return y1;
}

void CElipse::Horizline(int xMin, int yMin, int xMax) {

	for (int i = xMin; i <= xMax; i++)
		draw_fpixel(i, yMin);
}

void CElipse::draw_elipse(long long int x1, long long int x2,long long int y1, long long int y2) {
	long long int midx, midy, xradius, yradius;
	long long int xrad2, yrad2, twoxrad2, twoyrad2;
	long long int x, y, dp, dpx, dpy;

	/* x axis radius and y axis radius of ellipse */
	xradius = abs(x2 - x1); yradius = abs(y1 - y2);

	/* finding the center postion to draw ellipse */
	midx = x1;
	midy = y1;

	xrad2 = xradius * xradius;
	yrad2 = yradius * yradius;

	twoxrad2 = 2 * xrad2;
	twoyrad2 = 2 * yrad2;
	x = dpx = 0;
	y = yradius;
	dpy = twoxrad2 * y;

	draw_pixel(midx + x, midy + y);
	draw_pixel(midx - x, midy + y); //draw top and bottom pixels
	draw_pixel(midx + x, midy - y);
	draw_pixel(midx - x, midy - y);
	/*if (bfill) {
		Horizline(midx - x, midy + y - 1, midx + x);
		Horizline(midx - x, midy - y + 1, midx + x);
	}*/

	dp = (long long int)(0.5 + yrad2 - (xrad2 * yradius) + (0.25 * xrad2));

	while (dpx < dpy) {
		x = x + 1;
		dpx = dpx + twoyrad2;
		if (dp < 0) {
			dp = dp + yrad2 + dpx;
		}
		else {
			y = y - 1;
			dpy = dpy - twoxrad2;
			dp = dp + yrad2 + dpx - dpy;
		}
		if (bfill) {
			Horizline(midx - x, midy + y - 1, midx + x);
			Horizline(midx - x, midy - y + 1, midx + x);
		}
		/* plotting points in y-axis(top/bottom) */
		draw_pixel(midx + x, midy + y);
		draw_pixel(midx - x, midy + y);
		draw_pixel(midx + x, midy - y);
		draw_pixel(midx - x, midy - y);
		//sleep(100);
	}

	//delay(500);

	dp = (long long int)(0.5 + yrad2 * (x + 0.5) * (x + 0.5) +
		xrad2 * (y - 1) * (y - 1) - xrad2 * yrad2);

	while (y > 0) {
		y = y - 1;
		dpy = dpy - twoxrad2;

		if (dp > 0) {
			dp = dp + xrad2 - dpy;
		}
		else {
			x = x + 1;
			dpx = dpx + twoyrad2;
			dp = dp + xrad2 - dpy + dpx;
		}

		/* plotting points at x-axis(left/right) */
		if (bfill) {
			Horizline(midx - x, midy + y - 1, midx + x);
			Horizline(midx - x, midy - y + 1, midx + x);
		}
		draw_pixel(midx + x, midy + y);
		draw_pixel(midx - x, midy + y);
		draw_pixel(midx + x, midy - y);
		draw_pixel(midx - x, midy - y);
		//delay(100);
	}
}

void CElipse::fill() {

}

void CElipse::box() {

}

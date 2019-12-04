#include "Line.h"
#include <algorithm>

CLine::CLine()
{

	mVertices = new float* [2];
	bVertices = new float* [2];
	for (int i = 0; i < 2; ++i) {
		mVertices[i] = new float[2];
		bVertices[i] = new float[2];
	}

	
	mType = LINE;
}

CLine::~CLine()
{
	for (int i = 0; i < 2; ++i) {
		delete[] mVertices[i];
		delete[] bVertices[i];
	}
}

void CLine::display()
{
	int x1, x2, y1, y2;
	glColor3fv(mColor);
	x1 = long long int(mVertices[0][0]); x2 = long long int(mVertices[1][0]); y1 = long long int(mVertices[0][1]); y2 = long long int(mVertices[1][1]);
	draw_line(x1, x2, y1, y2);
	setbColor(0.0f, 0.95294, 0.89411);  //set color of bounding box
	if (bbox) {
		box();
	}
}

void CLine::draw_pixel(long long int x, long long int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void CLine::draw_bpixel(long long int x, long long int y) {
	glColor3fv(bColor);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void CLine::draw_line(long long int x1, long long int x2, long long int y1, long long int y2) {
	int dx, dy, i, e;
	int incx, incy, inc1, inc2;
	int x, y;

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

void CLine::fill() {

}

void CLine::box() {
	int x1, x2, y1, y2;
	x1 = long long int(bVertices[0][0]); x2 = long long int(bVertices[1][0]); y1 = long long int(bVertices[0][1]); y2 = long long int(bVertices[1][1]);
	int xmin = std::min(x1, x2); int xmax = std::max(x1, x2);
	int ymin = std::min(y1, y2); int ymax = std::max(y1, y2);
	glColor3fv(bColor);
	for (int i = xmin; i <= xmax; i++) {
		draw_pixel(i, ymin);
		draw_pixel(i, ymax);
	}
	for (int i = ymin + 1; i <= ymax - 1; i++) {
		draw_pixel(xmin, i);
		draw_pixel(xmax, i);
	}
}
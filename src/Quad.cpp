#include "Quad.h"

#include <algorithm>

CQuad::CQuad()
{

	mVertices = new float* [2];
	for (int i = 0; i < 2; ++i)
		mVertices[i] = new float[2];

	mType = QUAD;
}

CQuad::~CQuad()
{
	for (int i = 0; i < 2; ++i)
		delete[] mVertices[i];
}

void CQuad::display()
{
	int x1, x2, y1, y2;
	glColor3fv(mColor);
	x1 = int(mVertices[0][0]); x2 = int(mVertices[1][0]); y1 = int(mVertices[0][1]); y2 = int(mVertices[1][1]);
	draw_rectangle(x1, x2, y1, y2);
}

void CQuad::draw_pixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void CQuad::draw_rectangle(int x1, int x2, int y1, int y2) {
	int xmin = std::min(x1, x2); int xmax = std::max(x1, x2);
	int ymin = std::min(y1, y2); int ymax = std::max(y1, y2);
	for (int i = xmin; i <= xmax; i++) {
		draw_pixel(i, ymin);
		draw_pixel(i, ymax);
	}
	for (int i = ymin + 1; i <= ymax - 1; i++) {
		draw_pixel(xmin, i);
		draw_pixel(xmax, i);
	}
}

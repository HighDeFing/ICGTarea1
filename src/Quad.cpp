#include "Quad.h"
#include <algorithm>
#include "EditInterface.h"

CQuad::CQuad()
{

	mVertices = new float* [2];
	bVertices = new float* [2];
	for (int i = 0; i < 2; ++i) {
	mVertices[i] = new float[2];
	bVertices[i] = new float[2];
	}

	mType = QUAD;
}

CQuad::~CQuad()
{
	for (int i = 0; i < 2; ++i) {
		delete[] mVertices[i];
		delete[] bVertices[i];
	}
}

void CQuad::display()
{
	int x1, x2, y1, y2;
	x1 = int(mVertices[0][0]); x2 = int(mVertices[1][0]); y1 = int(mVertices[0][1]); y2 = int(mVertices[1][1]);
	fill();
	glColor3fv(mColor);
	draw_rectangle(x1, x2, y1, y2);
	setbColor(0.0f, 0.95294, 0.89411);  //set color of bounding box
	if (bbox) {
		box();
	}
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


void CQuad::fill(){
	int x1, x2, y1, y2;
	x1 = int(mVertices[0][0]); x2 = int(mVertices[1][0]); y1 = int(mVertices[0][1]); y2 = int(mVertices[1][1]);
	int xmin = std::min(x1, x2); int xmax = std::max(x1, x2);
	int ymin = std::min(y1, y2); int ymax = std::max(y1, y2);
	if (bfill) {
		for (int i = ymin + 1; i <= ymax - 1; i++) {
			Horizline(xmin + 1, i, xmax - 1);
		}
	}
}

void CQuad::draw_fpixel(int x, int y) {
	glColor3fv(fColor);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void CQuad::Horizline(int xMin, int yMin, int  xMax) {

	for (int i = xMin; i <= xMax; i++)
		draw_fpixel(i, yMin);
}

void CQuad::box() {
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

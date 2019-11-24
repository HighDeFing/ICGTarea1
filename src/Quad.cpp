#include "Quad.h"
#include <algorithm>
#include "EditInterface.h"
CEditInterface* editInterfaceq;

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
	x1 = int(mVertices[0][0]); x2 = int(mVertices[1][0]); y1 = int(mVertices[0][1]); y2 = int(mVertices[1][1]);
	draw_rectangle(x1, x2, y1, y2);
}

void CQuad::draw_pixel(int x, int y) {
	glColor3fv(mColor);
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
	editInterfaceq = CEditInterface::Instance();
	x1 = int(mVertices[0][0]); x2 = int(mVertices[1][0]); y1 = int(mVertices[0][1]); y2 = int(mVertices[1][1]);
	int xmin = std::min(x1, x2); int xmax = std::max(x1, x2);
	int ymin = std::min(y1, y2); int ymax = std::max(y1, y2);
	if (editInterfaceq->bfill) {
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


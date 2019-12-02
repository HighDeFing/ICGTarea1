#include "Figure.h"

CFigure::CFigure()
{
	mColor[0] = 0.0f;
	mColor[1] = 0.0f;
	mColor[2] = 0.0f;
}

CFigure::~CFigure()
{
	delete[] mVertices;
}

void CFigure::setVertex(int id, float x, float y)
{
	mVertices[id][0] = x;
	mVertices[id][1] = y;
}

void CFigure::setBoxVertex(int id, float x, float y)
{
	bVertices[id][0] = x;
	bVertices[id][1] = y;
}

void CFigure::setbColor(float r, float g, float b)
{
	bColor[0] = r;
	bColor[1] = g;
	bColor[2] = b;
}

void CFigure::setColor(float r, float g, float b)
{
	mColor[0] = r;
	mColor[1] = g;
	mColor[2] = b;
}

void CFigure::setfColor(float r, float g, float b)
{
	fColor[0] = r;
	fColor[1] = g;
	fColor[2] = b;
}

int CFigure::getType()
{
	return mType;
}

float* CFigure::getVertex(int id)
{
	return mVertices[id];
}

float* CFigure::getColor()
{
	return mColor;
}

float* CFigure::getfColor()
{
	return fColor;
}

void CFigure::Figuresetfill(bool x) {
	bfill = x;
}

void CFigure::Figuresetbox(bool x) {
	bbox = x;
}

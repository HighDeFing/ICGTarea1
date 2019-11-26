#pragma once

#include <GLFW/glfw3.h>

enum FigureType
{
	NONE,
	LINE,
	QUAD,
	CIRCLE,
	TRIANGLE,
	ELIPSE
};

class CFigure
{
protected:
	float** mVertices, mColor[3], fColor[3];
	int mType;
	bool bfill = false;

public:
	CFigure();
	virtual ~CFigure();
	void setVertex(int id, float x, float y);
	void setColor(float r, float g, float b);
	void setfColor(float r, float g, float b);
	virtual void fill() = 0;
	virtual void display() = 0;
	void Figuresetfill(bool);
	int getType();
	float* getVertex(int id);
	float* getColor();
	float* getfColor();
};
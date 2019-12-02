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
	float** mVertices, **bVertices, mColor[3], fColor[3], bColor[3];
	int mType;
	bool bfill = false;
	bool bbox = true;

public:
	CFigure();
	virtual ~CFigure();
	void setVertex(int id, float x, float y);
	void setBoxVertex(int id, float x, float y);
	void setColor(float r, float g, float b);
	void setbColor(float r, float g, float b);
	void setfColor(float r, float g, float b);
	virtual void fill() = 0;
	virtual void display() = 0;
	virtual void box() = 0;
	void Figuresetfill(bool);
	void Figuresetbox(bool);
	int getType();
	float* getVertex(int id);
	float* getColor();
	float* getfColor();
};
#pragma once

#include <AntTweakBar/AntTweakBar.h>
#include <iostream>
#include <string>
#include "Figure.h"

using std::string;

//Singleton user interface class

class CEditInterface
{
private:
	static CEditInterface* mInterface; //Holds the instance of the class
	TwBar* mEditInterface;
	float mFigureColor[3], fFigureColor[3];
	float g_Rotation[4];
	string smFigureType;
	FigureType figuretype = LINE;
	TwEnumVal mFigureType_enumEV[6] = { {NONE, "NONE"}, {LINE, "LINE"}, {QUAD, "QUAD"}, {CIRCLE, "CIRCLE"}, {TRIANGLE, "TRIANGLE" }, {ELIPSE, "ELIPSE"} }; //iniit of all figures
	TwType mFigureType;

public:
	///Method to obtain the only instance of the calls
	static CEditInterface* Instance();
	~CEditInterface();
	void reshape();
	void show();
	void hide();
	void setFigureColor(float* color);
	void setFigureType(FigureType type);
	void setFColor(float* color);
	float* getFigureColor();
	FigureType getFigureSelected();
	bool bfill = true;
	void fillFigure(FigureType type);

private:
	///Private constructor
	CEditInterface();
};

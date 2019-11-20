#pragma once

#include <AntTweakBar/AntTweakBar.h>
#include <iostream>
#include <string>
#include "Figure.h"

using std::string;

//Singleton user interface class

class CUserInterface
{
private:
	static CUserInterface* mInterface; //Holds the instance of the class
	TwBar* mUserInterface;
	float mFigureColor[3];
	float g_Rotation[4];
	string smFigureType;
	FigureType figuretype = LINE;
	TwEnumVal mFigureType_enumEV[6] = { {NONE, "NONE"}, {LINE, "LINE"}, {QUAD, "QUAD"}, {CIRCLE, "CIRCLE"}, {TRIANGLE, "TRIANGLE" }, {ELIPSE, "ELIPSE"} }; //iniit of all figures
	TwType mFigureType;

public:
	///Method to obtain the only instance of the calls
	static CUserInterface* Instance();
	~CUserInterface();
	void reshape();
	void show();
	void hide();
	void setFigureColor(float* color);
	void setFigureType(string type);
	float* getFigureColor();
	FigureType getFigureSelected();
	void EditfigureInterface();

private:
	///Private constructor
	CUserInterface();
};
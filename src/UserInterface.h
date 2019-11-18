#pragma once

#include <AntTweakBar/AntTweakBar.h>
#include <iostream>
#include <string>

using std::string;

//Singleton user interface class

class CUserInterface
{
private:
	static CUserInterface* mInterface; //Holds the instance of the class
	TwBar* mUserInterface;
	float mFigureColor[3];
	float g_Rotation[4];
	string mFigureType;
	typedef enum { LINE, QUAD, TRIANGLE, CIRCLE } mFigure_enum;
	mFigure_enum mcurrent_mFigure_enum = LINE;
	TwType mFigureType_enum;

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

private:
	///Private constructor
	CUserInterface();
};
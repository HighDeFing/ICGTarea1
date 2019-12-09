#include "UserInterface.h"
#include "Figure.h"

extern int gWidth, gHeight;

string openfilename(const char* filter = "Figure (*.fig)\0", HWND owner = NULL) {
	OPENFILENAME ofn;
	char fileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";
	string fileNameStr;
	if (GetOpenFileName(&ofn))
		fileNameStr = fileName;
	return fileNameStr;
}

string savefilename(const char* filter = "Figure (*.fig)\0", HWND owner = NULL) {
	OPENFILENAME ofn;
	char fileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrDefExt = "";
	string fileNameStr;
	if (GetSaveFileName(&ofn))
		fileNameStr = fileName;
	return fileNameStr;
}
// Global static pointer used to ensure a single instance of the class.
CUserInterface* CUserInterface::mInterface = NULL;
string s1 = "figure";
/**
* Creates an instance of the class
*
* @return the instance of this class
*/
CUserInterface* CUserInterface::Instance()
{
	if (!mInterface)   // Only allow one instance of class to be generated.
		mInterface = new CUserInterface();

	return mInterface;
}

void TW_CALL savecallback(void* clientData) {
	string s3 = savefilename();
	if (!s3.empty()) {
		save(s3);
	}
}
void TW_CALL loadcallback(void* clientData) {
	string s2 = openfilename();
	if (!s2.empty())
	{
		load(s2);
	}
}

CUserInterface::CUserInterface()
{
	mUserInterface = TwNewBar("Figure");

	TwDefine("Figure refresh = '0.0001f'");
	TwDefine("Figure resizable = false");
	TwDefine("Figure fontresizable = false");
	TwDefine("Figure movable = true");
	TwDefine("Figure visible = true");
	TwDefine("Figure position = '20 20'");
	TwDefine("Figure size = '220 250'");



	mFigureType = TwDefineEnum("mFigureType", mFigureType_enumEV, 6);

	TwAddVarRW(mUserInterface, "Figure", mFigureType, &figuretype, "label='Type'");

	//TwAddVarRO(mUserInterface, "meshType", TW_TYPE_STDSTRING, &mFigureType, "label='Type' readonly=true");
	TwAddVarRW(mUserInterface, "color", TW_TYPE_COLOR3F, &mFigureColor[0], "label = 'Color'");
	TwAddVarRW(mUserInterface, "bgcolor", TW_TYPE_COLOR3F, &bgColor[0], "label = 'Background color'");
	TwAddButton(mUserInterface, "Guardar", savecallback, NULL, "label='Save'");
	TwAddButton(mUserInterface, "Cargar", loadcallback, NULL, "label='Load'");
	
	

}



CUserInterface::~CUserInterface()
{
}

void CUserInterface::reshape()
{
	TwWindowSize(gWidth, gHeight);
}

void CUserInterface::show()
{
	TwDefine("Figure visible = true");
}

void CUserInterface::hide()
{
	TwDefine("Figure visible = false");
}

void CUserInterface::setFigureColor(float* color)
{
	mFigureColor[0] = color[0];
	mFigureColor[1] = color[1];
	mFigureColor[2] = color[2];
}

void CUserInterface::setFigureType(FigureType type)
{
	figuretype = type;
}

float* CUserInterface::getFigureColor()
{
	return mFigureColor;
}

float* CUserInterface::getbgColor()
{
	return bgColor;
}

void CUserInterface::setbgColor(float* color)
{
	bgColor[0] = color[0];
	bgColor[1] = color[1];
	bgColor[2] = color[2];
}

FigureType CUserInterface::getFigureSelected() 
{
	return figuretype;
}

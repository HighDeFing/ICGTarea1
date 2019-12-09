#include "Main.h"
#include "Line.h"
#include "Quad.h"
#include "Circle.h"
#include "Elipse.h"
#include "Triangle.h"
#include "UserInterface.h"
#include "EditInterface.h"
#include "Windows.h"
#include "commdlg.h"

using std::vector;

GLFWwindow* gWindow;
int gWidth, gHeight;
bool gPress;
CUserInterface* userInterface;
CEditInterface* editInterface;
vector <CFigure*> figures;
FigureType figureSelected;
int picked;
bool trian = false;
bool ispicked = false;
FILE* doc;

float* bgColor = new float [3]; 

CFigure* L, * B;
float *ve1, *ve2, *ve3;
float* veb1, * veb2, * veb3;

float py, px;

float* b1;
float* b2;

void pick(int x, int y)
{
	
	picked = -1;
	ispicked = false;
	editInterface->show();
	for (unsigned int i = 0; i < figures.size(); i++)
	{
		figures[i]->Figuresetbox(false); //disapear box at the beginnig
		float* v1 = figures[i]->getVertex(0);  //v1[0]=x1 v2[0]=x2
		float* v2 = figures[i]->getVertex(1);	//v1[1]=y2 v2[1]=y2 
		float max[2];		//max[0]=max(x) max[1]=max(y)
		float min[2];		//min[0]=min(x) min[1]=min(y)

		// This should be precalculated

		/*max[0] = MAX(v1[0], v2[0]);
		max[1] = MAX(v1[1], v2[1]);

		min[0] = MIN(v1[0], v2[0]);
		min[1] = MIN(v1[1], v2[1]);*/
		if (figures[i]->getType() == LINE) {
			max[0] = MAX(v1[0], v2[0]);
			max[1] = MAX(v1[1], v2[1]);

			min[0] = MIN(v1[0], v2[0]);
			min[1] = MIN(v1[1], v2[1]);
			float* v1 = figures[i]->getVertex(0);  //v1[0]=x1 v2[0]=x2
			float* v2 = figures[i]->getVertex(1);	//v1[1]=y2 v2[1]=y2

			figures[i]->setBoxVertex(0, min[0], min[1]); //creates bounding box
			figures[i]->setBoxVertex(1, max[0], max[1]); //creates bounding box
		}
		if (figures[i]->getType() == QUAD) {
			max[0] = MAX((v1[0] + 10), (v2[0] + 10));
			max[1] = MAX((v1[1] + 10), (v2[1] + 10));

			min[0] = MIN((v1[0] - 10), (v2[0] - 10));
			min[1] = MIN((v1[1] - 10), (v2[1] - 10));
			float* v1 = figures[i]->getVertex(0);  //v1[0]=x1 v2[0]=x2
			float* v2 = figures[i]->getVertex(1);	//v1[1]=y2 v2[1]=y2

			figures[i]->setBoxVertex(0, min[0], min[1]); //creates bounding box
			figures[i]->setBoxVertex(1, max[0], max[1]); //creates bounding box
		}
		if (figures[i]->getType() == CIRCLE) {
			int r = sqrt(pow((v1[0] - v2[0]), 2) + pow((v1[1] - v2[1]), 2));
			max[0] = v1[0] + r; max[1] = v1[1] + r;
			min[0] = v1[0] - r; min[1] = v1[1] - r;
			float* v1 = figures[i]->getVertex(0);  //v1[0]=x1 v2[0]=x2
			float* v2 = figures[i]->getVertex(1);	//v1[1]=y2 v2[1]=y2

			figures[i]->setBoxVertex(0, min[0], min[1]); //creates bounding box
			figures[i]->setBoxVertex(1, max[0], max[1]); //creates bounding box
		}
		if (figures[i]->getType() == ELIPSE) {
	
			float a[2];
			a[0] = abs(v1[0] - v2[0]); a[1] = abs(v1[1] - v2[1]);
			if (v1[0] <= v2[0] && v1[1] <= v2[1]) {
				min[0] = v2[0] - 2 * a[0];
				max[0] = v2[0];  
				min[1] = v2[1] - 2 * a[1];//above the center and right
				max[1] = v2[1]; 
			}
			if (v1[0] < v2[0] && v1[1] > v2[1]) {
				min[0] = v2[0] - 2 * a[0];
				max[0] = v2[0];               //bellow the center and right
				min[1] = v2[1]; 
				max[1] = v2[1] + 2 * a[1];
			}
			if (v1[0] >= v2[0] && v1[1] <= v2[1]) {
				min[0] = v2[0];
				max[0] = v2[0] + 2 * a[0];
				min[1] = v2[1] - 2 * a[0]; //above the center and left
				max[1] = v2[1];
			}
			if (v1[0] > v2[0] && v1[1] > v2[1]) {
				min[0] = v2[0];
				max[0] = v2[0] + 2 * a[0];
				min[1] = v2[1];					//bellow the center and left
				max[1] = v2[1] + 2 * a[0];
			}
			figures[i]->setBoxVertex(0, min[0], min[1]); //creates bounding box
			figures[i]->setBoxVertex(1, max[0], max[1]); //creates bounding box

		}
		if (figures[i]->getType() == TRIANGLE) {
			float* v3 = figures[i]->getVertex(2);

			max[0] = MAX(MAX(MAX(v1[0], v2[0]), MAX(v1[0], v3[0])), MAX(MAX(v2[0], v3[0]), MAX(v1[0], v2[0])));
			max[1] = MAX(MAX(MAX(v1[1], v2[1]), MAX(v1[1], v3[1])), MAX(MAX(v2[1], v3[1]), MAX(v1[1], v2[1])));
			min[0] = MIN(MIN(MIN(v1[0], v2[0]), MIN(v1[0], v3[0])), MIN(MIN(v2[0], v3[0]), MIN(v1[0], v2[0])));
			min[1] = MIN(MIN(MIN(v1[1], v2[1]), MIN(v1[1], v3[1])), MIN(MIN(v2[1], v3[1]), MIN(v1[1], v2[1])));
			figures[i]->setBoxVertex(0, min[0], min[1]); //creates bounding box
			figures[i]->setBoxVertex(1, max[0], max[1]); //creates bounding box
		}
		if (x >= min[0] && x <= max[0] && y >= min[1] && y <= max[1])
		{
			picked = i;
			ispicked = true;
			figures[picked]->Figuresetbox(true);
			editInterface->setBox(true);
			editInterface->setFigureColor(figures[picked]->getColor());
			editInterface->setFColor(figures[picked]->getfColor());
			ve1 = figures[picked]->getVertex(0);
			ve2 = figures[picked]->getVertex(1);
			if (figures[picked]->getType() == TRIANGLE) {
				ve3 = figures[picked]->getVertex(2);
			}
			veb1 = figures[picked]->getBoxVertex(0);
			veb2 = figures[picked]->getBoxVertex(1);
			int type = figures[picked]->getType();
			switch(type)
			{
			case LINE:editInterface->setFigureType(LINE);
				break;
			case QUAD:editInterface->setFigureType(QUAD);
				break;
			case TRIANGLE:editInterface->setFigureType(TRIANGLE);
				break;
			case CIRCLE:editInterface->setFigureType(CIRCLE);
				break;
			case ELIPSE:editInterface->setFigureType(ELIPSE);
				break;
			default:
				editInterface->setFigureType(NONE);
			}
		}
	}
}

void updateUserInterface()
{
	if (picked < -1)
	{
		float* color = userInterface->getFigureColor(); //line color with useriterface
		figures[picked]->setColor(color[0], color[1], color[2]);
	}
}

void updateEditInterface() {
	if (picked > -1 && ispicked)
	{
		editInterface->show();  //Show edit interface when clicked
		/*float* ecolor = editInterface->getFigureColor();
		figures[picked]->setColor(ecolor[0], ecolor[1], ecolor[2]); //line color

		float* fcolor = editInterface->getFigureFColor();
		figures[picked]->setfColor(fcolor[0], fcolor[1], fcolor[2]); //fill color
		*/
		
		editInterface->setFill(figures[picked]->getbfill()); //set if fill don't know why it works but it works lmao.

		figures[picked]->Figuresetbox(editInterface->getBox()); //set if bounding box

	}
	else if (!ispicked && picked < -1) {
		editInterface->hide(); //hide edit interface when not cliking on a figure
		editInterface->setFigureType(NONE);
	}
	if (picked > -1) {
		float* ecolor = editInterface->getFigureColor();
		figures[picked]->setColor(ecolor[0], ecolor[1], ecolor[2]); //line color

		float* fcolor = editInterface->getFigureFColor();
		figures[picked]->setfColor(fcolor[0], fcolor[1], fcolor[2]); //fill color

		figures[picked]->Figuresetfill(editInterface->getFill()); //set if fill but only on one figure properties.

		figures[picked]->Figuresetbox(editInterface->getBox()); //set if bounding box
	}
	else {
		editInterface->hide(); //hide edit interface when not cliking on a figure
		editInterface->setFigureType(NONE);
	}
	
}


void save(string S) {
	//S = S + ".Fig";
	char s[1024];
	strncpy_s(s, S.c_str(), sizeof(s));
	s[sizeof(s) - 1] = 0;
	fopen_s(&doc, s, "w+");
	int ti;
	float* col, *fcol, *bg;
	float* aux;
	int bfill;
	

	for (unsigned int i = 0; i < figures.size(); i++) {
		ti = figures[i]->getType();
		col = figures[i]->getColor();
		fcol = figures[i]->getfColor();
		bfill = int(figures[i]->getbfill());
		bg = userInterface->getbgColor();
		fprintf(doc, "%i %i %f %f %f %f %f %f ", ti, bfill, col[0], col[1], col[2], fcol[0], fcol[1], fcol[2]);
		fprintf(doc, "%f %f %f ", bg[0], bg[1], bg[2]);
		for (int j = 0;j < 2;j++) {
			aux = figures[i]->getVertex(j);
			fprintf(doc, "%f %f ", aux[0], aux[1]);
		}
		if (ti == TRIANGLE) {
			aux = figures[i]->getVertex(2);
			fprintf(doc, "%f %f\n", aux[0], aux[1]);
		}
		else fprintf(doc, "\n");
	}
	fclose(doc);

}

void load(string S) {
	figures.clear();
	//S = S + ".Fig";
	char s[1024];
	strncpy_s(s, S.c_str(), sizeof(s));
	s[sizeof(s) - 1] = 0;
	fopen_s(&doc, s, "r");
	if (doc == NULL) return;
	int ti = 0;
	float aux[2];
	float col[3];
	float fcol[3];
	float bg[3];
	int bfill;
	while (!feof(doc)) {

		fscanf_s(doc, "%i", &ti, sizeof(ti));
		fscanf_s(doc, "%i", &bfill, sizeof(bfill));

		fscanf_s(doc, "%f", &col[0], sizeof(col[0]));
		fscanf_s(doc, "%f", &col[1], sizeof(col[1]));
		fscanf_s(doc, "%f", &col[2], sizeof(col[2]));

		fscanf_s(doc, "%f", &fcol[0], sizeof(fcol[0]));
		fscanf_s(doc, "%f", &fcol[1], sizeof(fcol[1]));
		fscanf_s(doc, "%f", &fcol[2], sizeof(fcol[2]));

		fscanf_s(doc, "%f", &bg[0], sizeof(bg[0]));
		fscanf_s(doc, "%f", &bg[1], sizeof(bg[1]));
		fscanf_s(doc, "%f", &bg[2], sizeof(bg[2]));

		switch (ti) {
		case LINE:L = new CLine();
			break;
		case TRIANGLE:
			L = new CTriangle();
			trian = true;
			break;
		case QUAD:L = new CQuad();
			break;
		case CIRCLE:L = new CCircle();
			break;
		case ELIPSE:L = new CElipse();
			break;

		}
		userInterface->setbgColor(bg);
		L->Figuresetfill(bfill);
		L->setfColor(fcol[0], fcol[1], fcol[2]);
		L->setColor(col[0], col[1], col[2]);
		for (int j = 0;j < 2;j++) {
			fscanf_s(doc, "%f %f ", &aux[0], &aux[1], sizeof(aux[0]), sizeof(aux[1]));
			L->setVertex(j, aux[0], aux[1]);
		}
		if (trian) {
			fscanf_s(doc, "%f %f ", &aux[0], &aux[1], sizeof(aux[0]), sizeof(aux[1]));
			L->setVertex(2, aux[0], aux[1]);
			trian = false;
		}
		figures.push_back(L);
	}
	fclose(doc);
}

void display()
{
	float* bgc;
	bgc = userInterface->getbgColor();
	glClearColor(bgc[0], bgc[1], bgc[2], 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	if (!figures.empty()) {
		for (unsigned int i = 0; i < figures.size(); i++)
			figures[i]->display();
	}

}

void reshape(GLFWwindow* window, int width, int height)
{
	gWidth = width;
	gHeight = height;

	glViewport(0, 0, gWidth, gHeight);

	userInterface->reshape();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, gWidth, 0, gHeight, -1.0f, 1.0f);
}

void keyInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (TwEventKeyGLFW(key, action))
		return;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;

		case GLFW_KEY_P:
			figureSelected = NONE;
			break;

		case GLFW_KEY_L:
			figureSelected = LINE;
			break;

		case GLFW_KEY_Q:
			figureSelected = QUAD;
			break;

		case GLFW_KEY_PAGE_DOWN:
			if (picked > -1) {
				if (figures.size() > 1) {
					//figures.push_back(figures[picked]);
					if (figures[picked] != figures.front()) {
						std::iter_swap(figures.begin() + picked, figures.begin() + (picked - 1));
						picked = -1;
					}
				}
			}
			break;

		case GLFW_KEY_PAGE_UP:
			if (picked > -1) {
				if (figures.size() > 1) {
					//figures.push_back(figures[picked]);
					if (figures[picked] != figures.back()) {
						std::iter_swap(figures.begin() + picked, figures.begin() + (picked + 1));
						picked = -1;
					}
				}
			}
			break;

		case GLFW_KEY_DELETE:
			if (picked > -1) {
				figures[picked]->~CFigure();
				figures.erase(figures.begin() + picked);
				picked = -1;
			}
			break;
		}
	}
}

void mouseButton(GLFWwindow* window, int button, int action, int mods)
{
	float * Color;
	float max[2];		//max[0]=max(x) max[1]=max(y)
	float min[2];		//min[0]=min(x) min[1]=min(y)
	if (TwEventMouseButtonGLFW(button, action)) {
		figureSelected = userInterface->getFigureSelected(); //get figure selected and put it on figure
		return;
	}
	double x, y;
	glfwGetCursorPos(gWindow, &x, &y);

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && !gPress)
	{
		float ax = float(x);
		float ay = gHeight - float(y);
		//py = ay + gHeight;
		if (figureSelected == NONE) {
			px = ax; py = gHeight - ay;
			pick(int(ax), int(ay));
			editInterface->show();
			return;
		}

		if (trian) {
			figures.back()->setVertex(1, ax, ay);
			trian = false;
		}
		else if (figureSelected == LINE)
		{
			CLine* line = new CLine();
			line->setVertex(0, ax, ay);
			line->setVertex(1, ax, ay);

			userInterface->setFigureType(LINE);
			Color = userInterface->getFigureColor();
			line->setColor(Color[0], Color[1], Color[2]);
			figures.push_back(line);
			gPress = true;
		}
		else if (figureSelected == QUAD)
		{
			CQuad* quad = new CQuad();
			quad->setVertex(0, ax, ay);
			quad->setVertex(1, ax, ay);
			quad->fill();
			userInterface->setFigureType(QUAD);
			Color = userInterface->getFigureColor();
			quad->setfColor(Color[0], Color[1], Color[2]);
			quad->setColor(Color[0], Color[1], Color[2]);
			figures.push_back(quad);

			gPress = true;
		}
		else if (figureSelected == CIRCLE)
		{
			CCircle* circle = new CCircle();
			circle->setVertex(0, ax, ay);
			circle->setVertex(1, ax, ay);
			userInterface->setFigureType(CIRCLE);
			Color = userInterface->getFigureColor();
			circle->setColor(Color[0], Color[1], Color[2]);
			figures.push_back(circle);
			gPress = true;
		}
		else if (figureSelected == ELIPSE) {
			CElipse* elipse = new CElipse();
			elipse->setVertex(0, ax, ay);
			elipse->setVertex(1, ax, ay);
			userInterface->setFigureType(ELIPSE);
			Color = userInterface->getFigureColor();
			elipse->setColor(Color[0], Color[1], Color[2]);
			figures.push_back(elipse);
			gPress = true;
		}
		else if (figureSelected == TRIANGLE) {
			CTriangle* triangle = new CTriangle();
			triangle->setVertex(0, ax, ay);
			triangle->setVertex(1, ax, ay);
			triangle->setVertex(2, ax, ay);
			userInterface->setFigureType(TRIANGLE);
			Color = userInterface->getFigureColor();
			triangle->setColor(Color[0], Color[1], Color[2]);
			figures.push_back(triangle);
			gPress = true;
			trian = true;
		}
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		gPress = false;
		//picked = -1;
		ispicked = false;
	}
}

void cursorPos(GLFWwindow* window, double x, double y)
{
	if (TwEventMousePosGLFW(int(x), int(y)))
		return;
	if (picked > -1 && ispicked) {
		long float Tx = (x - px);
		long float Ty = (y - py);
		figures[picked]->setVertex(0, ve1[0] + (Tx), ve1[1] - (Ty));
		figures[picked]->setVertex(1, ve2[0] + (Tx), ve2[1] - (Ty));
		figures[picked]->setBoxVertex(0, veb1[0] + (Tx), veb1[1] - (Ty));
		figures[picked]->setBoxVertex(1, veb2[0] + (Tx), veb2[1] - (Ty));
		if ((figures[picked]->getType()) == TRIANGLE) {
			figures[picked]->setVertex(2, ve3[0] + (Tx), ve3[1] - (Ty));
		}
		px = x;
		py = y;
	}
	if (gPress)
	{
		float ax = float(x);
		float ay = gHeight - float(y);
		figures.back()->setVertex(1, ax, ay);
		if (trian) {
			figures.back()->setVertex(2, ax, ay);
		}
	}
}

void charInput(GLFWwindow* window, unsigned int scanChar)
{
	if (TwEventCharGLFW(scanChar, GLFW_PRESS))
		return;
}

void destroy()
{
	for (unsigned int i = 0; i < figures.size(); i++)
		delete figures[i];

	delete userInterface;

	TwTerminate();
	glfwDestroyWindow(gWindow);
	glfwTerminate();
}

bool initGlfw()
{
	if (!glfwInit())
		return false;

	gWindow = glfwCreateWindow(gWidth, gHeight, "ICG - Plantilla", NULL, NULL);

	if (!gWindow)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(gWindow);

	const GLFWvidmode* vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(gWindow, (vidMode->width - gWidth) >> 1, (vidMode->height - gHeight) >> 1);

	glfwSetWindowSizeCallback(gWindow, reshape);
	glfwSetKeyCallback(gWindow, keyInput);
	glfwSetMouseButtonCallback(gWindow, mouseButton);
	glfwSetCursorPosCallback(gWindow, cursorPos);
	glfwSetCharCallback(gWindow, charInput);

	return true;
}

bool initUserInterface()
{
	if (!TwInit(TW_OPENGL, NULL))
		return false;

	userInterface = CUserInterface::Instance();
	editInterface = CEditInterface::Instance();
	bgColor[0] = 1.0;
	bgColor[1] = 1.0;
	bgColor[2] = 1.0;
	userInterface->setbgColor(bgColor);
	return true;
}

int main(void)
{
	gWidth = 1200;
	gHeight = 680;
	gPress = false;
	figureSelected = LINE;
	picked = -1;

	if (!initGlfw() || !initUserInterface())
		return EXIT_FAILURE;

	reshape(gWindow, gWidth, gHeight);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	while (!glfwWindowShouldClose(gWindow))
	{
		display();


		TwDraw();

		updateUserInterface();

		updateEditInterface();

		glfwSwapBuffers(gWindow);

		glfwPollEvents();
	}

	destroy();

	return EXIT_SUCCESS;
}
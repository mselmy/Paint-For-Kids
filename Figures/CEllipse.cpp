#include "../Figures/CEllipse.h"
#include "CFigure.h"
#include <fstream>
#include <iostream>

CEllipse::CEllipse(Point _P1, Point _P2, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	P1 = _P1;
	P2 = _P2;
}
//CEllipse::CEllipse() {}
void CEllipse::SetID(int id)
{
	ID = id;
}
void CEllipse::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawCircle to draw a Circle on the screen	
	pGUI->DrawEllipse(P1, P2, FigGfxInfo, Selected);
}

bool CEllipse::IsPointInside(int x, int y) const	//whether the point is inside the figure or not
{
	// get ellipse center
    float centerX = (P1.x + P2.x) / 2;
    float centerY = (P1.y + P2.y) / 2;

	// get ellipse axes
    float a = abs(P2.x - P1.x) / 2;
    float b = abs(P2.y - P1.y) / 2;

	// check if point is inside ellipse
    float dx = x - centerX;
    float dy = y - centerY;

    return ((dx * dx) / (a * a) + (dy * dy) / (b * b)) <= 1;
}

void CEllipse::Save(ofstream& OutFile)	//Save the figure parameters to the file
{
    OutFile << endl << ITM_ELPS << "\t" << ID << "\t" << P1.x << "\t" << P1.y << "\t" << P2.x << "\t" << P2.y << "\t";
	OutFile << "(" << (int)FigGfxInfo.DrawClr.ucRed << "," << (int)FigGfxInfo.DrawClr.ucGreen << "," << (int)FigGfxInfo.DrawClr.ucBlue << ")" << "\t";
	if (FigGfxInfo.isFilled)
		OutFile << "(" << (int)FigGfxInfo.FillClr.ucRed << "," << (int)FigGfxInfo.FillClr.ucGreen << "," << (int)FigGfxInfo.FillClr.ucBlue << ")" << endl;
	else
		OutFile << "NO_FILL";
}
void CEllipse::Load(ifstream& Infile)	//Load the figure parameters to the file
{
	// Declare variables for x, y, len, drawColorString, and fill
	string drawColorString, fill;

	// Read values from the file into object data members
	Infile >> ID;
	Infile >> P1.x;
	Infile >> P1.y;
	Infile >> P2.x;
	Infile >> P2.y;
	Infile >> drawColorString >> fill;//read colors from file into strings first to convert to color later

	seTDrawandFillClr(drawColorString, fill); //set the draw and fill colors
}
CEllipse* CEllipse::Clone() const
{
	return new CEllipse(*this);
}
void CEllipse::ActionResizeFigure(GUI* pGUI, float size) {


	Point point1 = P1, point2 = P2;
	if (size == .5) size = -0.5;
	else if (size == .25) size = -(4.0 / 3);
	else if (size == 2) size = 1;
	else size = 4;
	// half radius (horizontal x && vertical y)
	float deltaX, deltaY;
	deltaX = 0.5 * (P2.x - P1.x);
	deltaY = 0.5 * (P2.y - P1.y);
	//new width and height based on the resizing factor
	point1.x -= deltaX * size;
	point2.x += deltaX * size;
	point1.y -= deltaY * size;
	point2.y += deltaY * size;
	//check if size of elipse is larger than the draw area
	if (point1.y < UI.ToolBarHeight || point2.y > UI.height - UI.StatusBarHeight
		|| point2.x > UI.width || point1.x < 1)
	{
		pGUI->PrintMessage("Ellips size will be more than Drawing Area:)");
	}
	else
	{
		//updating the two points
		P1 = point1;
		P2 = point2;

	}
}

void CEllipse::move(int& dx, int& dy)
{
	//changing drawing point
	P1.x += dx;
	P1.y += dy;
	P2.x += dx;
	P2.y += dy;
}
int CEllipse::type()
{
	return PELLIPSE;
			
}
#include "CSquare.h"
#include <fstream>
#include <iostream>

using namespace std;


CSquare::CSquare(Point P1, int len, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	length = len;
}

void CSquare::SetID(int id)
{
	ID = id;
}
void CSquare::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawSquare(TopLeftCorner, length, FigGfxInfo, Selected);
}

// Check if the point is inside the square or not
bool CSquare::IsPointInside(int x, int y) const
{
	if (x >= TopLeftCorner.x && x <= TopLeftCorner.x + length && y >= TopLeftCorner.y && y <= TopLeftCorner.y + length)
		return true;
	return false;
}

// save the square parameters to the file
void CSquare::Save(ofstream& OutFile)
{
	OutFile << endl << ITM_SQUR <<"\t" << ID << "\t" << TopLeftCorner.x << "\t" << TopLeftCorner.y << "\t" << length << "\t";
	OutFile << "(" << (int)FigGfxInfo.DrawClr.ucRed << "," << (int)FigGfxInfo.DrawClr.ucGreen << "," << (int)FigGfxInfo.DrawClr.ucBlue << ")" << "\t";
	if (FigGfxInfo.isFilled)
		OutFile << "(" << (int)FigGfxInfo.FillClr.ucRed << "," << (int)FigGfxInfo.FillClr.ucGreen << "," << (int)FigGfxInfo.FillClr.ucBlue << ")" << endl;
	else
		OutFile << "NO_FILL";
}

//load the square parameters from the file
void CSquare::Load(ifstream& Infile)
{
	// Declare variables for x, y, len, drawColorString, and fill
	int x, y, len;
	string drawColorString, fill;

	// Read values from the file into object data members
	Infile >> ID;
	Infile >> TopLeftCorner.x;
	Infile >> TopLeftCorner.y;
	Infile >> length;
	Infile >> drawColorString >> fill;//read colors from file into strings first to convert to color later

	seTDrawandFillClr(drawColorString, fill); //set the draw and fill colors
}
CSquare* CSquare::Clone() const {
	return new CSquare(*this);
}
void CSquare::ActionResizeFigure(GUI* pGUI, float size) {
	// Store the original length
	float length_test = length;
	// Store the original point
	Point point1 = TopLeftCorner;
	Point point2;
	point2.x = point1.x + length;
	point2.y = point1.y + length;
	// Calculate the new length based on the size factor
	length_test *= size;
	// Calculate the coordinates of the opposite corner after resizin
	point2.x = point1.x + length_test;
	point2.y = point1.y + length_test;

	// Update the coordinates of the square
	TopLeftCorner = point1;
	//check if square size is larger than the Area.
	if (point1.y < UI.ToolBarHeight || point2.y > UI.height - UI.StatusBarHeight
		|| point2.x > UI.width || point1.x < 1)
	{
		pGUI->PrintMessage("Square size will be more than Drawing Area:)");

	}
	else
	{
		// Update the coordinates of the square
		TopLeftCorner = point1;
		length = length_test;
	}
}

void CSquare::move(int& dx, int& dy)
{
	//changing drawing point
	TopLeftCorner.x += dx;
	TopLeftCorner.y += dy;
}
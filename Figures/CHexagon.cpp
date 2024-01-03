#include "CHexagon.h"
#include <fstream>
#include <iostream>
#include "..\ApplicationManager.h"
CHexagon::CHexagon(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	BottomRightCorner = P2;
	VerticalLen = abs(P1.y - P2.y);
	HorizentalLen = abs(P1.x - P2.x);
}


void CHexagon::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawHexagon(TopLeftCorner, BottomRightCorner, FigGfxInfo, Selected);
}

bool CHexagon::IsPointInside(int x, int y) const	//whether the point is inside the figure or not
{
	// Check if the point is inside the hexagon or not
	if (x >= TopLeftCorner.x && x <= BottomRightCorner.x && y >= TopLeftCorner.y && y <= BottomRightCorner.y)
		return true;
	return false;
}

void CHexagon::Save(ofstream& OutFile)	//Save the figure parameters to the file
{
	OutFile << endl << ITM_HEXA << "\t" << ID << "\t" << TopLeftCorner.x << "\t" << TopLeftCorner.y << "\t" << BottomRightCorner.x << "\t" << BottomRightCorner.y << "\t";
	OutFile << "(" << (int)FigGfxInfo.DrawClr.ucRed << "," << (int)FigGfxInfo.DrawClr.ucGreen << "," << (int)FigGfxInfo.DrawClr.ucBlue << ")" << "\t";
	if (FigGfxInfo.isFilled)
		OutFile << "(" << (int)FigGfxInfo.FillClr.ucRed << "," << (int)FigGfxInfo.FillClr.ucGreen << "," << (int)FigGfxInfo.FillClr.ucBlue << ")" << endl;
	else
		OutFile << "NO_FILL";
}
void CHexagon::Load(ifstream& Infile)	//Load the figure parameters to the file
{
	// Declare variables for x, y, len, drawColorString, and fill
	string drawColorString, fill;

	// Read values from the file into object data members
	Infile >> ID;
	Infile >> TopLeftCorner.x;
	Infile >> TopLeftCorner.y;
	Infile >> BottomRightCorner.x;
	Infile >> BottomRightCorner.y;
	Infile >> drawColorString >> fill;//read colors from file into strings first to convert to color later

	seTDrawandFillClr(drawColorString, fill); //set the draw and fill colors
}
void CHexagon::ActionResizeFigure(GUI* pGUI, float size) {//resize hexagon
	Point point1 = TopLeftCorner;
	Point point2 = BottomRightCorner;

	if (size == 0.5) size = -0.5;
	else if (size == 0.25) size = -(4.0 / 3);
	else if (size == 2) size = 1;
	else size = 4;

	// Calculate half of the horizontal and vertical lengths
	float deltaX = 0.5 * (point2.x - point1.x);
	float deltaY = 0.5 * (point2.y - point1.y);

	// Calculate new coordinates based on the resizing factor
	point1.x -= deltaX * size;
	point2.x += deltaX * size;
	point1.y -= deltaY * size;
	point2.y += deltaY * size;

	// Check if the resized hexagon is within the drawing area
	if (point1.y < UI.ToolBarHeight || point2.y > UI.height - UI.StatusBarHeight ||
		point2.x > UI.width || point1.x < 1)
	{
		pGUI->PrintMessage("Hexagon size will be more than Drawing Area:)");
	}
	else {
		// Update the TopLeftCorner and BottomRightCorner
		TopLeftCorner = point1;
		BottomRightCorner = point2;
	}
}

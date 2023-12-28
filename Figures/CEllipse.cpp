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
		OutFile << FigGfxInfo.FillClr.ucRed << "\t" << FigGfxInfo.FillClr.ucGreen << "\t" << FigGfxInfo.FillClr.ucBlue << "\t";
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

	// Convert the drawColorString to a color and assign it to FigGfxInfo.DrawClr
	FigGfxInfo.DrawClr = stringToColor(drawColorString);

	// Check if the fill is "NO_FILL"
	if (fill == "NO_FILL") {
		FigGfxInfo.isFilled = false;
		FigGfxInfo.FillClr = NULL;
	}
	else
	{
		// Convert the fill to a color and assign it to FigGfxInfo.FillClr
		FigGfxInfo.isFilled = true;
		FigGfxInfo.FillClr = stringToColor(fill);
	}
}
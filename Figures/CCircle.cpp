#include "CCircle.h"
#include <fstream>
#include <iostream>


CCircle::CCircle(Point P1, int _radius, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	center = P1;
	radius = _radius;
	
}


void CCircle::DrawMe(GUI* pGUI) const 
{
	//Call Output::DrawCircle to draw a Circle on the screen	
	pGUI->DrawCircle(center, radius, FigGfxInfo, Selected);
}

bool CCircle::IsPointInside(int x, int y) const	//whether the point is inside the figure or not
{
    int distanceSquared = (x - center.x) * (x - center.x) + (y - center.y) * (y - center.y);
    return distanceSquared <= radius * radius;
}

void CCircle::Save(ofstream& OutFile)	//Save the figure parameters to the file
{
	OutFile << endl << ITM_CIRC << "\t" << ID << "\t" << center.x << "\t" << center.y << "\t" << radius << "\t";
	OutFile << "(" << (int)FigGfxInfo.DrawClr.ucRed << "," << (int)FigGfxInfo.DrawClr.ucGreen << "," << (int)FigGfxInfo.DrawClr.ucBlue << ")" << "\t";
	if (FigGfxInfo.isFilled)
		OutFile << FigGfxInfo.FillClr.ucRed << "\t" << FigGfxInfo.FillClr.ucGreen << "\t" << FigGfxInfo.FillClr.ucBlue << "\t";
	else
		OutFile << "NO_FILL" << "\t";
	OutFile << endl;
}
void CCircle::Load(ifstream& Infile)	//Load the figure parameters to the file
{
	// Declare variables for x, y, len, drawColorString, and fill
	int x, y;
	string drawColorString, fill;

	// Read values from the file into object data members
	Infile >> ID;
	Infile >> center.x;
	Infile >> center.y;
	Infile >> radius;
	Infile >> drawColorString; //read colors from file into strings first to convert to color later
	Infile >> fill;

	// Convert the drawColorString to a color and assign it to FigGfxInfo.DrawClr
	ChngDrawClr(stringToColor(drawColorString));

	// Check if the fill is "NO_FILL"
	if (fill == "NO_FILL") {
		FigGfxInfo.isFilled = false;
		FigGfxInfo.FillClr = NULL;
	}
	else
	{
		// Convert the fill to a color and assign it to FigGfxInfo.FillClr
		FigGfxInfo.isFilled = true;
		ChngFillClr(stringToColor(fill));
	}
}
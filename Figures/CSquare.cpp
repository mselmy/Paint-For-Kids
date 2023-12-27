#include "CSquare.h"
#include <fstream>
#include <iostream>

using namespace std;

color CSquare::stringToColor(string s)
{
		int r, g, b;
	int i = 1;
	string temp = "";
	while (s[i] != ',')
	{
				temp += s[i];
		i++;
	}
	r = stoi(temp);
	i++;
	temp = "";
	while (s[i] != ',')
	{
				temp += s[i];
		i++;
	}
	g = stoi(temp);
	i++;
	temp = "";
	while (s[i] != ')')
	{
				temp += s[i];
		i++;
	}
	b = stoi(temp);
	color c;
	c.ucRed = r;
	c.ucGreen = g;
	c.ucBlue = b;
	return c;
}

CSquare::CSquare(Point P1, int len, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	length = len;
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
	OutFile << endl << SQUARE <<"\t" << ID << "\t" << TopLeftCorner.x << "\t" << TopLeftCorner.y << "\t" << length << "\t";
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


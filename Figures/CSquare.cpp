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
		int x, y, len;
	string drawColorString, fill;
/**
 *
		string id;
		cout << "ID: " << ID;

		Infile >> ID;
 */
		cout << "ID: "<<ID;
		Infile >> ID;
		Infile >> TopLeftCorner.x;
		Infile >> TopLeftCorner.y;
		Infile >> length;
		Infile >> drawColorString >> fill;

	cout<<"\nID: "<<ID;
	cout<< "\nTopLeftCorner.x: "<<TopLeftCorner.x;
	cout<< "\nTopLeftCorner.y: "<<TopLeftCorner.y;
	cout<< "\n length: "<<length;
		cout<< "\n color: "<< drawColorString;
		cout<< "\n fill: "<<fill;
		 stringToColor(drawColorString);

	FigGfxInfo.DrawClr = stringToColor(drawColorString);
	if (fill == "NO_FILL") {
		FigGfxInfo.isFilled = false;
		FigGfxInfo.FillClr = NULL;// stringToColor(drawColorString);
	}
	else
	{
		FigGfxInfo.isFilled = true;
		FigGfxInfo.FillClr = stringToColor(fill);
	}
	//FigGfxInfo.BorderWdth sent current from appmanager (GUI) if we want other border width change save and load
	/*
	 *fill color  = (255,255,255)
	 *r = 255 , g = 255 , b = 255
	 *better use a function to convert string to color
	 *even better use enum for colors
	 *
	 *
		color FillColor;
		FillColor.ucRed = r;
		FillColor.ucGreen = g;
		FillColor.ucBlue = b;
		FigGfxInfo.FillClr = FillColor;
		FigGfxInfo.isFilled = true;
	 *
	 */
}


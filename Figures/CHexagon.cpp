#include "CHexagon.h"
#include <fstream>
#include <iostream>
#include "..\ApplicationManager.h"
CHexagon::CHexagon(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	VerticalLen = abs(P1.y - P2.y);
	HorizentalLen = abs(P1.x - P2.x);
	BottomRightCorner = P2;

}


void CHexagon::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawHexagon(TopLeftCorner, BottomRightCorner, FigGfxInfo, Selected);
}

bool CHexagon::IsPointInside(int x, int y) const	//whether the point is inside the figure or not
{
	{
		int lengthx = abs(TopLeftCorner.x - BottomRightCorner.x);
		int lengthy = abs(TopLeftCorner.y - BottomRightCorner.y);

		int xCenter = (BottomRightCorner.x + TopLeftCorner.x) / 2;
		int yCenter = (BottomRightCorner.y + TopLeftCorner.y) / 2;

		int arrx[6] = { TopLeftCorner.x,TopLeftCorner.x + lengthx, TopLeftCorner.x + 1.5 * lengthx,TopLeftCorner.x + lengthx,TopLeftCorner.x,TopLeftCorner.x - 0.5 * lengthx };
		int arry[6] = { TopLeftCorner.y,TopLeftCorner.y,TopLeftCorner.y + 0.5 * lengthy,TopLeftCorner.y + lengthy,TopLeftCorner.y + lengthy,TopLeftCorner.y + 0.5 * lengthy };

		float areax1 = (0.5) * abs(x * (arry[0] - arry[1]) + arrx[0] * (arry[1] - y) + arrx[1] * (y - arry[0]));
		float areax2 = (0.5) * abs(x * (arry[1] - arry[2]) + arrx[1] * (arry[2] - y) + arrx[2] * (y - arry[1]));
		float areax3 = (0.5) * abs(x * (arry[2] - arry[3]) + arrx[2] * (arry[3] - y) + arrx[3] * (y - arry[2]));
		float areax4 = (0.5) * abs(x * (arry[3] - arry[4]) + arrx[3] * (arry[4] - y) + arrx[4] * (y - arry[3]));
		float areax5 = (0.5) * abs(x * (arry[4] - arry[5]) + arrx[4] * (arry[5] - y) + arrx[5] * (y - arry[4]));
		float areax6 = (0.5) * abs(x * (arry[5] - arry[0]) + arrx[5] * (arry[0] - y) + arrx[0] * (y - arry[5]));
		float areax = areax1 + areax2 + areax3 + areax4 + areax5 + areax6;

		float totalarea = lengthy * lengthx * 1.5;
		 int Area = totalarea;
		if (areax == totalarea)
			return true;
		else
			return false;
	}
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
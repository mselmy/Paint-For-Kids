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
	//ID = newID++;

}
//CHexagon::CHexagon() {};


void CHexagon::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawHexagon(TopLeftCorner, BottomRightCorner, FigGfxInfo, Selected);
}

bool CHexagon::IsPointInside(int x, int y) const	//whether the point is inside the figure or not
{
	return false;
}

void CHexagon::Save(ofstream& OutFile)	//Save the figure parameters to the file
{}
void CHexagon::Load(ifstream& Infile)	//Load the figure parameters to the file
{}
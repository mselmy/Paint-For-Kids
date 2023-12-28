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
	return false;
}

void CEllipse::Save(ofstream& OutFile)	//Save the figure parameters to the file
{}
void CEllipse::Load(ifstream& Infile)	//Load the figure parameters to the file
{}
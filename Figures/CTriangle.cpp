#include "CTriangle.h"
#include <fstream>
#include <iostream>

CTriangle::CTriangle(Point v1, Point v2, Point v3, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo) {
	P1 = v1;
	P2 = v2;
	P3 = v3;
}


void CTriangle::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawTriangle(P1, P2, P3, FigGfxInfo, Selected);

}

bool CTriangle::IsPointInside(int x, int y) const	//whether the point is inside the figure or not
{
	return false;
}

void CTriangle::Save(ofstream& OutFile)	//Save the figure parameters to the file
{}
void CTriangle::Load(ifstream& Infile)	//Load the figure parameters to the file
{}
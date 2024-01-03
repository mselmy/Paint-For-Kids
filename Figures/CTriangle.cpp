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
    // Implementing the point inside function for a triangle using the barycentric coordinate system

    // Calculate the area of the triangle formed by the three corner points
    double totalArea = CalculateTriangleArea(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y);

    // Calculate the areas of the three sub-triangles formed by the point and the corner points
    double area1 = CalculateTriangleArea(x, y, P2.x, P2.y, P3.x, P3.y);
    double area2 = CalculateTriangleArea(P1.x, P1.y, x, y, P3.x, P3.y);
    double area3 = CalculateTriangleArea(P1.x, P1.y, P2.x, P2.y, x, y);

    // Check if the sum of the areas of the sub-triangles is equal to the total area of the triangle
    return (area1 + area2 + area3 == totalArea);
}

// Helper function to calculate the area of a triangle given its three corner points
double CTriangle::CalculateTriangleArea(int x1, int y1, int x2, int y2, int x3, int y3) const
{
    return abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
}

void CTriangle::Save(ofstream& OutFile)	//Save the figure parameters to the file
{
    OutFile << endl << ITM_TRNG << "\t" << ID << "\t" << P1.x << "\t" << P1.y << "\t" << P2.x << "\t" << P2.y << "\t" << P3.x << "\t" << P3.y << "\t";
	OutFile << "(" << (int)FigGfxInfo.DrawClr.ucRed << "," << (int)FigGfxInfo.DrawClr.ucGreen << "," << (int)FigGfxInfo.DrawClr.ucBlue << ")" << "\t";
	if (FigGfxInfo.isFilled)
		OutFile << "(" << (int)FigGfxInfo.FillClr.ucRed << "," << (int)FigGfxInfo.FillClr.ucGreen << "," << (int)FigGfxInfo.FillClr.ucBlue << ")" << endl;
	else
		OutFile << "NO_FILL";
}
void CTriangle::Load(ifstream& Infile)	//Load the figure parameters to the file
{
    // Declare variables for x, y, len, drawColorString, and fill
	string drawColorString, fill;

	// Read values from the file into object data members
	Infile >> ID;
	Infile >> P1.x;
	Infile >> P1.y;
	Infile >> P2.x;
	Infile >> P2.y;
	Infile >> P3.x;
	Infile >> P3.y;
	Infile >> drawColorString >> fill;//read colors from file into strings first to convert to color later

	seTDrawandFillClr(drawColorString, fill); //set the draw and fill colors
}
CTriangle* CTriangle::Clone() const {
	return new CTriangle(*this);
}
void CTriangle::ActionResizeFigure(GUI* pGUI, float size) {
    // Store the original vertices of the triangle
    Point originalV1 = P1;
    Point originalV2 = P2;
    Point originalV3 = P3;

    // Calculate the centroid of the triangle
    float centroidX = (P1.x + P2.x + P3.x) / 3.0;
    float centroidY = (P1.y + P2.y + P3.y) / 3.0;

    // Calculate the new coordinates based on the resizing factor
    P1.x = centroidX + size * (P1.x - centroidX);
    P1.y = centroidY + size * (P1.y - centroidY);

    P2.x = centroidX + size * (P2.x - centroidX);
    P2.y = centroidY + size * (P2.y - centroidY);

    P3.x = centroidX + size * (P3.x - centroidX);
    P3.y = centroidY + size * (P3.y - centroidY);

    // Check if the resized triangle is within the drawing area
    if (P1.y < UI.ToolBarHeight || P2.y < UI.ToolBarHeight || P3.y < UI.ToolBarHeight ||
        P1.y > UI.height - UI.StatusBarHeight || P2.y > UI.height - UI.StatusBarHeight ||
        P3.y > UI.height - UI.StatusBarHeight || P1.x < 1 || P2.x < 1 || P3.x < 1 ||
        P1.x > UI.width || P2.x > UI.width || P3.x > UI.width)
    {
        // Restore the original vertices and print a message
        P1 = originalV1;
        P2 = originalV2;
        P3 = originalV3;
        pGUI->PrintMessage("Triangle size will be more than Drawing Area:)");
    }
}
void CTriangle::SetID(int id)
{
    ID = id;
}
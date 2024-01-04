#ifndef CTriangle_H
#define CTriangle_H

#include "CFigure.h"
#include "..\ApplicationManager.h"
#include <fstream>
#include <iostream>

class CTriangle : public CFigure
{
	Point P1;
	Point P2;
	Point P3;
public:
	virtual CTriangle* Clone() const;
	ApplicationManager* pManager = NULL;	//Actions needs AppMngr to do their job
	int Area;
	CTriangle(Point, Point, Point, GfxInfo FigureGfxInfo);
	
	virtual void DrawMe(GUI* pOut) const;
	virtual double CalculateTriangleArea(int x1, int y1, int x2, int y2, int x3, int y3) const;
	virtual bool IsPointInside(int, int) const;	//whether the point is inside the figure or not
	virtual void SetID(int id);
	virtual void Save(ofstream& OutFile);	//Save the figure parameters to the file
	virtual void Load(ifstream& Infile);	//Load the figure parameters to the file
	void ActionResizeFigure(GUI* pGui, float size);// to resize the triangle
	virtual void move(int& dx, int& dy);	//Move the figure
	virtual int type();	//Return string of the figure type

};

#endif

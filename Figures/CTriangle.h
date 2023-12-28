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
	ApplicationManager* pManager = NULL;	//Actions needs AppMngr to do their job
	int Area;
	CTriangle(Point, Point, Point, GfxInfo FigureGfxInfo);
	
	virtual void DrawMe(GUI* pOut) const;

	virtual bool IsPointInside(int, int) const;	//whether the point is inside the figure or not

	virtual void Save(ofstream& OutFile);	//Save the figure parameters to the file
	virtual void Load(ifstream& Infile);	//Load the figure parameters to the file
};

#endif

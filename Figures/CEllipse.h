#ifndef CELLIPSE_H
#define CELLIPSE_H

#include "CFigure.h"
#include "..\ApplicationManager.h"
#include <fstream>
#include <iostream>

class CEllipse :public CFigure
{
private:
	Point P1, P2;

public:
	virtual CEllipse* Clone() const;

	ApplicationManager* pManager = NULL;	//Actions needs AppMngr to do their job

	CEllipse(Point, Point, GfxInfo FigureGfxInfo);
	
	virtual void DrawMe(GUI* pOut) const;
	void ActionResizeFigure(GUI* pGui, float size);// to resize ellipse
	virtual void SetID(int id);
	virtual bool IsPointInside(int, int) const;	//whether the point is inside the figure or not

	virtual void Save(ofstream& OutFile);	//Save the figure parameters to the file
	virtual void Load(ifstream& Infile);	//Load the figure parameters to the file


};

#endif





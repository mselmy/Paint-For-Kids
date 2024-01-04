#ifndef CCIRCLE_H
#define CCIRCLE_H

#include "CFigure.h"
#include "..\ApplicationManager.h"
#include <fstream>
#include <iostream>

class CCircle :public CFigure
{
private:
	Point center;
	int radius;
public:
	virtual CCircle* Clone() const;

	ApplicationManager* pManager = NULL;	//Actions needs AppMngr to do their job

	CCircle(Point, int, GfxInfo FigureGfxInfo);
	virtual void SetID(int id);
	virtual void DrawMe(GUI* pOut) const;
	void ActionResizeFigure(GUI* pGui, float size);// to resize circle

	virtual bool IsPointInside(int, int) const;	//whether the point is inside the figure or not

	virtual void Save(ofstream& OutFile);	//Save the figure parameters to the file
	virtual void Load(ifstream& Infile);	//Load the figure parameters to the file
	virtual void CCircle::move(int& dx, int& dy);	//Move the figure

};

#endif

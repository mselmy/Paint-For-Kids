#ifndef CSQUARE_H
#define CSQUARE_H

#include "CFigure.h"

class CSquare : public CFigure
{
private:
	Point TopLeftCorner;	
	int length;
public:
	CSquare(Point , int, GfxInfo FigureGfxInfo );
	virtual void DrawMe(GUI* pOut) const;

	virtual bool IsPointInside(int x, int y) const; //whether the point is inside the figure or not

	virtual void Save(ofstream& OutFile);	//Save the figure parameters to the file
};

#endif
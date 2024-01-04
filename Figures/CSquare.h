#ifndef CSQUARE_H
#define CSQUARE_H

#include "CFigure.h"
#include <fstream>
#include <iostream>

class CSquare : public CFigure
{
private:
	Point TopLeftCorner;	
	int length;
public:
	virtual CSquare* Clone() const;

	CSquare(Point , int, GfxInfo FigureGfxInfo );
	virtual void DrawMe(GUI* pOut) const;

	virtual bool IsPointInside(int x, int y) const; //whether the point is inside the figure or not

	virtual void Save(ofstream& OutFile);	//Save the figure parameters to the file
	virtual void SetID(int id);
	virtual void Load(ifstream& Infile);	//Load the figure parameters to the file

	void ActionResizeFigure(GUI* pGui, float size);// to resize square

	virtual void move(int& dx, int& dy); //to move the figure

	virtual int  type();	//Return string of the figure type
};


#endif
#pragma once
#include "../DEFS.h"
#include "Action.h"
#include "../Figures/CFigure.h"

class ActionPickByBoth : public Action
{
private:
	int numOfFigures;	//num of figures
	int rightSelect;	//correct picked figs
	int wrongSelect;	//wrong picked figs
	int randomFiguresNum;	//random number
	int pickedFigureCount;	//picked figure count
	color figColor;		//figure color
	CFigure* Fig;		//pointer to the figure
	int figs_colors[PSHAPECOUNT][PCOLORCOUNT];		//pointer to the figure
	Point p;

public:
	ActionPickByBoth(ApplicationManager* pApp);

	void calcScore(int);

	void Execute();

	string ColorToReadableString(color);

	string ShapeToReadableString(int);

	int getenum(color);

	void GetFilledShape();
};


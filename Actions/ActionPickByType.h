#include "Action.h"
#include "ActionSelectFigure.h"
#include "ActionAddSquare.h"
#define ACTION_PICK_TYPE_FIGURE_H

#include "..\Figures\CFigure.h"
#include "Action.h"

class ActionPickByType : public Action
{
	CFigure* Fig;
	Point p;
	int  numOfFigures, randomFiguresNum, pickedFigureCount, wrongSelect, rightSelect;
	int figs[5];//5 different shapes
	void calcScore(int);
	void GetShape();

public:
	ActionPickByType(ApplicationManager* pApp);
	virtual void Execute();
};

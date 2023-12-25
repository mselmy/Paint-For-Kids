#pragma once
#include "Action.h"

class ActionSelectFigure : public Action
{
	Point P;

public:
	ActionSelectFigure(ApplicationManager* pApp);

	virtual void Execute();
};


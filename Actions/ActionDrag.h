#pragma once
#include "Action.h"
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"

class ActionDrag : public Action
{
	int x1, y1, x2, y2;

	CFigure* SelectedFig;

	buttonstate state;

public:
	ActionDrag(ApplicationManager* pApp);

void Execute();
};


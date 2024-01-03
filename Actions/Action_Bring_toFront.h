#pragma once
#include "Action.h"
#include "..\\ApplicationManager.h"

class Bring_to_Front : public Action
{
	CFigure* Selected;
public:
	Bring_to_Front(ApplicationManager* pApp, CFigure* _selected);

	virtual void Execute();
};

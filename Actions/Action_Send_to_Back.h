#pragma once
#include "Action.h"
#include "..\\ApplicationManager.h"

class Send_to_Back : public Action
{
	CFigure* Selected_Back;
public:
	Send_to_Back(ApplicationManager* pApp, CFigure* _selected_Back);

	virtual void Execute();
}; 
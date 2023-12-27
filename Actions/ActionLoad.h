#pragma once
#include "Action.h"
class ActionLoad : public Action
{
	public:
	ActionLoad(ApplicationManager* pApp);

	//Execute action (code depends on action type)
	virtual void Execute();
 	color stringToColor(string s);
};


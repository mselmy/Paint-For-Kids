#pragma once
#include "Action.h"
class ActionExit : public Action
{
public:
	ActionExit(ApplicationManager* pApp);
	void Execute();
};


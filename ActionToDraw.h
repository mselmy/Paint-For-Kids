#pragma once

#ifndef ACTION_TO_DRAW_H
#define ACTION_TO_DRAW_H
#include "Actions/Action.h"

class ActionToDraw : public Action
{

public:
	ActionToDraw(ApplicationManager* pApp);
	void Execute();
};
#endif
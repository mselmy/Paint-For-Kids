
#pragma once
#ifndef ACTION_TO_PLAY_H
#define ACTION_TO_PLAY_H
#include "Actions/Action.h"

class ActionToPlay : public Action
{

public:
	ActionToPlay(ApplicationManager* pApp);
	void Execute();
};
#endif
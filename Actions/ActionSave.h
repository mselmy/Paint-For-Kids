#pragma once
#include "Action.h"

class ActionSave : public Action
{
public:

	//constructor: set the ApplicationManager pointer inside this action
	ActionSave(ApplicationManager* pApp);

	// template function to print elements in a table
	template<typename T> void saveElement(ofstream& outFile, T t, const int& width, const char& separator);

	//execute action
	void ActionSave::Execute();
};
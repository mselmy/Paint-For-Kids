#include "ActionLoad.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include <fstream>
#include <iostream>
#include <iomanip>

ActionLoad::ActionLoad(ApplicationManager* pApp) : Action(pApp)
{}

void ActionLoad::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	pGUI->PrintMessage("Enter file name to load from: ");
}
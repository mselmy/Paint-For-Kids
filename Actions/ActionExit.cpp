#include "ActionExit.h"
#include "..\ApplicationManager.h"
#include "ActionSave.h"

ActionExit::ActionExit(ApplicationManager* pApp) : Action(pApp)
{}

void ActionExit::Execute()
{
	//Get a Pointer to the Interface
		int reply = pManager->WarningMessage("You didn't save your Drawings, Do you want to save them?\nClick yes to save\nClick no to continoue without saving");
		if (reply == IDCANCEL)
			return;
		else if (reply == IDYES)
		{
			Action* newAct = new ActionSave(pManager);
			pManager->ExecuteAction(newAct);
			delete newAct;
		}
		exit(0);
}
#include "ActionSend_to_Back.h"
#include "ActionSelectFigure.h"

// Constructor of AddEllipse Action Class
Send_to_Back::Send_to_Back(ApplicationManager* pApp, CFigure* _selected) : Action(pApp)
{

	Selected_Back = _selected;
}

void Send_to_Back::Execute()
{
	GUI* pGUI = pManager->GetGUI();

	if (Selected_Back != NULL)
	{
		pGUI->PrintMessage("Send to Back");
		pManager->Send_Back(Selected_Back);
		pManager->set_LastMessage("Send to Back");
	}
	else
	{
		pGUI->PrintMessage("Please, Select a figure");
		pManager->set_LastMessage("Please, Select a figure");
	}
}
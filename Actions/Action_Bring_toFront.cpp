#include "ActionSelectFigure.h"
#include"./Action_Bring_toFront.h"

Bring_to_Front::Bring_to_Front(ApplicationManager* pApp, CFigure* _selected) : Action(pApp)
{

	Selected = _selected;
}

void Bring_to_Front::Execute()
{
	GUI* pGUI = pManager->GetGUI();

	if (Selected != NULL)
	{
		pManager->Bring_Front(Selected);
		pGUI->PrintMessage("Bring to Front");
		pManager->set_LastMessage("Brought to Front");
	}
	else
	{
		pGUI->PrintMessage("Please, Select a figure");
		pManager->set_LastMessage("Please, Select a figure");
	}
}
#include "ActionSelectFigure.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"

ActionSelectFigure::ActionSelectFigure(ApplicationManager* pApp) : Action(pApp)
{}

void ActionSelectFigure::Execute()
{
	Point P;
	CFigure* SelectedFigure = NULL;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	// print message to the user to select a figure
	pGUI->PrintMessage("Select a figure");

	// Get the point clicked
	pGUI->GetPointClicked(P.x, P.y);

	// clear status bar
	pGUI->ClearStatusBar();

	//Get a Pointer to the selected figure
	SelectedFigure = pManager->GetFigure(P.x, P.y);
	if (SelectedFigure == NULL)
	{
		pGUI->PrintMessage("No Figure Selected");
		pManager->UnselectAllFigures();
		return;
	}

	//If there is a selected figure then change its selected state to the opposite
	SelectedFigure->SetSelected(!SelectedFigure->IsSelected());

	pGUI->PrintMessage(pManager->IsAnyFigureSelected() ? "Figure is selected" : "Figure is unselected");
}
#include "ActionDrag.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include <iostream>
using namespace std;
ActionDrag::ActionDrag(ApplicationManager * pApp) :Action(pApp)
{
	x1 = x2 = y1 = y2 = 0;
	SelectedFig = NULL;
}

void ActionDrag::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	// check if there are any figures to drag
	if (pManager->getFigCount() == 0)
	{
		pGUI->PrintMessage("You must draw a figure first");
		return;
	}

	//Print message to the user
	pGUI->PrintMessage("Drag any figure you want");

	//Get start point
	while (pGUI->pWind->GetButtonState(LEFT_BUTTON, x1, y1) == BUTTON_UP) {};

	//get draged figure
	SelectedFig = pManager->GetFigure(x1, y1);

	//get end point
	while (pGUI->pWind->GetButtonState(LEFT_BUTTON, x2, y2) == BUTTON_DOWN) {};

	//calculate the difference between 2 points
	int dx = x2 - x1;
	int dy = y2 - y1;

	// move the figure
	SelectedFig->move(dx, dy);
	
	//clear drawing area
	pGUI->ClearDrawArea();
	pManager->setSavedState(false);
}
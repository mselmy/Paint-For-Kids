#include "ActionChangeColor.h"

ActionChangeColor::ActionChangeColor(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionChangeColor::Execute()
{
	Point P;
	int const itemsCount = 10;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	//Prepare Color menu images directorys
	string ColorItemImages[itemsCount];
	for (int i = 1; i <= itemsCount; i++)
		sprintf(&ColorItemImages[i - 1][0], "images\\Colors\\%02d.jpg", i);

	//Draw Color menu items one image at a time
	for (int i = 0; i < itemsCount; i++)
		pGUI->pWind->DrawImage(&ColorItemImages[i][0], i * UI.MenuItemWidth, UI.ToolBarHeight, UI.MenuItemWidth, UI.ToolBarHeight);

	pGUI->PrintMessage("Please choose the border color");
	//Read point and store in point P
	pGUI->GetPointClicked(P.x, P.y);




	if (P.x < UI.MenuItemWidth * itemsCount && P.y > UI.ToolBarHeight && P.y < UI.ToolBarHeight * 2)
	{
		color clcikedcolor = pGUI->pWind->GetColor(P.x, P.y);
		pGUI->setCrntDrawColor(clcikedcolor);
		pManager->UpdateFigureColor(clcikedcolor);
	}
	else
		pManager->ResetPoint();
	pGUI->ClearDrawArea();
	pGUI->ClearStatusBar();
	pManager->UpdateInterface();
	pManager->UnselectAllFigures();
	pManager->setSavedState(false);
}
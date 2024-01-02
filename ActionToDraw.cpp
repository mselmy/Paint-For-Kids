
#include "ActionToDraw.h"
#include "ApplicationManager.h"
#include "GUI/GUI.h"
ActionToDraw::ActionToDraw(ApplicationManager* pApp) :Action(pApp)
{

}
void ActionToDraw::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->ClearStatusBar();
	pGUI->CreateDrawToolBar();
	pManager->restoreFigList();
	UI.InterfaceMode = MODE_DRAW;
}
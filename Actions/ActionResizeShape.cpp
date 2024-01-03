#include "..\GUI\GUI.h"
#include "ActionResizeShape.h"
#include "ActionAddSquare.h"
#include "..\Figures\CSquare.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include <iostream>
ActionResizeShape::ActionResizeShape(ApplicationManager* pApp) :Action(pApp)
{}
void ActionResizeShape::Execute() {
	GUI* PGUI = pManager->GetGUI();
	PGUI->ClearStatusBar();
	if (pManager->IsAnyFigureSelected()) {
		ActionType pAction;
		do {

			PGUI->CreateReSizeBar();//to create resize bar
			UI.InterfaceMode = MODE_RESIZE;//turn to resize mode
			pAction = PGUI->MapInputToActionType();
			PGUI->PrintMessage("Resizing");
			switch (pAction)
			{
			case BACK:
				//return back to draw mode
				UI.InterfaceMode = MODE_DRAW;
				PGUI->CreateDrawToolBar();
				PGUI->PrintMessage("Back to draw mode!");
				break;
			case QUARTER:
				//case click on QUARTER
				PGUI->ClearDrawArea();
				pManager->Resize_figure(0.25);
				pManager->UpdateInterface();
				break;
			case HALF: //case click on half
				PGUI->ClearDrawArea();
				pManager->Resize_figure(0.5);
				pManager->UpdateInterface();
				break;
			case DOUBLE1:
				//case click on DOUBLE1
				PGUI->ClearDrawArea();
				pManager->Resize_figure(2);
				pManager->UpdateInterface();
				break;
			case QUADRUPLE:
				//case click on QUADRUPLE
				PGUI->ClearDrawArea();
				pManager->Resize_figure(4);
				pManager->UpdateInterface();
				break;
			}

		} while (pAction != BACK);
	}
	else {
		PGUI->PrintMessage("please select the shape first! ");
	}
	pManager->setSavedState(false);
}
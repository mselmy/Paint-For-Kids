#include "ApplicationManager.h"
#include "Actions\ActionAddSquare.h"
#include "Actions\ActionAddCircle.h"
#include "Actions\ActionAddEllipse.h"
#include "Actions\ActionAddHexagon.h"
#include "Actions\ActionAddTriangle.h"
#include "Actions\ActionSelectFigure.h"
#include "Actions/ActionChangeColor.h"
#include "Actions/ActionChangeFill.h"
#include "Actions/ActionChangeBackground.h"
#include "Actions\ActionSave.h"
#include "Actions\ActionLoad.h"
#include "Actions/ActionDelete.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include "Actions/Action_Bring_toFront.h"
#include "Figures/CSquare.h"

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pGUI = new GUI;

	FigCount = 0;

	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++)
		FigList[i] = NULL;
}

void ApplicationManager::Run()
{
	ActionType ActType;
	do
	{
		//1- Read user action
		ActType = pGUI->MapInputToActionType();

		//2- Create the corresponding Action
		Action* pAct = CreateAction(ActType);

		//3- Execute the action
		ExecuteAction(pAct);

		//4- Update the interface
		UpdateInterface();

	} while (ActType != EXIT);

}


//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
//Creates an action
Action* ApplicationManager::CreateAction(ActionType ActType)
{
	Action* newAct = NULL;


	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case DRAW_SQUARE:
		newAct = new ActionAddSquare(this);
		break;

	case DRAW_ELPS:
		newAct = new ActionAddEllipse(this);
		break;

	case DRAW_HEX:
		newAct = new ActionAddHexagon(this);
		break;

	case DRAW_CIRC:
		newAct = new ActionAddCircle(this);
		break;

	case DRAW_TRA:
		newAct = new ActionAddTriangle(this);
		break;
	case CHNG_DRAW_CLR:
		newAct = new ActionChangeColor(this);
		break;
	case CHNG_BG_CLR:
		newAct = new ActionChangeBackground(this);
		break;
	case CHNG_FILL_CLR:
		newAct = new ActionChangeFill(this);
		break;

	case SAVE:
		newAct = new ActionSave(this);
		break;

	case LOAD:
		newAct = new ActionLoad(this);
		break;

    case BRING_TO_FRONT:
		for (int j = 0; j < FigCount; j++) {
			if (FigList[j]->IsSelected()) {
				newAct = new Bring_to_Front(this, FigList[j]);
			}
		}
		break;

	/*case SEND_TO_BACK:
		for (int i = FigCount - 1; i > 0; i--) {

			if (FigList[i]->IsSelected()) {

				newAct = new Send_to_Back(this, FigList[i]);
			}
		}
		break;
      */
	case DEL:
		newAct = new ActionDelete(this);
		break;

	case EXIT:
		ExitMessage();
		break;

		break;
	case DRAWING_AREA:	//a click on the drawing area
		newAct = new ActionSelectFigure(this);
		break;

	case STATUS:	//a click on the status bar ==> no action
		return NULL;
		break;
	}
	return newAct;
}
//////////////////////////////////////////////////////////////////////
//Executes the created Action
void ApplicationManager::ExecuteAction(Action*& pAct)
{
	//Execute the created action
	if (pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
void ApplicationManager::SetPoint(int _x, int _y)
{
	x = _x;
	y = _y;
}
void ApplicationManager::ResetPoint()
{
	x = y = -1;
}

void ApplicationManager::set_LastMessage(string s)
{
	LastMessage = s;
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if (FigCount < MaxFigCount)
		FigList[FigCount++] = pFig;
}
////////////////////////////////////////////////////////////////////////////////////
///////Bring_To_Front \ send to back/////////////

void ApplicationManager::LoadFig()  //for each figure FigList, make it points to NULL 
{
	for (int i = 0; i < FigCount; ++i)
		FigList[i] = NULL;
	FigCount = 0;
}


//////////////////Bring_to_Front///////////////////////////////
void ApplicationManager::Bring_Front(CFigure* swapped)
{
	CFigure* temp = swapped;
	int Swapped_index = 0;
	for (int i = 0; i < FigCount; i++) {
		if (swapped == FigList[i])
			Swapped_index = i;
	}
	
	for (int i = Swapped_index; i < FigCount - 1; i++) {
		FigList[i] = FigList[i + 1];
	}
	FigList[FigCount - 1] = temp;
}

CFigure* ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL

	///Add your code here to search for a figure given a point x,y
	for (int i = FigCount - 1; i >= 0; i--)
	{
		if (FigList[i]->IsPointInside(x, y))
			return FigList[i];
	}

	return NULL;
}
// check if there is any selected figure
bool ApplicationManager::IsAnyFigureSelected()
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
			return true;
	}
	return false;
}

// unselect all figures
void ApplicationManager::UnselectAllFigures()
{
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->SetSelected(false);
	}
}

// get the number of selected figures
int ApplicationManager::getFigCount() const
{
	return FigCount;
}

// save all figures in a file
void ApplicationManager::saveAll(ofstream& OutFile)
{
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->Save(OutFile);
	}
}
void ApplicationManager::UpdateFigureColor(color _color) const //Update border color of selected figure(s)
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
			FigList[i]->ChngDrawClr(_color);
	}
}


void ApplicationManager::reset()
{
	for (int i = 0; i < FigCount; i++)
	{
		delete FigList[i];
		FigList[i] = NULL;
	}
	FigCount = 0;
	pGUI->ClearDrawArea();
}

void ApplicationManager::UpdateFigureFill(color _color, bool isFilled) const //Update fill color of selected figure(s)
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			FigList[i]->ChngFillStts(isFilled);
			FigList[i]->ChngFillClr(_color);
		}
	}
}

void ApplicationManager::Deleteselected() //Delete Selected Figures
{
	for (int i = 0; i < FigCount; i++)
	{
		// delete the selected figures
		if (FigList[i]->IsSelected())
		{
			delete FigList[i];
			FigList[i] = NULL;
		}
	}
	// declare number of deleted figures variable
	int nDeleted = 0;

	// Shifting figures to the top of figure list
	for (int i = 0; i < FigCount; i++)
	{
		if(FigList[i] == NULL)
		{
			nDeleted++;
		}
		else
		{
			FigList[i - nDeleted] = FigList[i];
		}
	}

	// set repeated figures pointer to NULL;
	for (int i = nDeleted; i > 0; i--)
	{
		FigList[FigCount - i] = NULL;
	}

	// set figure count to the new value
	FigCount -= nDeleted;
}

//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	for (int i = 0; i < FigCount; i++)
		FigList[i]->DrawMe(pGUI);		//Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the interface
GUI* ApplicationManager::GetGUI() const
{
	return pGUI;
}
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < FigCount; i++)
		delete FigList[i];
	delete pGUI;

}
//==================================================================================//
//							------EXIT WINDOW----------      						//
//==================================================================================//

int ApplicationManager::ExitMessage()
{
	int msgboxID = MessageBox(
		NULL,
		"Are You Sure You Have Saved Your File?\n Click ok to Leave\nClick cancel to Save",
		"Exit",
		MB_OKCANCEL | MB_ICONWARNING
	);

	switch (msgboxID)
	{
	case IDCANCEL:
	{

		Action* newAct = new ActionSave(this);
		ExecuteAction(newAct);
	}
	break;
	case IDOK:
		exit(0);
		break;
	}

	return msgboxID;
}

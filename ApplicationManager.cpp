#include "ApplicationManager.h"
#include "Actions\ActionAddSquare.h"
#include "Actions\ActionAddCircle.h"
#include "Actions\ActionAddEllipse.h"
#include "Actions\ActionAddHexagon.h"
#include "Actions\ActionAddTriangle.h"
#include "Actions\ActionSelectFigure.h"
#include "Actions\ActionSave.h"
#include "Actions\ActionLoad.h"
#include "Actions/ActionDelete.h"
#include <fstream>
#include <iostream>
#include <iomanip>



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

	case SAVE:
		newAct = new ActionSave(this);
		break;

	case LOAD:
		newAct = new ActionLoad(this);
		break;
	case DEL:
		newAct = new ActionDelete(this);
		break;

	case EXIT:
		///create ExitAction here

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

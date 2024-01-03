#include "ActionLoad.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

#include "../Figures/CSquare.h"
#include "../Figures/CCircle.h"
#include "../Figures/CEllipse.h"
#include "../Figures/CTriangle.h"
#include "../Figures/CHexagon.h"
#include "../Actions/ActionSave.h"

ActionLoad::ActionLoad(ApplicationManager* pApp) : Action(pApp)
{}

void ActionLoad::Execute()
{
		int reply = pManager->WarningMessage("You didn't save your Drawings, Do you want to save them?\nClick yes to save\nClick no to continoue without saving");
		if (reply == IDCANCEL)
			return;
		else if (reply == IDYES)
		{
			Action* newAct = new ActionSave(pManager);
			pManager->ExecuteAction(newAct);
			delete newAct;
		}
	

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	pGUI->PrintMessage("Enter file name to load from: ");

	//get file name from user

	string fileName = pGUI->GetSrting();

	//check if user canceled
	if (fileName.length() == 0)
	{
		pGUI->PrintMessage("Loading is Canceled");
		return;
	}
	 if (fileName.length() < 4||fileName.substr(fileName.length() - 4) != ".txt")
	 {
		fileName += ".txt";
	 }

	//open file
	ifstream inFile;
	inFile.open("Saved_Files/" + fileName, ios::in);

	//check if file is open
	if (!inFile.is_open())
	{
		pGUI->PrintMessage("Error: File not found");
		return;
	}


	//load data
	string  drawColor, fillColor, bgColor;
	inFile >> drawColor >> fillColor >> bgColor;//read header data
	
	//set current colors to GUI
	pGUI->setCrntDrawColor(color::stringToColor(drawColor));
	pGUI->setCrntFillColor(color::stringToColor(fillColor));
	pGUI->setCrntBackgroundColor(color::stringToColor(bgColor));

	int figCount;
	inFile >> figCount;//read fig count

	//initialize paramters
	int figType = -1;
	CFigure* figure = nullptr;
	Point p;
	p.x = 0;
	p.y = 0;

	GfxInfo SqrGfxInfo;
	SqrGfxInfo.isFilled = false;
	SqrGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	SqrGfxInfo.FillClr = pGUI->getCrntFillColor();
	SqrGfxInfo.BorderWdth = pGUI->getCrntPenWidth();

	pManager->reset();//reset all figures

	for (int i = 0; i < figCount; i++)
	{
		inFile >> figType;
		switch (figType)
		{
		case ITM_SQUR:
			figure = new CSquare(p, 1, SqrGfxInfo);
			break;
		case ITM_CIRC:
			figure = new CCircle(p, 1, SqrGfxInfo);
			break;
		case ITM_ELPS:
			figure = new CEllipse(p, p, SqrGfxInfo);
			break;
		case ITM_TRNG:
				figure = new CTriangle(p, p, p, SqrGfxInfo);
			break;
		case ITM_HEXA:
			figure = new CHexagon(p, p, SqrGfxInfo);
			break;
		}
		figure->Load(inFile);
		pManager->AddFigure(figure);
	}

	//close file
	inFile.close();

	pGUI->PrintMessage("Loading is done");

}
#include "ActionLoad.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

ActionLoad::ActionLoad(ApplicationManager* pApp) : Action(pApp)
{}


void ActionLoad::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	pGUI->PrintMessage("Enter file name to load from: ");

	//get file name from user
	pGUI->PrintMessage("Enter file name to save to: ");
	string fileName = pGUI->GetSrting();

	//check if user canceled
	if (fileName.length() == 0)
	{
		pGUI->PrintMessage("Loading is Canceled");
		return;
	}
	else if (fileName.substr(fileName.length() - 4) != ".txt")
		fileName += ".txt";

	//open file
	ifstream infile;
	infile.open("Saved_Files/" + fileName, ios::in);

	//check if file is open
	if (!infile.is_open())
	{
		pGUI->PrintMessage("Error: File not found");
		return;
	}

	//load data
	
	

	//close file
	infile.close();

		pGUI->PrintMessage("Loading is done");



}
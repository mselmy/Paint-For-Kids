#include "ActionSave.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
ActionSave::ActionSave(ApplicationManager* pApp) :Action(pApp)
{}

//set the width of the columns in the file
const char separator = ' ';
const int stringWidth = 24;
const int numWidth = 12;

//template function to print elements in a table
template<typename T> void ActionSave::saveElement(ofstream& outFile, T content, const int& width, const char& separator)
{
	outFile << left << setw(width) << setfill(separator) << content;
}


void ActionSave::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();
	ofstream outFile;
	string fileName;

	bool firstTime = true;

	do {
		if(firstTime)
		{
			pGUI->PrintMessage("Enter file name to save to: ");
			firstTime = false;
		}
		else
		{pGUI->PrintMessage("File name is invalid please try again: ");}

		//get file name from user
		fileName = pGUI->GetSrting();

		//check if file name is not empty and add .txt if not added by user
		if (fileName.length() == 0)
		{
			pGUI->PrintMessage("Saving is Canceled");
			return;
		}
		else if (fileName.find_first_of("\\/:*?\"<>|") != string::npos)
		{}
		else if (fileName.length()<=4 || fileName.substr(fileName.length() - 4) != ".txt")
			fileName += ".txt";
	} while (fileName.find_first_of("\\/:*?\"<>|") != string::npos);
	
	//open file and save all figures

	//open file in write mode and truncate it if it already exists
	outFile.open("Saved_Files/" + fileName, ios::out | ios::trunc);

	//check if file is open
	if (outFile.is_open())
	{
		//get current the drawing colors
		color drawing_color = pGUI->getCrntDrawColor();
		string drawingcolorstring = color::colorToString(drawing_color);

		//get current the filling colors
		color filling_color = pGUI->getCrntFillColor();
		string fillingcolorstring = color::colorToString(filling_color);

		//get current background color
		color background_color = pGUI->getBackgroundColor();
		string backgroundcolorstring = color::colorToString(background_color);

		//save drawing, filling and background colors to file
		saveElement(outFile, drawingcolorstring, stringWidth, separator);
		saveElement(outFile, fillingcolorstring, stringWidth, separator);
		saveElement(outFile, backgroundcolorstring, stringWidth, separator);
		outFile << endl;

		//save number of figures to file
		saveElement(outFile, pManager->getFigCount(), numWidth, separator);

		//send file to application manager to save all figures
		pManager->saveAll(outFile);
		pGUI->PrintMessage("File Saved Successfully");
	}
	else
	{
		pGUI->PrintMessage("Error: Cannot open file to save");
	}
	pManager->setSavedState(true);
}

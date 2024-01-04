#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"

class Action;	//Forward Declaration


//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200 };	//Max no of figures

private:
	int FigCount;		//Actual number of figures
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)

	int FigCountBackup;		//Actual number of figures
	CFigure* FigListBackup[MaxFigCount];	//Clone version of FigList (Array of pointers)
	CFigure* selectedfigure; //The Selected Figure

	bool isSaved; //Checks if the file is saved or not
	int msgboxID; //ID of the message box

	//Pointers to Input and Output classes
	GUI* pGUI;
	//Current coordinates of selected menu action
	int x;
	int y;
	

public:	
	ApplicationManager(); 
	~ApplicationManager();

	void Run();		//to run the application
	
	// -- Action-Related Functions
	Action* CreateAction(ActionType);
	void ExecuteAction(Action*&) ; //Execute an action
	void SetPoint(int, int); //Set x and y to coordinates of last selected menu action
	void ResetPoint(); //Set x and y to -1
	void clearInterface();
	// -- Figures Management Functions
	void AddFigure(CFigure* pFig); //Adds a new figure to the FigList
	CFigure *GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
	void UpdateFigureColor(color _color) const; //Update border color of selected figure(s)
	void UpdateFigureFill(color _color, bool isFilled = true) const; //Update fill color of selected figure(s)
	bool IsAnyFigureSelected(); //Checks if any figure is selected
	void UnselectAllFigures(); //Unselects all figures on the list
	int getFigCount() const; //Returns the number of figures
	void saveAll(ofstream& OutFile); //Saves all figures in a file
	void Send_Back(CFigure*);//Send to back
	void Bring_Front(CFigure*);///Bring to front

	void LoadFig();  //clean the FigList

	void Set_LastMessage(string);//saving last messages
	string LastMessage;//defin last message
	void Deleteselected(); // delete selected figure
	int WarningMessage(LPCSTR); // warning message
		
	// -- Interface Management Functions	
	GUI *GetGUI() const; //Return pointer to the interface
	void UpdateInterface() const;	//Redraws all the drawing window
	void reset(); //Resets the application and deletes all figures/

	void backupFigList();

	void restoreFigList();

	void Resize_figure(float size) const; //resize figure
	CFigure* DrawnFigs(int i) const;//draw figs

	bool getSavedState(); //Returns the saved state of the file
	void setSavedState(bool); //Sets the saved state of the file

};

#endif
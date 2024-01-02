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

	//Pointers to Input and Output classes
	GUI* pGUI;
	

public:	
	ApplicationManager(); 
	~ApplicationManager();

	void Run();		//to run the application
	
	// -- Action-Related Functions
	Action* CreateAction(ActionType);
	void ExecuteAction(Action*&) ; //Execute an action
	
	// -- Figures Management Functions
	void AddFigure(CFigure* pFig); //Adds a new figure to the FigList
	CFigure *GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
	bool IsAnyFigureSelected(); //Checks if any figure is selected
	void UnselectAllFigures(); //Unselects all figures on the list
	int getFigCount() const; //Returns the number of figures
	void saveAll(ofstream& OutFile); //Saves all figures in a file
	void Deleteselected();
		
	// -- Interface Management Functions	
	GUI *GetGUI() const; //Return pointer to the interface
	void UpdateInterface() const;	//Redraws all the drawing window
	void reset(); //Resets the application and deletes all figures/

	void backupFigList();

	void restoreFigList();

};

#endif
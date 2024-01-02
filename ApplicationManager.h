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
	
	// -- Figures Management Functions
	void AddFigure(CFigure* pFig); //Adds a new figure to the FigList
	CFigure *GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
	void UpdateFigureColor(color _color) const; //Update border color of selected figure(s)
	void UpdateFigureFill(color _color, bool isFilled = true) const; //Update fill color of selected figure(s)
	bool IsAnyFigureSelected(); //Checks if any figure is selected
	void UnselectAllFigures(); //Unselects all figures on the list
	int getFigCount() const; //Returns the number of figures
	void saveAll(ofstream& OutFile); //Saves all figures in a file
	void Bring_Front(CFigure*);///Bring to front
	void set_LastMessage(string); // saving the last message


	void LoadFig();  //clean the FigList

	void Set_LastMessage(string);//saving last messages
	string LastMessage;//defin last message
	int ExitMessage(); //// Action Exit
	void Deleteselected(); // delete selected figure
		
	// -- Interface Management Functions	
	GUI *GetGUI() const; //Return pointer to the interface
	void UpdateInterface() const;	//Redraws all the drawing window
	void reset(); //Resets the application and deletes all figures/


};

#endif
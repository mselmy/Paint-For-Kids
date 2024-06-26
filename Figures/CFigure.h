#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\defs.h"
#include "..\GUI\GUI.h"
#include <fstream>
#include <iostream>
//Base class for all figures
class CFigure
{
protected:
	int ID;		//Each figure has an ID
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
	static int counter;	//counter for the ID of the figure
	bool figHidden;   //hidden figure
	/// Add more parameters if needed.

public:
	CFigure();
	CFigure(GfxInfo FigureGfxInfo);
	void SetSelected(bool );	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected
	virtual CFigure* Clone() const = 0;
	virtual void DrawMe(GUI*) const  = 0 ;		//Draw the figure

	virtual bool IsPointInside(int , int ) const = 0;	//whether the point is inside the figure or not
	
	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color
	virtual void ActionResizeFigure(GUI* pGUI, float size) = 0;//resize the figure.
	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	
	void Hide(); //to hide a figure
	void Show(); //show a figure
	bool CFigure::HiddenStatus();//know hidden status
	

	//virtual void Rotate() = 0;	//Rotate the figure
	//virtual void Resize() = 0;	//Resize the figure
	//virtual void Move() = 0;		//Move the figure

	virtual void Save(ofstream &OutFile) = 0;	//Save the figure parameters to the file
	virtual void Load(ifstream &Infile) = 0;	//Load the figure parameters to the file

	//virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar

	void ChngFillStts(bool isFilled); //changes the figure's filling status
	void seTDrawandFillClr(string, string); // set the draw and fill color of the figure
	GfxInfo CFigure::GetGfxInfo();
	virtual void move(int& dx, int& dy) = 0; //to move the figure
	virtual int type() = 0;	//Return string of the figure type

};


#endif
#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

//This file contais some global constants and definitions to be used in the project.
enum ActionType //The actions supported (you can add more if needed)
{
	DRAW_SQUARE,	//Draw a Square
	DRAW_ELPS,		//Draw an Ellipse
	DRAW_HEX,		//Draw a Hexagon
	DRAW_CIRC,      //DRAW A CIRCLE
	DRAW_TRA,       //DRAW A TRIANGL
	CHNG_DRAW_CLR,	//Change the drawing color
	CHNG_FILL_CLR,	//Change the filling color
	CHNG_BG_CLR,	//Change background color
	DEL,			//Delete a figure(s)
	MOVE,			//Move a figure(s)
	RESIZE,			//Resize a figure(s)
	ROTATE,			//Rotate a figure(s)
	SEND_TO_BACK,		//Send a figure to the back of all figures
	BRING_TO_FRONT,		//Bring a figure to the front of all figures
	SAVE,			//Save the whole graph to a file
	LOAD,			//Load a graph from a file
	DRAG,			//Drag and drop
	EXIT,			//Exit the application
	TO_DRAW,		//Switch interface to Draw mode
	TO_PLAY,		//Switch interface to Play mode
	DRAWING_AREA,	//A click on the drawing area
	STATUS,			//A click on the status bar
	EMPTY,			//A click on empty place in the toolbar
	ACTION_TO_PLAY,		//Switch interface to Play mode
	ACTION_TO_DRAW,		//Switch interface to Draw mode
	ACTION_PLAY_TYPE,	//play figures by type
	ACTION_PLAY_FILL,	//play figures by fill color
	ACTION_PLAY_TYPEFILL,//play figures by type and fill color
//	PLAY_COLOR,
	///TODO: Add more action types (if needed)
	//global constants for resize
	
	PICK,          //pick by type in play mode
	BACK,           //back to main page
	QUARTER,         //QUARTER of shape size
	HALF,           //half of shape size  
	DOUBLE1,         //DOUBLE of shape size
	QUADRUPLE,//QUADRUPLE of shape size
};

struct Point	//To be used for figures points
{ int x,y; };

struct GfxInfo	//Graphical info of each figure (you may add more members)
{
	color DrawClr;	//Draw color of the figure
	color FillClr;	//Fill color of the figure
	bool isFilled;	//Figure Filled or not
	int BorderWdth;	//Width of figure borders

};

#endif
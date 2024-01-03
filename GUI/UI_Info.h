#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

enum GUI_MODE	//Graphical user interface mode
{
	MODE_DRAW,	//Drawing mode (startup mode)
	MODE_PLAY,	//Playing mode
	MODE_RESIZE  //resize mode
};

enum DrawMenuItem //The items of the Draw menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_SQUR,		//Square item in menu
	ITM_ELPS,		//Ellipse item in menu
	//TODO: Add more items names here
	//ITM_SELECT,		//select item in menu
	ITM_HEXA,      //Hexagon item in menu
	ITM_CIRC,      //Circle item in menu
	ITM_TRNG,      //Triangle item in menu
	ITM_PLAY,        //play item in menu
	ITM_CLR,
	ITM_BG,			//Change background color
	ITM_FILL,		//Change shape filling
	ITM_RESIZE,//Change shape color
	ITM_SEND_TO_BACK,// Send_to_back
	ITM_BRING_TO_FRONT,// brnig to front
	ITM_SAVE,		//save item in menu
	ITM_LOAD,		//load item in menu	
	ITM_DEL,		//Delete item
	ITM_EXIT,		//Exit item
	
	DRAW_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum
	
};

enum PlayMenuItem //The items of the Play menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
  
	//TODO: Add more items names here
	PLAY_TYPE,
	PLAY_FILL,
	PLAY_TYPEFILL,
	//PLAY_RESET,
	PLAY_BACK,
	PLAY_ITM_COUNT	//no. of menu items ==> This should be the last line in this enum

};


enum ResizeMenueItems //items of resize menu 
{
	ITM_BACK,
	ITM_QUARTER,
	ITM_HALF,
	ITM_DOUBLE,
	ITM_QUADRAPLE,
	RESIZE_ITM_COUNT,
};



__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	GUI_MODE InterfaceMode;
	
	int	width, height,	//Window width and height
		wx , wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuItemWidth;		//Width of each item in toolbar menu
	
	bool IsFilled;
	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	int PenWidth;			//width of the pen that draws shapes

	/// Add more members if needed
	
}UI;	//create a global object UI

#endif
#include "GUI.h"
#include "UI_Info.h"
#include <iostream>
//constructor make necessary initializations
GUI::GUI()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;

	UI.width = 1380;
	UI.height = 700;
	UI.wx = 5;
	UI.wy = 5;


	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 80;

	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = GREEN;	//Filling color
	UI.MsgColor = RED;		//Messages color
	UI.BkGrndColor = WHITE;	//Background color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = TURQUOISE;
	UI.PenWidth = 3;	//width of the figures frames


	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");

	CreateDrawToolBar();
	CreateStatusBar();

}


//======================================================================================//
//								Input Functions										    //
//======================================================================================//


void GUI::GetPointClicked(int& x, int& y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string GUI::GetSrting() const
{
	string Label;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if (Key == 8)	//BackSpace is pressed
		{
			if (Label.size() > 0)
			{
				Label.resize(Label.size() - 1);
			}
			else
			{

				Label = "";
			}
		}
		else
		{
			Label += Key;
		}
		PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType GUI::MapInputToActionType() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if (UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_SQUR: return DRAW_SQUARE;
			case ITM_ELPS: return DRAW_ELPS;
			case ITM_HEXA: return DRAW_HEX;
			case ITM_CIRC: return DRAW_CIRC;
			case ITM_TRNG: return DRAW_TRA;
			case ITM_RESIZE: return RESIZE;
			case ITM_PLAY:return TO_PLAY;
			case ITM_CLR: return CHNG_DRAW_CLR;
			case ITM_BG: return CHNG_BG_CLR;
			case ITM_DRAG: return DRAG;
			case ITM_FILL: return CHNG_FILL_CLR;
			case ITM_SAVE: return SAVE;
			case ITM_LOAD: return LOAD;
			case ITM_EXIT: return EXIT;
			case ITM_SEND_TO_BACK: return SEND_TO_BACK;
			case ITM_BRING_TO_FRONT:return BRING_TO_FRONT;
			case ITM_DEL: return DEL;          
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else if (UI.InterfaceMode == MODE_PLAY)	//GUI is in PLAY mode
	{
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			switch (ClickedItemOrder)
			{
			case PLAY_TYPE: return ACTION_PLAY_TYPE;
			case PLAY_FILL: return ACTION_PLAY_FILL;
			case PLAY_TYPEFILL: return ACTION_PLAY_TYPEFILL;
			//case PLAY_RESET: return ACTION_PLAY_RESET;*/
			case PLAY_BACK: return ACTION_TO_DRAW;
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}
		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}
		//[3] User clicks on the status bar
		return STATUS;
		//return TO_PLAY;	//just for now. This should be updated
	}
	else if (UI.InterfaceMode == MODE_RESIZE) // get in resize mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//If division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
			switch (ClickedItemOrder)
			{
			case ITM_BACK:
				return BACK;
			case ITM_QUARTER:
				return QUARTER;
			case ITM_HALF:
				return HALF;
			case ITM_DOUBLE:
				return DOUBLE1;
			case ITM_QUADRAPLE:
				return QUADRUPLE;
			default: return EMPTY;
			}
		}
	}
}
//======================================================================================//
//								Output Functions										//
//======================================================================================//

window* GUI::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white Square
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_SQUR] = "images\\MenuItems\\Menu_Sqr.jpg";
	MenuItemImages[ITM_ELPS] = "images\\MenuItems\\Menu_Elps.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";
	//TODO: Prepare images for each menu item and add it to the list
	MenuItemImages[ITM_HEXA] = "images\\MenuItems\\Menu_Hex.jpg";
	MenuItemImages[ITM_CIRC] = "images\\MenuItems\\Menu_Circle.jpg";//
	MenuItemImages[ITM_TRNG] = "images\\MenuItems\\Menu_Tri.jpg";
	MenuItemImages[ITM_BG] = "images\\MenuItems\\MenuBackground.jpg";
	MenuItemImages[ITM_CLR] = "images\\MenuItems\\MenuColor.jpg";
	MenuItemImages[ITM_FILL] = "images\\MenuItems\\MenuFill.jpg";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\Menu_Save.jpg";
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\Menu_Load.jpg";
	MenuItemImages[ITM_SEND_TO_BACK] = "images\\MenuItems\\Send_to_back.jpg";
	MenuItemImages[ITM_BRING_TO_FRONT] = "images\\MenuItems\\Bring_To_Front.jpg";
	MenuItemImages[ITM_DEL] = "images\\MenuItems\\Menu_Del.jpg";
	MenuItemImages[ITM_PLAY] = "images\\MenuItems\\PlayMode.jpg";
	MenuItemImages[ITM_RESIZE] = "images\\MenuItems\\Menu_resize.jpg";
	MenuItemImages[ITM_DRAG] = "images\\MenuItems\\Menu_Drag.jpg";

	//Draw menu item one image at a time
	for (int i = 0; i < DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreatePlayToolBar() const
{///TODO: write code to create Play mode menu
		
	ClearToolBarArea();
		UI.InterfaceMode = MODE_PLAY;
		string PlayMenuImages[PLAY_ITM_COUNT];
		PlayMenuImages[PLAY_TYPE] = "images\\MenuItems\\Menue_Shapes.jpg";
		PlayMenuImages[PLAY_FILL] = "images\\MenuItems\\Menue_Colors.jpg";
		PlayMenuImages[PLAY_TYPEFILL] = "images\\MenuItems\\Menu_Type_Color.jpg";
		//PlayMenuImages[PLAY_RESET] = "images\\MenuItems\\newgame.jpg";
		PlayMenuImages[PLAY_BACK] = "images\\MenuItems\\Menu_Back.jpg";

		//TODO: Prepare images for each menu item and add it to the list
		//Draw menu item one image at a time
		for (int i = 0; i < PLAY_ITM_COUNT; i++)
			pWind->DrawImage(PlayMenuImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

		//Draw a line under the toolbar
		pWind->SetPen(RED, 3);
		pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
  }
//Resize 
void GUI::CreateReSizeBar()const {
	CreateToolBar();
	//determine mode type
	UI.InterfaceMode = MODE_RESIZE;
	//create resize menue images
	//define array (size is num of items).
	string MenueResizeItemImages[RESIZE_ITM_COUNT];
	MenueResizeItemImages[ITM_BACK] = "images\\MenuItems\\Menu_Back.jpg";
	MenueResizeItemImages[ITM_QUARTER] = "images\\MenuItems\\Menue_Quarter.jpg";
	MenueResizeItemImages[ITM_HALF] = "images\\MenuItems\\Menue_Half.jpg";
	MenueResizeItemImages[ITM_DOUBLE] = "images\\MenuItems\\Menue_Double.jpg";
	MenueResizeItemImages[ITM_QUADRAPLE] = "images\\MenuItems\\Menue_Quad.jpg";
	
	//Draw resize menu item on GUI Screen. 
	for (int i = 0; i < RESIZE_ITM_COUNT; i++) {

		pWind->DrawImage(MenueResizeItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	}
	//Draw a line under the toolbar
	pWind->SetPen(GREEN, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

void GUI::CreateToolBar() const
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearToolBarArea() const
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}

void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight / 1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntDrawColor() const	//get current drwawing color
{
	return UI.DrawColor;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::setCrntDrawColor(color _color) const	//set current drwawing color
{
	UI.DrawColor = _color;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::setCrntFillColor(color _color, bool isFilled) const	//set current fill color
{
	UI.IsFilled = isFilled;
	UI.FillColor = _color;
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntFillColor() const	//get current filling color
{
	return UI.FillColor;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::setCrntBackgroundColor(color _color) const	//set current background color
{
	UI.BkGrndColor = _color;
}
//////////////////////////////////////////////////////////////////////////////////////////


color GUI::getBackgroundColor() const //get current background color
{
	return UI.BkGrndColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

int GUI::getCrntPenWidth() const		//get current pen width
{
	return UI.PenWidth;
}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void GUI::DrawSquare(Point P1, int length, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;
	


	pWind->DrawRectangle(P1.x, P1.y, P1.x + length, P1.y + length, style);
	

}
/////////////////////////////////////////////////////////////////////////////
void GUI::DrawEllipse(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;

	

	pWind->DrawEllipse(P1.x, P1.y, P2.x, P2.y, style);
}
////////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawHexagon(Point P1, Point P2, GfxInfo HexGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = HexGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, HexGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (HexGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(HexGfxInfo.FillClr);
	}
	else
		style = FRAME;

	int lengthx = abs(P1.x - P2.x);
	int lengthy = abs(P1.y - P2.y);

	int arrx[6] = { P1.x,P1.x + lengthx, P1.x + 1.5 * lengthx,P1.x + lengthx,P1.x,P1.x - 0.5 * lengthx };
	int arry[6] = { P1.y,P1.y,P1.y + 0.5 * lengthy,P1.y + lengthy,P1.y + lengthy,P1.y + 0.5 * lengthy };


	Point topleft, bottomright;
	topleft.x = P1.x - 0.5 * lengthx;
	topleft.y = P1.y;
	bottomright.x= P1.x  +1.5 * lengthx;
	bottomright.y = P1.y + 1.732 * lengthx;

	

	pWind->DrawPolygon(arrx, arry, 6, style);

}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawCircle(Point P1, int _radius, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;

	



	pWind->DrawCircle(P1.x, P1.y, _radius, style);


}
void GUI::DrawTriangle(Point P1, Point P2, Point P3, GfxInfo ElpsGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = ElpsGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, ElpsGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (ElpsGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(ElpsGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);

}
//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()

{
	delete pWind;
}


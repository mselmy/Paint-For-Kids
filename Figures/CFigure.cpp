#include "CFigure.h"

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	ID = ++counter; //assigning the ID of the figure
}

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }

void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}

color CFigure::stringToColor(string s)
{
	int r, g, b;
	int i = 1;
	string temp = "";
	while (s[i] != ',')
	{
		temp += s[i];
		i++;
	}
	r = stoi(temp);
	i++;
	temp = "";
	while (s[i] != ',')
	{
		temp += s[i];
		i++;
	}
	g = stoi(temp);
	i++;
	temp = "";
	while (s[i] != ')')
	{
		temp += s[i];
		i++;
	}
	b = stoi(temp);
	color c;
	c.ucRed = r;
	c.ucGreen = g;
	c.ucBlue = b;
	return c;
}
void CFigure::ChngFillStts(bool isFilled)
{
	FigGfxInfo.isFilled = isFilled;
}


#include "CFigure.h"
CFigure::CFigure()
{
	figHidden = false;
}
CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	figHidden = false;
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

void CFigure::ChngFillStts(bool isFilled)
{
	FigGfxInfo.isFilled = isFilled;
}

void CFigure::seTDrawandFillClr(string drawColorString, string fill) // set the draw and fill color of the figure
{
	// Convert the drawColorString to a color and assign it to FigGfxInfo.DrawClr
	ChngDrawClr(color::stringToColor(drawColorString));

	// Check if the fill is "NO_FILL"
	if (fill == "NO_FILL") {
		FigGfxInfo.isFilled = false;
		FigGfxInfo.FillClr = NULL;
	}
	else
	{
		// Convert the fill to a color and assign it to FigGfxInfo.FillClr
		ChngFillClr(color::stringToColor(fill));
	}
}
void CFigure::Hide()
{
	figHidden = true;
}
//Shows Figures
void CFigure::Show()
{
	figHidden = false;
}


bool CFigure::HiddenStatus() {
	return figHidden;
}
GfxInfo CFigure::GetGfxInfo()
{
	return FigGfxInfo;
}

void CFigure::move(int& dx, int& dy)
{}

#include "ActionPickByBoth.h"
#include "ActionAddSquare.h"
#include "..\Figures\CSquare.h"
#include "..\Figures\CHexagon.h"
#include "..\Figures\CTriangle.h"
#include "..\GUI\GUI.h"
#include "..\ApplicationManager.h"
#include "..\Figures\CCircle.h"
#include "..\Figures\CEllipse.h"

ActionPickByBoth::ActionPickByBoth(ApplicationManager* pApp) :Action(pApp)
{
	numOfFigures = 0;//num of figures
	rightSelect = 0;//correct picked figs
	wrongSelect = 0;//wrong picked figs

	for (int i = 0; i < PSHAPECOUNT; i++)
	{
		for(int j = 0; j < PCOLORCOUNT; j++)
		{
			figs_colors[i][j] = 0;		// set all figures colors with 0
		}
	}

}

void ActionPickByBoth::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	//set numper of figures
	numOfFigures = pManager->getFigCount();

	if (numOfFigures > 1)
	{

		// get filled shapes
		GetFilledShape();

		CFigure* clickedFig;
		// get random number in the range 0 to figCount
		randomFiguresNum = rand() % numOfFigures;

		Fig = pManager->DrawnFigs(randomFiguresNum);
		figColor = Fig->GetGfxInfo().FillClr;

		// choose to play without colors
		if (!Fig->GetGfxInfo().isFilled)
		{
			figColor = SNOW;
		}
		
		switch (Fig->type())
		{
		case ITM_SQUR:
			pickedFigureCount = figs_colors[PSQUARE][getenum(figColor)];
			break;
		case ITM_CIRC:
			pickedFigureCount = figs_colors[PCIRCLE][getenum(figColor)];
			break;
		case ITM_ELPS:
			break;
		case ITM_HEXA:
			pickedFigureCount = figs_colors[PHEXAGON][getenum(figColor)];
			break;
		case ITM_TRNG:
			pickedFigureCount = figs_colors[PTRIANGLE][getenum(figColor)];
			break;
		};
		pGUI->PrintMessage("Pick up all the " + ShapeToReadableString(Fig->type()) + " with color " + ColorToReadableString(figColor) + " !");
		
		while (pickedFigureCount > 0)
		{
			pGUI->GetPointClicked(p.x, p.y);
			if (p.y > UI.ToolBarHeight)
			{
				clickedFig = pManager->GetFigure(p.x, p.y);

				if (clickedFig != NULL)
				{

					if ((clickedFig->type() == Fig->type()) && (getenum(clickedFig->GetGfxInfo().FillClr) == getenum(figColor)))
					{
						calcScore(1);
						clickedFig->Hide();
						pickedFigureCount--;
						pGUI->ClearDrawArea();
						pManager->UpdateInterface();
					}
					else
					{
						calcScore(2);
						clickedFig->Hide();

						pGUI->ClearDrawArea();
						pManager->UpdateInterface();
					}

				}
			}
			else
			{
				pickedFigureCount = -1;
				pGUI->ClearStatusBar();
			}

		}
		pGUI->ClearDrawArea();

		// end the clicked
		if (pickedFigureCount == 0)
		{
			calcScore(3);
		}
		for (int i = 0; i < pManager->getFigCount(); i++)
		{
			pManager->DrawnFigs(i)->Show();
		}
	}
	else
	{
		pGUI->PrintMessage("You must have at least two types of figures to play ! ");
	}

	for (int i = 0; i < pManager->getFigCount(); i++)
	{
		pManager->DrawnFigs(i)->Show();
	}
	pManager->UpdateInterface();
}

void ActionPickByBoth::calcScore(int Score)
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	//print message for the player 
	string Message;

	if (Score == 1)
	{
		rightSelect++;
		Message = "Amazing!, Your score is: " + to_string(rightSelect) + " correct & " + to_string(wrongSelect) + "incorrect";

	}
	else if (Score == 2)
	{
		wrongSelect++;
		Message = "Wrong!, Your score is: " + to_string(rightSelect) + " correct & " + to_string(wrongSelect) + "incorrect.";
	}
	else
	{
		if (rightSelect > wrongSelect)
		{
			Message = "Congratulations You win!, Your score is : " + to_string(rightSelect) + " correct & : " + to_string(wrongSelect) + " incorrect.";
		}
		else if (rightSelect == wrongSelect && rightSelect != 0)
		{
			Message = "Try again it's Draw!, Your score is : " + to_string(rightSelect) + " correct & : " + to_string(wrongSelect) + " incorrect.";
		}
		else
		{
			Message = "Hard Luck,Try again!, Your score is : " + to_string(rightSelect) + " correct & : " + to_string(wrongSelect) + " incorrect.";
		}

	}
	pGUI->PrintMessage(Message);
}

void ActionPickByBoth::GetFilledShape()
{
	for (int i = 0; i < pManager->getFigCount(); i++) {
		Fig = pManager->DrawnFigs(i);

		// counting colors exists
		figs_colors[Fig->type()][getenum(Fig->GetGfxInfo().FillClr)]++;
	}
}

string ActionPickByBoth::ColorToReadableString(color c)
{
	if (c == BLACK)
		return "BLACK";
	else if (c == WHITE)
		return "WHITE";
	else if (c == RED)
		return "RED";
	else if (c == GREEN)
		return "GREEN";
	else if (c == BLUE)
		return "BLUE";
	else if (c == ORANGE)
		return "ORANGE";
	else if (c == YELLOW)
		return "YELLOW";
	else if (c == BROWN)
		return "BROWN";
	else if (c == PINK)
		return "PINK";
	else if (c == PURPLE)
		return "PURPLE";
	else
		return "NO_FILL";
}

string ActionPickByBoth::ShapeToReadableString(int s)
{
	if (s == PSQUARE)	
		return "SQUARE";
	else if (s == PCIRCLE)
		return "CIRCLE";
	else if (s == PELLIPSE)
		return "ELLIPSE";
	else if (s == PHEXAGON)
		return "HEXAGON";
	else if (s == PTRIANGLE)
		return "TRIANGLE";
}

int ActionPickByBoth::getenum(color c)
{
	if (c == BLACK)
		return PBLACK;
	else if (c == WHITE)
		return PWHITE;
	else if (c == RED)
		return PRED;
	else if (c == GREEN)
		return PGREEN;
	else if (c == BLUE)
		return PBLUE;
	else if (c == ORANGE)
		return PORANGE;
	else if (c == YELLOW)
		return PYELLOW;
	else if (c == BROWN)
		return PBROWN;
	else if (c == PINK)
		return PPINK;
	else if (c == PURPLE)
		return PPURPLE;
	else
		return PNOFILL;
}

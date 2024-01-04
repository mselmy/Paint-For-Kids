#include "ActionPickByType.h"
#include "ActionAddSquare.h"
#include "..\Figures\CSquare.h"
#include "..\Figures\CHexagon.h"
#include "..\Figures\CTriangle.h"
#include "..\GUI\GUI.h"
#include "..\ApplicationManager.h"
#include "..\Figures\CCircle.h"
#include "..\Figures\CEllipse.h"

ActionPickByType::ActionPickByType(ApplicationManager* pApp) :Action(pApp)
{
	numOfFigures = 0;//num of figures
	rightSelect = 0;//correct picked figs
	wrongSelect = 0;//wrong picked figs
	for (int i = 0; i < 5; i++)
	{
		figs[i] = 0;		// set all figures with 0
	}

}
//score calaculation
void ActionPickByType::calcScore(int Score)
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
void ActionPickByType::GetShape()
{
	for (int i = 0; i < pManager->getFigCount(); i++)
	{
		Fig = pManager->DrawnFigs(i);
		if (dynamic_cast<CSquare*>(Fig))
			figs[0]++;
		//figs-> array of figures in runtime for count figures, assign every index to a figure to check then ++ 
		else if (dynamic_cast<CCircle*>(Fig))
			figs[1]++;
		else if (dynamic_cast<CEllipse*>(Fig))
			figs[2]++;
		else if (dynamic_cast<CHexagon*>(Fig))
			figs[3]++;
		else if (dynamic_cast<CTriangle*>(Fig))
			figs[4]++;

	}
	for (int i = 0; i < 5; i++)  //loop to know count of all figures 
	{
		if (figs[i] != 0)
			numOfFigures++;
	}
}

//Execution of action
void ActionPickByType::Execute()
{
	//for switching to draw mode
	GUI* pGUI = pManager->GetGUI();
	pGUI->ClearStatusBar();
	if (pManager->IsAnyFigureSelected()) {//to make sure that there are figures selected
		ActionType pAction;
		//do {
			//pGUI->CreatePlayToolBar();
			//UI.InterfaceMode = MODE_PLAY;
			//pAction = pGUI->MapInputToActionType();
			//switch (pAction)
			//{
			//case PICK:

		GetShape();
		if (numOfFigures > 1)
		{
			CFigure* clickedFig;

			// get random number in the range 0 to figCount
			randomFiguresNum = rand() % pManager->getFigCount();
			Fig = pManager->DrawnFigs(randomFiguresNum);
			if (dynamic_cast<CSquare*>(Fig))
			{

				pickedFigureCount = figs[0];
				pGUI->PrintMessage("Pick up all the Squares !");

			}
			else if (dynamic_cast<CCircle*>(Fig))
			{
				pickedFigureCount = figs[1];
				pGUI->PrintMessage("Pick up all the Circles !");
			}

			else if (dynamic_cast<CEllipse*>(Fig))
			{
				pickedFigureCount = figs[2];
				pGUI->PrintMessage("Pick up all the Ellipse !");
			}
			else if (dynamic_cast<CHexagon*>(Fig))
			{
				pickedFigureCount = figs[3];
				pGUI->PrintMessage("Pick up all the Hexagon !");
			}
			else if (dynamic_cast<CTriangle*>(Fig))
			{
				pickedFigureCount = figs[4];
				pGUI->PrintMessage("Pick up all the Triangle !");
			}
			while (pickedFigureCount > 0)
			{
				pGUI->GetPointClicked(p.x, p.y);
				if (p.y > UI.ToolBarHeight || p.x > (UI.MenuItemWidth * PLAY_ITM_COUNT))
				{
					clickedFig = pManager->GetFigure(p.x, p.y);

					if (clickedFig != NULL)
					{

						if ((dynamic_cast<CSquare*>(clickedFig)) && (dynamic_cast<CSquare*>(Fig)))
						{
							calcScore(1);
							clickedFig->Hide();

							pickedFigureCount--;
							pGUI->ClearDrawArea();
							pManager->UpdateInterface();
						}
						else if ((dynamic_cast<CCircle*>(clickedFig)) && (dynamic_cast<CCircle*>(Fig)))
						{
							calcScore(1);
							clickedFig->Hide();
							pickedFigureCount--;
							pGUI->ClearDrawArea();
							pManager->UpdateInterface();

						}
						else if ((dynamic_cast<CEllipse*>(clickedFig)) && (dynamic_cast<CEllipse*>(Fig)))
						{
							calcScore(1);
							clickedFig->Hide();

							pickedFigureCount--;
							pGUI->ClearDrawArea();
							pManager->UpdateInterface();

						}
						else if ((dynamic_cast<CHexagon*>(clickedFig)) && (dynamic_cast<CHexagon*>(Fig)))
						{
							calcScore(1);
							clickedFig->Hide();

							pickedFigureCount--;
							pGUI->ClearDrawArea();
							pManager->UpdateInterface();

						}
						else if ((dynamic_cast<CTriangle*>(clickedFig)) && (dynamic_cast<CTriangle*>(Fig)))
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
		/*else
		{
			pGUI->PrintMessage("You must have at least two types of figures to play ! ");
		}

		for (int i = 0; i < pManager->getFigCount(); i++)
		{
			pManager->DrawnFigs(i)->Show();
		}
		pManager->UpdateInterface();
		break;
	case BACK:
		//return back to draw mode
		UI.InterfaceMode = MODE_DRAW;
		pGUI->CreateDrawToolBar();
		pGUI->PrintMessage("Back to draw mode!");
		break;
	}
} while (pAction != BACK);
}
*/

		else {
			pGUI->PrintMessage("select at least 2 shapes");
		}
	}
}
#include "ActionSelect.h"
/*#include "..\ApplicationManager.h"*/
#include "ApplicationManager.h"

/*#include "..\GUI\GUI.h"*/
#include "GUI/GUI.h"

ActionSelect::ActionSelect(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
//Omar
void ActionSelect::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	int x, y, index=-1;
	pGUI->GetPointClicked(x, y);//double click
	CFigure *figSelected = pManager->GetFigure(x, y, index);
	if (figSelected != NULL)
	{
		if (!(figSelected->IsSelected()))
		{
			
			figSelected->SetSelected(true);
			figSelected->setOldDrawClr(figSelected->getDrawColor());//save the old draw color to get it again after unselecting
			if (figSelected->IsShapeFilled()) {
				figSelected->setOldFillClr(figSelected->getFillColor()); //save the old fill color only if the figure is filled
			}
			bool FillStatusBeforeHighlighted = figSelected->IsShapeFilled();//save the filling status before changing the filling color
			//start highlight
			figSelected->ChngDrawClr(pGUI->getCrntHighlightColor()); //change the draw color of the object to be highlighted
			
			figSelected->ChngFillClr(pGUI->getCrntHighlightColor());//change the filling color to be highlighted
			//filled = true

			figSelected->setFilling(FillStatusBeforeHighlighted);//change the filling status to the saved filling status before being highlighted
			//filled = false/true
			pManager->UpdateInterface();
			pGUI->ClearStatusBar();
			pGUI->PrintMessage(figSelected->GetInfo());
		}
		else
		{
			figSelected->SetSelected(false);
			figSelected->ChngDrawClr(figSelected->getOldDrawColor());
			if (figSelected->IsShapeFilled()) {
				figSelected->ChngFillClr(figSelected->getOldFillColor());
			}
			pManager->UpdateInterface();
			pGUI->ClearStatusBar();
		}
	}
}

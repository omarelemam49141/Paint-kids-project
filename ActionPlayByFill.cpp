#include "ActionPlayByFill.h"
#include "ApplicationManager.h"
#include "GUI/GUI.h"
#include "Figures/CFigure.h"
ActionPlayByFill::ActionPlayByFill(ApplicationManager* pApp) :Action(pApp)
{
	correct = wrong = 0;
}

void ActionPlayByFill::Execute()
{
	for (int i = 0; i < pManager->getFigCount(); i++)
		pManager->DrawnFigs(i)->ShowW();
	pManager->UpdateInterface();
	GUI* pGUI = pManager->GetGUI();
	if (pManager->numberOfShapes() > 0) {
		string color = pManager->getRandomExistingColor();
		int numberOfShapesOfColor = pManager->countByColor(color);
	
		pGUI->PrintMessage("Pick All " + color + " Shapes");
		while (numberOfShapesOfColor > 0) {
			int x, y;
			pGUI->GetPointClicked(x, y);
			if (pGUI->clickedInsideToolBar(x, y))
				break;
			int index;
			CFigure* fig = pManager->GetFigure(x, y, index);
			while (fig == NULL) {
				pGUI->PrintMessage("No Shape Found, Please Click on shape");
				pGUI->getPointInsideDrawArea(x, y);
				fig = pManager->GetFigure(x, y, index);
			}

			if (fig != NULL && pManager->getColorName(fig->getFillColor()) == color) {
				correct++;
				numberOfShapesOfColor--;

				//delete figure on 
				fig->Hide();

			}
			else {
				wrong++;
				fig->Hide();
			}
			pGUI->ClearDrawArea();
			pManager->UpdateInterface();
			pGUI->PrintMessage("Correct: " + to_string(correct) + " || Wrong:" + to_string(wrong));
			if (numberOfShapesOfColor == 0|| (correct + wrong) == pManager->getFigCount()) {
				pGUI->PrintMessage("You Won ^_^ " + to_string(correct) + " / " + to_string(wrong));
			}
		}
	}
	else {
		pGUI->PrintMessage("There is no shapes");
	}
}

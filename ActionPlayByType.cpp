#include "ActionPlayByType.h"
#include "ApplicationManager.h"
#include "GUI/GUI.h"


ActionPlayByType::ActionPlayByType(ApplicationManager* pApp) :Action(pApp)
{
	correct = wrong = 0;

}


void ActionPlayByType::Execute()
{
	for (int i = 0; i < pManager->getFigCount(); i++)
		pManager->DrawnFigs(i)->ShowW();
	pManager->UpdateInterface();
	GUI* pGUI = pManager->GetGUI();
	if (pManager->numberOfShapes() > 0) {
		string type = pManager->getRandomExistingType();
		int numberOfShapesOfType = pManager->countByType(type);		
		pGUI->PrintMessage("Pick All Shapes of type " + type);

		while (numberOfShapesOfType > 0) {
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

			if (fig != NULL && fig->getShapeType() == type) {
				correct++;
				numberOfShapesOfType--;

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
			if (numberOfShapesOfType == 0 || (correct + wrong) == pManager->getFigCount()) {
				pGUI->PrintMessage("You Won ^_^ " + to_string(correct) + " / " + to_string(wrong));
			}
		}
	}
	else {
		pGUI->PrintMessage("There is no shapes");
	}
}
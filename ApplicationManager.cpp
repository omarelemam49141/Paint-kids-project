#include "ApplicationManager.h"
#include "Actions\ActionAddSquare.h"
#include "ActionAddEllipse.h"
#include "ActionAddHexagon.h"
#include "ActionChngDrawClr.h"
#include "ActionChngFillClr.h"
#include "ActionChngBGClr.h"
#include "ActionSelect.h"
#include "ActionChngFigureClr.h"
#include "ActionDelete.h"
#include "ActionSendToBack.h"
#include "ActionSendToFront.h"
#include "ActionResize.h"
#include "ActionSave.h"
#include "ActionLoad.h"
#include "CMUgraphicsLib/colors.h"
#include <fstream>
#include <iostream>
#include <string>
#include "ActionSwitchToPlay.h"
#include "ActionSwitchToDraw.h"
#include "ActionPlayByFill.h"
#include "ActionPlayByType.h"
#include "Actions/ActionPlayByFillType.h"
#include "ActionColorize.h"
#include "ActionExit.h"


//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pGUI = new GUI;	
	
	FigCount = 0;
		
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	
}

void ApplicationManager::Run()
{
	ActionType ActType;
	do
	{		
		//1- Read user action
		ActType = pGUI->MapInputToActionType();

		//2- Create the corresponding Action
		Action *pAct = CreateAction(ActType);
		
		//3- Execute the action
		ExecuteAction(pAct);

		//4- Update the interface
		UpdateInterface();	

	}while(ActType != EXIT);
	
}


//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
//Creates an action
Action* ApplicationManager::CreateAction(ActionType ActType) 
{
	Action* newAct = NULL;
	
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_SQUARE:
			newAct = new ActionAddSquare(this);
			break;
		case DRAW_ELPS:
			newAct = new ActionAddEllipse(this);
			break;
		case DRAW_HEX:
			newAct = new ActionAddHexagon(this);
			break;
		case CHNG_DRAW_CLR:
			newAct = new ActionChngDrawClr(this);
			break;
		case CHNG_FILL_CLR:
			newAct = new ActionChngFillClr(this);
			break;
		case CHNG_BK_CLR:
			newAct = new ActionChngBGClr(this);
			break;
		case DRAWING_AREA:
			newAct = new ActionSelect(this);
			break;
		case CHNG_FIG_CLR:
			newAct = new ActionChngFigureClr(this);
			break;
		case DEL:
			newAct = new ActionDelete(this);
			break;
		case SEND_BACK:
			newAct = new ActionSendToBack(this);
			break;
		case BRNG_FRNT:
			newAct = new ActionSendToFront(this);
			break;
		case QUARTERED_RESIZE: // Resize a figure to 1/4 of it's current size
			newAct = new ActionResize(this, selectedfigure, 0.25);
			break;
		case HALFED_RESIZE: // Resize a figure to 1/2 of it's current size
			newAct = new ActionResize(this, selectedfigure, 0.5);
			break;
		case DOUBLED_RESIZE: // Resize a figure to Double of it's current size
			newAct = new ActionResize(this, selectedfigure, 2);
			break;
		case QUADRUPLE_RESIZED: // Resize a figure to quadruple of it's current size
			newAct = new ActionResize(this, selectedfigure, 4);
			break;
		case SAVE:
			newAct = new ActionSave(this, FigCount);
			break;
		case LOAD:
			newAct = new ActionLoad(this);
			break;
		case TO_PLAY:
			newAct = new ActionSwitchToPlay(this);
			break;

		case TO_DRAW:
			newAct = new ActionSwitchToDraw(this);
			break;

		/////////////////////////////////////
		case ACTION_PLAY_TYPE:
			newAct = new ActionPlayByType(this);
			break;
		case ACTION_PLAY_FILL:
			newAct = new ActionPlayByFill(this);
			break;
		case ACTION_PLAY_TYPEFILL:
			newAct = new ActionPlayByFillType(this);
			break;
		case ACTION_ORANGE:
			newAct = new ActionColorize(this, ORANGE);
			break;
		case ACTION_RED:
			newAct = new ActionColorize(this, RED);
			break;
		case ACTION_PINK:
			newAct = new ActionColorize(this, PINK);
			break;
		case ACTION_BLUE:
			newAct = new ActionColorize(this, BLUE);
			break;
		case ACTION_GREEN:
			newAct = new ActionColorize(this, GREEN);
			break;

		case EXIT:
			ExitMessage();
			break;
		
		case STATUS:	//a click on the status bar ==> no action
			return NULL;
			break;
	}	
	return newAct;
}
//////////////////////////////////////////////////////////////////////
//Executes the created Action
void ApplicationManager::ExecuteAction(Action* &pAct) 
{	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount)
		FigList[FigCount++] = pFig;	
}
//Delete a figure from the list of figures

void ApplicationManager::DeleteFigureAndRearrange(CFigure* pFig, int index)
{
	delete pFig;

	for (int i = index; i < FigCount - 1; i++)
	{
		FigList[i] = FigList[i + 1];
	}

	FigCount--;
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y, int &index) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL


	///Add your code here to search for a figure given a point x,y	
	//Omar
	for (int i = FigCount - 1; i >= 0; i--)
	{
		if (FigList[i]->IsPointInside(x, y))
		{
			index = i;
			return FigList[i];
		}
	}

	return NULL;
}


void ApplicationManager::deleteALLFig()
{
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i] = NULL;

	}

	FigCount = 0;

}
//==================================================================================//
//							Save	load						                        //
//==================================================================================//

//Convert from color object to string to save
string ApplicationManager::colorString(color ClrObj) const
{
	if (ClrObj == WHITE) return "WHITE";
	else if (ClrObj == BLACK) return "BLACK";
	else if (ClrObj == BROWN) return "BROWN";
	else if (ClrObj == PURPLE) return "PURPLE";
	else if (ClrObj == PINK) return "PINK";
	else if (ClrObj == RED) return "RED";
	else if (ClrObj == ORANGE) return "ORANGE";
	else if (ClrObj == YELLOW) return "YELLOW";
	else if (ClrObj == GREEN) return "GREEN";
	else if (ClrObj == BLUE) return "BLUE";
	else if (ClrObj == GREY) return "GREY";
	else if (ClrObj == LIGHTYELLOW) return "LIGHTYELLOW";
	else if (ClrObj == LIGHTCYAN) return "LIGHTCYAN";
	else if (ClrObj == LIGHTGOLDENRODYELLOW) return "LIGHTGOLDENRODYELLOW";
	else return "ORANGE";
}
//Convert from string to object color to load
color ApplicationManager::ColorObject(string ClrStr) const
{
	if (ClrStr == "WHITE") return WHITE;
	else if (ClrStr == "BLACK") return BLACK;
	else if (ClrStr == "BROWN") return BROWN;
	else if (ClrStr == "PURPLE") return PURPLE;
	else if (ClrStr == "PINK") return PINK;
	else if (ClrStr == "RED") return RED;
	else if (ClrStr == "ORANGE") return ORANGE;
	else if (ClrStr == "YELLOW") return YELLOW;
	else if (ClrStr == "GREEN") return GREEN;
	else if (ClrStr == "BLUE") return BLUE;
	else return WHITE;
}

void ApplicationManager::SaveAll(ofstream& Out)
{
	// Iterate through each figure in FigList
	for (int i = 0; i < FigCount; i++) {
		// Call the Save function for each figure, passing the output file stream
		FigList[i]->Save(Out);

	}
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//
void ApplicationManager::clearInterface()
{
	//Create an array of figure pointers and set them to NULL    
	for (int i = 0; i < MaxFigCount; i++)
		FigList[i] = NULL;
	FigCount = 0;
	pGUI->ClearDrawArea();
}
//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	for (int i = 0; i < FigCount; i++)
		if (FigList[i]->HiddenStatus()) {
			continue;
		}
		else {
			FigList[i]->DrawMe(pGUI);
		}
}
////////////////////////////////////////////////////////////////////////////////////
// 
// CFigure* currentFigure = NULL;
bool ApplicationManager::DeleteSelectedObjects()
{
	int countDeleted = 0;
	for (int i = FigCount-1; i >= 0; i--)
	{
		if (FigList[i]->IsSelected())
		{
			DeleteFigureAndRearrange(FigList[i], i);
			pGUI->PrintMessage("Deleted successfully");
			countDeleted++;
		}
	}

	return countDeleted > 0;
}

//omar
//loop through the figures, if selected then multiplicate it by factor
//if no selected at all, then return false

CFigure* ApplicationManager::GetFigureByIndex(int index)
{
	return FigList[index];
}

int ApplicationManager::GetCount()
{
	return FigCount;
}

//BringToFront/back
int ApplicationManager::GetSelectedFigureIndex()
{
	for (int i = FigCount - 1; i >= 0; i--)
	{
		if (FigList[i]->IsSelected())
			return i;
	}
	return -1;
}

void ApplicationManager::sendFigToBack(int index)
{
	CFigure* temp = FigList[index];

	for (int i = index; i > 0; i--)
	{
		FigList[i] = FigList[i - 1];
	}

	FigList[0] = temp;
	temp = NULL;
}

void ApplicationManager::sendFigToFront(int index)
{
	CFigure* temp = FigList[index];

	for (int i = index; i < FigCount - 1; i++)
	{
		FigList[i] = FigList[i + 1];
	}

	FigList[FigCount - 1] = temp;
	temp = NULL;
}
//resize functionality
CFigure* ApplicationManager::GetSelectedFigure() const
{
	//check if a figure selected
	for (int i = (FigCount - 1); i >= 0; i--) {
		if (FigList[i]->IsSelected()) return FigList[i];
	}
	return NULL;
}

int ApplicationManager::GetSelectedCount() {
	selectedCount = 0;
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
			selectedCount++;

	}
	return selectedCount;
}

//Return a pointer to the interface
GUI *ApplicationManager::GetGUI() const
{	return pGUI; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pGUI;
	
}



int ApplicationManager::numberOfShapes()
{
	return FigCount;
}
int ApplicationManager::countByType(string type) {
	int count = 0;
	for (int i = 0; i < FigCount; i++)
		if (FigList[i]->getShapeType() == type)
			count++;
	return count;
}
int ApplicationManager::getFigCount() const
{
	return FigCount;

}
CFigure* ApplicationManager::DrawnFigs(int i) const
{
	return FigList[i];
}

string ApplicationManager::getRandomExistingColor()
{
	//generating Random index 
	int RandomIndex = rand() % FigCount;

	color tempClr = FigList[RandomIndex]->getFillColor();

	return getColorName(tempClr);

}
string ApplicationManager::getRandomExistingType()
{
	//generating Random index 
	int RandomIndex = rand() % FigCount;

	string type = FigList[RandomIndex]->getShapeType();

	return type;

}

int ApplicationManager::countByColor(string color) {
	int count = 0;
	for (int i = 0; i < FigCount; i++)
		if (getColorName(FigList[i]->getFillColor()) == color)
			count++;
	return count;
}


string ApplicationManager::getColorName(color c)
{
	
	if ((c.ucBlue == PINK.ucBlue) && (c.ucGreen == PINK.ucGreen) && (c.ucRed == PINK.ucRed))
		return "PINK";
	if ((c.ucBlue == ORANGE.ucBlue) && (c.ucGreen == ORANGE.ucGreen) && (c.ucRed == ORANGE.ucRed))
		return "ORANGE";
	if ((c.ucBlue == BLUE.ucBlue) && (c.ucGreen == BLUE.ucGreen) && (c.ucRed == BLUE.ucRed))
		return "BLUE";
	if ((c.ucBlue == RED.ucBlue) && (c.ucGreen == RED.ucGreen) && (c.ucRed == RED.ucRed))
		return "RED";
	if ((c.ucBlue == GREEN.ucBlue) && (c.ucGreen == GREEN.ucGreen) && (c.ucRed == GREEN.ucRed))
		return "GREEN";
	return "NO-FILL";
}

void ApplicationManager::getRandomColorAndType(string& type, string& color)
{
	//generating Random index
	int RandomIndex = rand() % FigCount;
	type = FigList[RandomIndex]->getShapeType();
	color = getColorName(FigList[RandomIndex]->getFillColor());
}
int ApplicationManager::countByTypeAndColor(string type, string color) {
	int count = 0;
	for (int i = 0; i < FigCount; i++)
		if (FigList[i]->getShapeType() == type && getColorName(FigList[i]->getFillColor()) == color)
			count++;
	return count;
}

int ApplicationManager::ExitMessage()
{
	int msgboxID = MessageBox(
		NULL,
		"Do You want to leave befor saving your file?\n Click ok to Leave\nClick cancel to Save",
		"Exit",
		MB_OKCANCEL | MB_ICONWARNING
	);

	switch (msgboxID)
	{
	case IDCANCEL:
	{

		Action* newAct = new ActionSave(this, FigCount);
		ExecuteAction(newAct);
	}
	break;
	case IDOK:
		exit(0);
		break;
	}

	return msgboxID;
}

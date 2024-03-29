#ifndef GUI_H
#define GUI_H

#include "..\DEFS.h"
#include "UI_Info.h" 
#include "..\CMUgraphicsLib\CMUgraphics.h"


//This class is responsible for Grphical User Interface handling
//All user input and program outputs MUST be done through this class
//No other class is allowed to perform direct i/o
class GUI	
{
public:	
	window* pWind;	//Pointer to the Graphics Window
public:
	GUI();	
	~GUI();	
	window* CreateWind(int, int, int , int) const; //creates the application window

	/////////// Input Functoinality  /////////////////
	void GetPointClicked(int &x, int &y) const;//Get coordinate where user clicks
	string GetSrting() const ;	 //Returns a string entered by the user
	ActionType MapInputToActionType() const; //Read the user click and map to an action


	/////////// Output Functoinality  ////////////////
	void CreateDrawToolBar() const;	//creates Draw mode toolbar & menu
	void CreatePlayToolBar() const;	//creates Play mode toolbar & menu
	void CreateStatusBar() const;	//create the status bar

	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area
	void ClearToolBar() const;

	void CreateColorToolBar(char colorMode) const;

	void ChangeColors(color clr);

	// -- Figures Drawing functions
	void DrawSquare(Point P1, int length, GfxInfo RectGfxInfo, bool selected=false) const;  //Draw a Square

	//Omar
	//Draw Ellipse
	void DrawEllipse(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const;
	//Omar
	//Draw Hexagon
	void DrawHexagon(int* xCoords, int* yCoords, int vertexes, GfxInfo RectGfxInfo, bool selected) const;
	
	///TODO: Make similar functions for drawing all other figures.
	
	void PrintMessage(string msg) const;	//Print a message on Status bar

	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;	//get current filling color
	color getCrntBGColor() const;
	void setCrntDrawColor(color); //omar//set current drawing color
	void setCrntFillColor(color); //omar//set current fill color
	void setCrntBGColor(color); //omar//set current bg color
	int getCrntPenWidth() const;		//get current pen width
	color getCrntHighlightColor() const; //get highlighted color
	//Check if excceding the drawing area
	bool ExceedDrawingArea(int minX, int minY, int maxX, int maxY);
	double GUI::GetNumber() const; //get a number for resizing


	void getPointInsideDrawArea(int& x, int& y); // get point inside draw area
	bool clickedInsideToolBar(int& x, int& y); //check if the point is inside the toolbar

};


#endif
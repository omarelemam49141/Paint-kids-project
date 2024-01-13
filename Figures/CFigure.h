#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\defs.h"
#include "..\GUI\GUI.h"

//Base class for all figures
class CFigure
{
protected:
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
	bool PlayHidden;
	color oldFillClr;
	color oldDrawClr;
	bool IsFilled;
	
	/// Add more parameters if needed.

public:
	static bool filledChanged;
	CFigure(GfxInfo FigureGfxInfo);
	CFigure();
	void SetSelected(bool );	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected
	bool IsShapeFilled() const;

	virtual void DrawMe(GUI*) const  = 0 ;		//Draw the figure
	
	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color
	void setOldFillClr(color clr);
	void setOldDrawClr(color clr);
	void setFilling(bool filled);

	//Omar
	virtual bool IsPointInside(int x, int y)=0;
	virtual string GetInfo() = 0;
	virtual float CalcArea() = 0;

	//Save asma
	string ColorString(color) const;
	color ColorObject(string) const;
	virtual void Save(ofstream& OutFile) = 0;
	virtual void Load(ifstream& File) = 0;
	void show();
	bool IsHidden();

	//nyra
	virtual void Resize(GUI* pGUI, float size) = 0;
	virtual string getShapeType() = 0;  // to get type of the shape
	color getDrawColor();
	color getFillColor();
	color getOldFillColor();
	color getOldDrawColor();
	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	


	//virtual void Rotate() = 0;	//Rotate the figure
	//virtual void Resize() = 0;	//Resize the figure
	//virtual void Move() = 0;		//Move the figure

	//virtual void Save(ofstream &OutFile) = 0;	//Save the figure parameters to the file
	//virtual void Load(ifstream &Infile) = 0;	//Load the figure parameters to the file

	//virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar

	void Hide();
	void ShowW();
	bool CFigure::HiddenStatus();
};
#endif
#include "CFigure.h"

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	if (filledChanged)
	{
		FigGfxInfo.isFilled = true;
	}
	else {
		FigGfxInfo.isFilled = false;
	}
	PlayHidden = false;
}

bool CFigure::filledChanged = false;

CFigure::CFigure() {
	Selected = false;
	if (filledChanged)
	{
		FigGfxInfo.isFilled = true;
	}
	else {
		FigGfxInfo.isFilled = false;
	}
	PlayHidden = false;
}

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }

bool CFigure::IsShapeFilled() const
{
	return FigGfxInfo.isFilled;
}

void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }


void CFigure::ChngFillClr(color Fclr)
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}

void CFigure::setFilling(bool filled)
{
	FigGfxInfo.isFilled = filled;
}

//asmaa
//This function takes a color object as an argument and returns its  string representation.(Convert from Color Type to String Type)
string CFigure::ColorString(color ClrObj) const
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
	else return "ORANGE";
}
//asma
//This function takes a color object as an argument and returns its  string representation.(Convert from string to color object)
color CFigure::ColorObject(string ClrStr) const
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

//this function returns the value of the IsHidden member variable of the FigGfxInfo
bool CFigure::IsHidden() {
	return FigGfxInfo.IsHidden;
};
//asma
//to show the figure 
void CFigure::show() {
	FigGfxInfo.IsHidden = false;
};

void CFigure::Hide()
{
	PlayHidden = true;
}
void CFigure::ShowW()
{
	PlayHidden = false;
}

color CFigure::getFillColor()
{
	return FigGfxInfo.isFilled ? FigGfxInfo.FillClr : NULL;
}

color CFigure::getDrawColor()
{
	return FigGfxInfo.DrawClr;
}

void CFigure::setOldFillClr(color clr)
{
	oldFillClr = clr;
}

void CFigure::setOldDrawClr(color clr)
{
	oldDrawClr = clr;
}

color CFigure::getOldDrawColor()
{
	return oldDrawClr;
}

color CFigure::getOldFillColor()
{
	return oldFillClr;
}

bool CFigure::HiddenStatus() {
	return PlayHidden;
}
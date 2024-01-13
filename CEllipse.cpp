#include "CEllipse.h"
#include <iostream>
#include <fstream>
using namespace std;

CEllipse::CEllipse(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	pointone = P1;
	pointtwo = P2;
}

CEllipse::CEllipse() {
	pointone = {};
	pointtwo = {};
}

void CEllipse::DrawMe(GUI* pGUI) const
{
	//Call Output::Draw Ellipse	
	pGUI->DrawEllipse(pointone, pointtwo, FigGfxInfo, Selected);
}

bool CEllipse::IsPointInside(int x, int y)
{
    // Calculate the normalized coordinates relative to the center
    double normalizedX = (x - (pointone.x + pointtwo.x) / 2.0) / ((pointtwo.x - pointone.x) / 2.0);
    double normalizedY = (y - (pointone.y + pointtwo.y) / 2.0) / ((pointtwo.y - pointone.y) / 2.0);

    // Check if the point satisfies the ellipse equation
    return (normalizedX * normalizedX + normalizedY * normalizedY) <= 1.0;
}

string CEllipse::GetInfo()
{
    return "First point: (" + to_string(pointone.x) + ", " + to_string(pointone.y) + ")" + 
        " - Second point: (" + to_string(pointtwo.x) + ", " + to_string(pointtwo.y) + ")"
        + " - Area: " + to_string(CalcArea());
}

float CEllipse::CalcArea()
{
    double semiMajorAxis = std::abs(pointtwo.x - pointone.x) / 2.0;
    double semiMinorAxis = std::abs(pointtwo.y - pointone.y) / 2.0;

    // Calculate the area of the ellipse
    double area = (22/7) * semiMajorAxis * semiMinorAxis;
    return area;
}

void CEllipse::Save(ofstream& OutFile) {

    OutFile << "CEllipse\t" //the type of the figure(CEllipse)
        //the coordinates of the two points that define the ellipse
        << this->pointone.x << "\t"
        << this->pointone.y << "\t"
        << this->pointtwo.x << "\t"
        << this->pointtwo.y << "\t"
        // the drawing color
        << this->ColorString(this->FigGfxInfo.DrawClr) << "\t";
    // check figure is filled or not
    if (this->FigGfxInfo.isFilled)
        //the fill color
        OutFile << this->ColorString(this->FigGfxInfo.FillClr) << "\n";
    else
        OutFile << "NO_FILL\n";
}
//asmaa
//This function reads the details of the ellipse figure from the input file stream 
void CEllipse::Load(ifstream& Infile) {
    // It reads the coordinates of the two points(pointone and pointtwo)
    string ellipseData;
    Infile >> pointone.x
        >> pointone.y
        >> pointtwo.x
        >> pointtwo.y;

    // the drawing color
    Infile >> ellipseData;
    FigGfxInfo.DrawClr = this->ColorObject(ellipseData);

    //and the fill color
    Infile >> ellipseData;
    if (ellipseData == "NO_FILL")
        FigGfxInfo.isFilled = false;
    else
    {
        FigGfxInfo.FillClr = this->ColorObject(ellipseData);
        FigGfxInfo.isFilled = true;
    }

    //show figure
    this->show();
    this->FigGfxInfo.BorderWdth = 3;
    this->SetSelected(false);
}
//nyra

void CEllipse::Resize(GUI* pGUI, float size) {
    Point test1 = pointone, test2 = pointtwo;

    // Define a tolerance for floating-point comparisons
    const float tolerance = 1e-6;

    // Adjust the size if it matches one of the special cases
    if (std::abs(size - 0.5) < tolerance) {
        size = 0.5;
    }
    else if (std::abs(size - 0.25) < tolerance) {
        // Resize to 1/4 by adjusting the points relative to the current size
        float currentSizeX = (test2.x - test1.x) / 2;
        float currentSizeY = (test2.y - test1.y) / 2;
        float adjustmentX = currentSizeX * 0.75;
        float adjustmentY = currentSizeY * 0.75;

        // Check if the resized ellipse would be too small
        if (((test2.x - test1.x) - 2 * adjustmentX) < 5 || ((test2.y - test1.y) - 2 * adjustmentY) < 5) {
            pGUI->PrintMessage("Resizing ellipse would make it too small");
            return;
        }

        test1.x += adjustmentX;
        test2.x -= adjustmentX;
        test1.y += adjustmentY;
        test2.y -= adjustmentY;

        pointone = test1;
        pointtwo = test2;
        return;
    }
    else if (std::abs(size - 2.0) < tolerance) {
        size = 2.0;
    }
    else if (std::abs(size - 1.0) < tolerance) {
        size = 1.0;
    }

    // Calculate half radius (horizontal x && vertical y)
    float deltaX = 0.5 * (test2.x - test1.x);
    float deltaY = 0.5 * (test2.y - test1.y);

    // Calculate resized points
    test1.x -= deltaX * (size - 1);
    test2.x += deltaX * (size - 1);
    test1.y -= deltaY * (size - 1);
    test2.y += deltaY * (size - 1);

    // Check if the resized ellipse is within the drawing area
    if (test1.y < UI.ToolBarHeight || test2.y > UI.height - UI.StatusBarHeight
        || test2.x > UI.width || test1.x < 1) {
        pGUI->PrintMessage("Resizing ellipse would place it outside the drawing area");
        return;
    }
    // Check if the resized ellipse is too small
    if (((test2.x - test1.x) / 2) < 5 || ((test2.y - test1.y) / 2) < 5) {
        pGUI->PrintMessage("Resizing ellipse would make it too small");
        return;
    }

    // Apply the resized points if no issues
    pointone = test1;
    pointtwo = test2;
}


//omar return the details

string CEllipse::getShapeType()
{
    return "Ellipse";
}
#include "CHexagon.h"
#include <iostream>
#include <fstream>
using namespace std;
CHexagon::CHexagon(int *_xCoords, int* _yCoords, int _vertexes, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
    xCoordinates = _xCoords;
    yCoordinates = _yCoords;
	vertexes = _vertexes;
}

CHexagon::CHexagon() {
    xCoordinates = new int[6];
    yCoordinates = new int[6];
    vertexes = 6;
}


void CHexagon::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawHexagon to draw a hexagon on the screen	
	pGUI->DrawHexagon(xCoordinates, yCoordinates, vertexes, FigGfxInfo, Selected);
}

bool CHexagon::IsPointInside(int x, int y)
{
    // Check if the point is within the bounding box of the hexagon
    int minX = *std::min_element(xCoordinates, xCoordinates + vertexes);
    int maxX = *std::max_element(xCoordinates, xCoordinates + vertexes);
    int minY = *std::min_element(yCoordinates, yCoordinates + vertexes);
    int maxY = *std::max_element(yCoordinates, yCoordinates + vertexes);

    if (x < minX || x > maxX || y < minY || y > maxY) {
        return false;  // The point is outside the bounding box
    }

    // Check if the point is inside the hexagon using a ray-casting algorithm
    int crossings = 0;
    for (int i = 0; i < vertexes; ++i) {
        int x1 = xCoordinates[i];
        int y1 = yCoordinates[i];
        int x2 = xCoordinates[(i + 1) % vertexes];
        int y2 = yCoordinates[(i + 1) % vertexes];

        if (((y1 <= y && y < y2) || (y2 <= y && y < y1)) &&
            x < (x2 - x1) * (y - y1) / (y2 - y1) + x1) {
            crossings++;
        }
    }

    // If the number of crossings is odd, the point is inside the hexagon
    return (crossings % 2 == 1);
}

string CHexagon::GetInfo()
{
    return  "First point : (" + to_string(xCoordinates[0]) + ", " + to_string(yCoordinates[0]) + ")" +
        " - Second point: (" + to_string(xCoordinates[1]) + ", " + to_string(yCoordinates[1]) + ")"
        + " - vertexes count is: " + to_string(vertexes)
        + " - Area is : " + to_string(CalcArea());
}

float CHexagon::CalcArea()
{
    float sideLength = std::sqrt(std::pow(xCoordinates[1] - xCoordinates[0], 2) + std::pow(yCoordinates[1] - yCoordinates[0], 2));

    // Calculate the area of a regular hexagon
    double area = (3.0 * std::sqrt(3.0) / 2.0) * std::pow(sideLength, 2);
    return area;
}

//asma save This function writes the details of the ellipse figure to the output file stream (OutFile).
void CHexagon::Save(ofstream& OutFile) {
    //the type of the figure
    OutFile << "CHexagon\t";

    //the vertexes and points 
    OutFile << this->vertexes << "\t";
    for (int i = 0; i < vertexes; i++) {
        OutFile << this->yCoordinates[i] << "\t";
    }
    for (int i = 0; i < vertexes; i++) {
        OutFile << this->xCoordinates[i] << "\t";
    }


    // the drawing color
    OutFile << ColorString(this->FigGfxInfo.DrawClr) << "\t";


    //the fill color
    if (this->FigGfxInfo.isFilled)
        OutFile << this->ColorString(this->FigGfxInfo.FillClr) << "\n";
    else
        OutFile << "NO_FILL\n";
}

//asmaa
//This function reads the details of the ellipse figure from the input file stream 
void CHexagon::Load(ifstream& Infile) {
    string hexagonData;
    
    // It reads the vertexes and points
    Infile >> vertexes;
    yCoordinates = new int[vertexes];
    xCoordinates = new int[vertexes];
    for (int i = 0; i < vertexes; i++) {
        Infile >> yCoordinates[i];
    }
    for (int i = 0; i < vertexes; i++) {
        Infile >> xCoordinates[i];
    }

    // the drawing color
    Infile >> hexagonData;
    FigGfxInfo.DrawClr = ColorObject(hexagonData);

    //and the fill color
    Infile >> hexagonData;
    if (hexagonData == "NO_FILL") {
        FigGfxInfo.isFilled = false;
        FigGfxInfo.FillClr = this->ColorObject(hexagonData);
    }
    else
    {
        FigGfxInfo.FillClr = this->ColorObject(hexagonData);
        FigGfxInfo.isFilled = true;
    }

    //show figure
    this->show();
    this->FigGfxInfo.BorderWdth = 3; //pass 3 as default value for borderWidth
    this->SetSelected(false);
}

//nyra
//function to resize the hexagon 
void CHexagon::Resize(GUI* pGUI, float scaleFactor)
{
    // Minimum size threshold to prevent resizing too small
    const float minSizeThreshold = 10.0;

    // Calculate the center of the hexagon
    float centerX = 0, centerY = 0;
    for (int i = 0; i < vertexes; ++i) {
        centerX += xCoordinates[i];
        centerY += yCoordinates[i];
    }
    centerX /= vertexes;
    centerY /= vertexes;

    // Check if the resized hexagon would be outside the drawing area
    for (int i = 0; i < vertexes; ++i) {
        float dx = xCoordinates[i] - centerX;
        float dy = yCoordinates[i] - centerY;

        // Calculate the original distance from the center
        float originalDistance = std::hypot(dx, dy);

        // Calculate the scaled distance from the center
        float scaledDistance = originalDistance * scaleFactor;

        // Check if the new position is outside the drawing area or below the minimum size threshold
        if (scaledDistance < minSizeThreshold ||
            (centerX + scaledDistance * (dx / originalDistance)) < 0 ||
            (centerX + scaledDistance * (dx / originalDistance)) > UI.width ||
            (centerY + scaledDistance * (dy / originalDistance)) < UI.ToolBarHeight ||
            (centerY + scaledDistance * (dy / originalDistance)) > UI.height - UI.StatusBarHeight) {
            pGUI->PrintMessage("Resizing hexagon exceeds drawing area or is too small");
            return;  // Abort resizing
        }
    }

    // If all vertices are within the drawing area and above the minimum size, apply the resizing
    for (int i = 0; i < vertexes; ++i) {
        float dx = xCoordinates[i] - centerX;
        float dy = yCoordinates[i] - centerY;

        // Calculate the original distance from the center
        float originalDistance = std::hypot(dx, dy);

        // Calculate the scaled distance from the center
        float scaledDistance = originalDistance * scaleFactor;

        // Resize the distance from the center by the scale factor
        xCoordinates[i] = static_cast<int>(centerX + scaledDistance * (dx / originalDistance));
        yCoordinates[i] = static_cast<int>(centerY + scaledDistance * (dy / originalDistance));
    }
}
void CHexagon::ResetToOriginalSize()
{
    for (int i = 0; i < vertexes; ++i) {
        xCoordinates[i] = originalXCoordinates[i];
        yCoordinates[i] = originalYCoordinates[i];
    }
}


string CHexagon::getShapeType()
{
    return "Hexagon";
}
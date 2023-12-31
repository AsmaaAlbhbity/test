#include "CHexagon.h"
#include <iostream>
#include <fstream>
CHexagon::CHexagon(int *_xCoords, int* _yCoords, int _vertexes, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
    xCoordinates = _xCoords;
    yCoordinates = _yCoords;
	vertexes = _vertexes;
}
CHexagon::CHexagon(){}

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

//asma save
void CHexagon::Save(ofstream& OutFile) {
    OutFile << "CHexagon\t";
    OutFile << this->vertexes << "\t";
    for (int i = 0;i < vertexes;i++) {
        OutFile << this->yCoordinates[i] << "\t";
    }
    for (int i = 0;i < vertexes;i++) {
        OutFile << this->xCoordinates[i] << "\t";
    }

    OutFile << ColorString(this->FigGfxInfo.DrawClr) << "\t";



    if (this->FigGfxInfo.isFilled)
        OutFile << this->ColorString(this->FigGfxInfo.FillClr) << "\n";
    else
        OutFile << "NO_FILL\n";
}

void CHexagon::Load(ifstream& Infile) {
    string hexagonData;
    Infile >>vertexes ;
    for (int i = 0;i < vertexes;i++) {
        Infile >> yCoordinates[i] ;
    }
    for (int i = 0;i < vertexes;i++) {
        Infile >> xCoordinates[i] ;
    }
    
    Infile >> hexagonData;
    FigGfxInfo.DrawClr = ColorObject(hexagonData);

    Infile >> hexagonData;
    if (hexagonData == "NO_FILL")
        FigGfxInfo.isFilled = false;
    else
    {
        FigGfxInfo.FillClr = ColorObject(hexagonData);
        FigGfxInfo.isFilled = true;
    }
    this->show();
    this->FigGfxInfo.BorderWdth = 5; //pass 3 as default value for borderWidth
    this->SetSelected(false);
}

//omar return the details
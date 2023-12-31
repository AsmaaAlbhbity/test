#include "CEllipse.h"
#include <iostream>
#include <fstream>
CEllipse::CEllipse(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	pointone = P1;
	pointtwo = P2;
}
CEllipse::CEllipse() {}; //default constructor

void CEllipse::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
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

//omar return the details

//asma save
void CEllipse::Save(ofstream& OutFile) {

	OutFile << "CEllipse\t"
		<< this->pointone.x << "\t"
		<< this->pointone.y << "\t"
		<< this->pointtwo.x << "\t"
		<< this->pointtwo.y << "\t"
		<< this->ColorString(this->FigGfxInfo.DrawClr) << "\t";
	// check figure is filled or not
	if (this->FigGfxInfo.isFilled)
		OutFile << this->ColorString(this->FigGfxInfo.FillClr) << "\n";
	else
		OutFile << "NO_FILL\n";
}
void CEllipse::Load(ifstream& Infile) {
	string ellipseData;
	Infile >> pointone.x
		>> pointone.y
		>> pointtwo.x
		>> pointtwo.y;

	Infile >> ellipseData;
	FigGfxInfo.DrawClr = this->ColorObject(ellipseData);

	Infile >> ellipseData;
	if (ellipseData == "NO_FILL")
		FigGfxInfo.isFilled = false;
	else
	{
		FigGfxInfo.FillClr = this->ColorObject(ellipseData);
		FigGfxInfo.isFilled = true;
	}
	this->show();
	this->FigGfxInfo.BorderWdth = 5;
	this->SetSelected(false);
}
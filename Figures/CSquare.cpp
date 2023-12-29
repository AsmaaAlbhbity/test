#include "CSquare.h"
#include <iostream>
#include <fstream>
using namespace std;

CSquare::CSquare(Point P1, int len, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	length = len;
}
CSquare::CSquare() {};

void CSquare::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawSquare(TopLeftCorner, length, FigGfxInfo, Selected);
}
//asmaa save
void CSquare::Save(ofstream& OutFile) {

	cout << "i get called";
	OutFile << "CSquare\t"
		<< this->TopLeftCorner.x << "\t"
		<< this->TopLeftCorner.y << "\t"
		<< this->length << "\t"
		<< this->ColorString(this->FigGfxInfo.DrawClr) << "\t";

	if (this->FigGfxInfo.isFilled)
		OutFile << this->ColorString(this->FigGfxInfo.FillClr) << "\n";
	else
		OutFile << "NO_FILL\n";
}
void CSquare::Load(ifstream& Infile) {

	string squareData;
	Infile
		>> ID
		>> TopLeftCorner.x
		>> TopLeftCorner.y
		>> length;

	Infile >> squareData;
	FigGfxInfo.DrawClr = this->ColorObject(squareData);

	Infile >> squareData;
	if (squareData == "NO_FILL")
		FigGfxInfo.isFilled = false;
	else
	{
		FigGfxInfo.FillClr = this->ColorObject(squareData);
		FigGfxInfo.isFilled = true;
	}
	this->show();
	this->FigGfxInfo.BorderWdth = 5; //pass 3 as default value for borderWidth
	this->SetSelected(false);

}

//omar
bool CSquare::IsPointInside(int x, int y)
{
	// Check if the point is within the bounds of the square
	return (x >= TopLeftCorner.x && x <= TopLeftCorner.x + length &&
		y >= TopLeftCorner.y && y <= TopLeftCorner.y + length);
}

//omar return the details
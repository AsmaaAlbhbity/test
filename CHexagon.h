#ifndef CHEXAGON_H
#define CHEXAGON_H
#endif

#include "figures/CFigure.h"

class CHexagon : public CFigure
{
private:
	int * xCoordinates;
	int* yCoordinates;
	int vertexes;
public:
	CHexagon(int *, int*, int, GfxInfo FigureGfxInfo);
	CHexagon();
	virtual void DrawMe(GUI* pOut) const;

	bool IsPointInside(int x, int y);
	//asma
	void Save(ofstream&);
	void Load(ifstream&);
	
};

#include "ActionLoad.h"
#include "ApplicationManager.h"
#include "GUI\GUI.h"
#include "Figures\CFigure.h"
#include "Figures\CSquare.h"
#include "CHexagon.h"
#include "CEllipse.h"
#include <fstream>
#include <iostream>

ActionLoad::ActionLoad(ApplicationManager* pApp) :Action(pApp)
{
}

void ActionLoad::Execute()
{
	int r, g, b;
	ifstream File;
	bool flag = false;
	string figName, drawclr, fillclr;
	int figcount;
	CFigure* fig;
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("please write the file name -->");
	FileName = pGUI->GetSrting();



	File.open("saved_Drawing_files/" + FileName + ".txt");


	if (File.fail())
	{
		pGUI->PrintMessage("invalid name");
		return;
	}
	pGUI->ClearDrawArea();
	pManager->deleteALLFig();

	
	File >> r >> g >> b;
	color drawClr(r, g, b);
	File >> r >> g >> b;
	color FillClr(r, g, b);
	File >> r >> g >> b;
	color bkgclr(r, g, b);

	cout << r;

	pGUI->setCrntDrawColor(drawClr);
	pGUI->setCrntFillColor(FillClr);
	pGUI->setCrntBGColor(bkgclr);
	File >> figcount;
	cout << figcount;
	

	while (figcount)
	{
		
		cout << figcount;
		File >> figName;
		
		 if (figName == "CEllipse")
		{
			fig = new CEllipse();
			cout << "Elipse" << endl;
		}
		else if (figName == "CSquare") {
			fig = new CSquare();
			cout << "Square" << endl;
		}
		
		else if (figName == "CHexagon") {
			fig = new CHexagon();
			cout << "Hexagon" << endl;
		}

		fig->Load(File);
		pManager->AddFigure(fig);

		figcount--;
	}
	pManager->UpdateInterface();    //draw the figure list
	pGUI->PrintMessage("File Loaded.. ^_^");
	pGUI->ClearStatusBar();
}


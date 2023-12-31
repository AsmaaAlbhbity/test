#include "ApplicationManager.h"
#include "Actions\ActionAddSquare.h"
#include "ActionAddEllipse.h"
#include "ActionAddHexagon.h"
#include "ActionChngDrawClr.h"
#include "ActionChngFillClr.h"
#include "ActionChngBGClr.h"
#include "ActionSelect.h"
#include "ActionDelete.h"
#include "ActionSave.h"
#include "ActionLoad.h"
#include "CMUgraphicsLib/colors.h"
#include <fstream>
#include <iostream>
#include <string>


//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pGUI = new GUI;	
	
	FigCount = 0;
		
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	
}

void ApplicationManager::Run()
{
	ActionType ActType;
	do
	{		
		//1- Read user action
		ActType = pGUI->MapInputToActionType();

		//2- Create the corresponding Action
		Action *pAct = CreateAction(ActType);
		
		//3- Execute the action
		ExecuteAction(pAct);

		//4- Update the interface
		UpdateInterface();	

	}while(ActType != EXIT);
	
}


//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
//Creates an action
Action* ApplicationManager::CreateAction(ActionType ActType) 
{
	Action* newAct = NULL;
	
	
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_SQUARE:
			newAct = new ActionAddSquare(this);
			break;
		case DRAW_ELPS:
			newAct = new ActionAddEllipse(this);
			break;
		case DRAW_HEX:
			newAct = new ActionAddHexagon(this);
			break;
		case CHNG_DRAW_CLR:
			newAct = new ActionChngDrawClr(this);
			break;
		case CHNG_FILL_CLR:
			newAct = new ActionChngFillClr(this);
			break;
		case CHNG_BK_CLR:
			newAct = new ActionChngBGClr(this);
			break;
		case DRAWING_AREA:
			newAct = new ActionSelect(this);
			break;
		case DEL:
			newAct = new ActionDelete(this);
			break;
		case SAVE:
			newAct = new ActionSave(this, FigCount, 0);
			break;
		case LOAD:
			newAct = new ActionLoad(this);
			break;
			
		case EXIT:
			///create ExitAction here
			break;
		
		case STATUS:	//a click on the status bar ==> no action
			return NULL;
			break;
	}	
	return newAct;
}
//////////////////////////////////////////////////////////////////////
//Executes the created Action
void ApplicationManager::ExecuteAction(Action* &pAct) 
{	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount)
		FigList[FigCount++] = pFig;	
}
////////////////////////////////////////////////////////////////////////////////////
CFigure* ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL


	///Add your code here to search for a figure given a point x,y	
	//Omar
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsPointInside(x, y))
			return FigList[i];
	}

	return NULL;
}
//==================================================================================//
//							Delete							                        //
//==================================================================================//

CFigure* ApplicationManager::getSelected()
{
	int index = -1;
	for (int i = 0; i < FigCount; i++)
		if (FigList[i]->IsSelected()) {
			index = i;
			break;
		}

	if (index >= 0 && index < FigCount)
		return FigList[index];
	return NULL;
}

// -- For  Figure Deleted 
int ApplicationManager::DeleteFigure()
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			delete FigList[i];
			FigList[i] = NULL;
			FigCount--;
			return i;
		}
	}
}

// After delete figure shift elements and delete null
void ApplicationManager::shiftFigList(int _figCount)
{
	for (int j = _figCount; j < FigCount; j++)
	{
		FigList[j] = FigList[j + 1];
	}
}

//==================================================================================//
//							Save	load						                        //
//==================================================================================//

//Convert from color object to string to save
string ApplicationManager::colorString( color ClrObj ) const
{
	if ( ClrObj == WHITE) return "WHITE";
	else if (ClrObj == BLACK) return "BLACK";
	else if (ClrObj == BROWN) return "BROWN";
	else if (ClrObj == PURPLE) return "PURPLE";
	else if (ClrObj == PINK) return "PINK";
	else if (ClrObj == RED) return "RED";
	else if (ClrObj == ORANGE) return "ORANGE";
	else if (ClrObj == YELLOW) return "YELLOW";
	else if (ClrObj == GREEN) return "GREEN";
	else if (ClrObj == BLUE) return "BLUE";
	else return "GREEN";
}
color ApplicationManager::ColorObject(string ClrStr) const
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
	else return BLUE;
}

void ApplicationManager::SaveAll(ofstream& Out)
{
	cout << "iamheeeeeeer";
	for (int i = 0; i < FigCount; i++) {
	
				FigList[i]->Save(Out);
			
	}
}
void ApplicationManager::deleteALLFig()
{
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i] = NULL;

	}

	FigCount = 0;

}

//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	for(int i=0; i<FigCount; i++)
		FigList[i]->DrawMe(pGUI);		//Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the interface
GUI *ApplicationManager::GetGUI() const
{	return pGUI; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pGUI;
	
}

#include "ChangeDrwClrAction.h"
#include "..\ApplicationManager.h"


ChangeDrwClrAction::ChangeDrwClrAction(ApplicationManager*pApp):Action(pApp)
{
	pManager->GetOutput()->CreateColorToolBar();
}


ChangeDrwClrAction::~ChangeDrwClrAction()
{
	pManager->GetOutput()->CreateDrawToolBar();
}

void ChangeDrwClrAction::Execute()
{
	
	pManager->GetOutput()->PrintMessage("Choose the Draw color");
	Point clickedPoint;
	do {
		pManager->GetInput()->GetPointClicked(clickedPoint.x, clickedPoint.y);
		if (clickedPoint.y > pManager->GetOutput()->getUIToolBarHeight()
			|| CLR_ITM_COUNT <= (clickedPoint.x / pManager->GetOutput()->getUIMenuItemWidth()))
			continue;
		if (CLR_BACK == (clickedPoint.x / pManager->GetOutput()->getUIMenuItemWidth()))
		{
			pManager->GetOutput()->ClearStatusBar();
			return;
		}
		color DrawClr =GetColor(clickedPoint);
		if (pManager->ThereIsSelectedFigs())
		{
			ChngSelectedFigsDrwClr(DrawClr);
			pManager->UpdateInterface();
			pManager->GetOutput()->PrintMessage("Draw color of selected figures is Changed to "
			+pManager->GetOutput()->ColorToString(DrawClr));
		}
		else
		{
			pManager->GetOutput()->setCrntDrawColor(DrawClr);
			pManager->GetOutput()->PrintMessage("Draw color is Changed to "
			+pManager->GetOutput()->ColorToString(DrawClr));
		}
	} while (1);
}

color ChangeDrwClrAction::GetColor(Point p)
{
	Output* pOut = pManager->GetOutput();
	int test = p.x / pOut->getUIMenuItemWidth();
	switch (test)
	{
	case CLR_BLACK:
		return BLACK;
	case CLR_WHITE:
		return WHITE;
	case CLR_RED:
		return RED;
	case CLR_GREEN:
		return GREEN;
	case CLR_BLUE:
		return BLUE;
	default:
		return pOut->getBkGrndColor(); //To eleminate the warning
	}
}

void ChangeDrwClrAction:: ReadActionParameters()
{}

void ChangeDrwClrAction::ChngSelectedFigsDrwClr(color c)
{
	for (int i = 0; i < pManager->GetSelectedCount(); i++)
	{
		pManager->getSelectedFig(i)->ChngDrawClr(c);
		if(pManager->getSelectedFig(i)->getFigureType()==LINE)
			pManager->getSelectedFig(i)->ChngFillClr(c);
	}
}


#include "ChangeFillColorAction.h"
#include "..\ApplicationManager.h"



ChangeFillColorAction::ChangeFillColorAction(ApplicationManager * pApp):Action(pApp)
{
	pManager->GetOutput()->CreateColorToolBar();
}


ChangeFillColorAction::~ChangeFillColorAction()
{
	pManager->GetOutput()->CreateDrawToolBar();
}

void ChangeFillColorAction::Execute()
{
	pManager->GetOutput()->PrintMessage("Choose the Fill color");
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
		color FillClr = GetColor(clickedPoint);
		if (pManager->ThereIsSelectedFigs())
		{
			ChngSelectedFigsFillClr(FillClr);
			pManager->UpdateInterface();
			pManager->GetOutput()->PrintMessage("Fill color of selected figures is Changed to "
			+pManager->GetOutput()->ColorToString(FillClr));
		}
		else
		{
			pManager->GetOutput()->setCrntFillColor(FillClr);
			pManager->GetOutput()->PrintMessage("Fill color is Changed to "
			+pManager->GetOutput()->ColorToString(FillClr));
		}
	} while (1);
}

color ChangeFillColorAction::GetColor(Point p)
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

void ChangeFillColorAction:: ReadActionParameters()
{} 

void ChangeFillColorAction:: ChngSelectedFigsFillClr(color c)
{
	for (int i = 0; i < pManager->GetSelectedCount(); i++)
	{
		if (!pManager->getSelectedFig(i)->IsFilled())
		{
			pManager->getSelectedFig(i)->setFilled(true);
		}
		if (pManager->getSelectedFig(i)->getFigureType() != LINE)
			pManager->getSelectedFig(i)->ChngFillClr(c);
	}
}


#include "SelectAction.h"

#include "..\ApplicationManager.h"

SelectAction::SelectAction(ApplicationManager *pApp):Action(pApp)
{
	pManager->GetOutput()->PrintMessage("Select Figures");
}
SelectAction::~SelectAction()
{
}
 void SelectAction:: ReadActionParameters()
{
}
 void SelectAction:: Execute()
{
	Output* pOut = pManager->GetOutput();
		Input* pIn = pManager->GetInput();
	{
	if (pManager->getfigcount() == 0)
	{
		Output* pOut = pManager->GetOutput();
		Input* pIn = pManager->GetInput();
		pOut->PrintMessage("There is no figures to select");
		return;
	}
	CFigure*F;
	Point clickedPoint;
	do {
		pIn->GetPointClicked(clickedPoint.x, clickedPoint.y);
		if (clickedPoint.y <= UI.ToolBarHeight&&ITM_SELECT == (clickedPoint.x / UI.MenuItemWidth))
			break;                            //End selection if user pressed on SELECT icon
		F = pManager->GetFigure(clickedPoint);
		if (!F)
		{
			pOut->PrintMessage("Press on a figure to select!");
			continue;                         //when user press on drawing area or status bar
		}
		if (F->Select(clickedPoint))
		{
			if (F->IsSelected())
			{
				F->SetSelected(false);
				pOut->PrintMessage(pOut->intToType(F->getFigureType())+" ID:"+to_string(F->GetID())
					+"-->has been unselected");     // tell the user he unselected a figure
				for (int i = 0; i < pManager->GetSelectedCount(); i++)
				{
					if (pManager->getSelectedFig(i) == F)
					{
						if (pManager->GetSelectedCount() == (i + 1))
						{
							pManager->SetSelectedFig(NULL,i);
							break;
						}
						else
						{
							pManager->SetSelectedFig(pManager->getSelectedFig(pManager->GetSelectedCount()-1),i);
							pManager->SetSelectedFig(NULL,pManager->GetSelectedCount()-1);
							
							break;
						}
					}
				}
				pManager->setSelectedCount(-1);
			}
			else
			{
				F->SetSelected(true);
				F->PrintInfo(pOut);                      // print info of selected fig
				pManager->SetSelectedFig(F,pManager->GetSelectedCount());
				
				pManager->setSelectedCount(1);
			}
			pManager->UpdateInterface();
		}
	} while (1);
	if(pManager->GetSelectedCount()>1)
	        pOut->PrintMessage(to_string(pManager->GetSelectedCount())+" Figures have been selected-->End Selection");
	else
			pOut->PrintMessage(to_string(pManager->GetSelectedCount())+" Figure has been selected-->End Selection");
    }
	
}



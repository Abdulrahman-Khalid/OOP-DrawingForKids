#include "CUTACTION.h"


CUTACTION::CUTACTION(ApplicationManager *pApp):Action(pApp)
{
}

void CUTACTION:: ReadActionParameters()	
{  
}
				
void CUTACTION:: Execute()
{   Output* pOut = pManager->GetOutput();
	if(!(pManager->ThereIsSelectedFigs()))
	{
		pOut->PrintMessage("No select Fig");
			return ;
	}
	pManager->ResetClipboard();
	for (int i=0;i<200;i++)
		if(pManager->getSelectedFig(i)!=NULL)
			pManager->AddToClipboard(pManager->getSelectedFig(i)->copyFig(),i);
	
	pManager->Delete();
	pManager->ResetSelectedFigs();
	pManager->UpdateInterface();
}

CUTACTION::~CUTACTION()
{
}

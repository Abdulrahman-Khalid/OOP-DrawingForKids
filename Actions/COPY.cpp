#include "COPY.h"


COPY::COPY(ApplicationManager * pApp):Action(pApp)
{
}

void COPY:: ReadActionParameters()	
{
	
}
				
void COPY:: Execute()
{  Output* pOut = pManager->GetOutput();
	if(!(pManager->ThereIsSelectedFigs())){
		pOut->PrintMessage("No select Fig");
		return ;}
	pManager->ResetClipboard();
	for (int i=0;i<200;i++)
	{   if(pManager->getSelectedFig(i)!=NULL){
		pManager->AddToClipboard(pManager->getSelectedFig(i)->copyFig(),i);
		pManager->getSelectedFig(i)->SetSelected(false);}
	}
	pManager->ResetSelectedFigs();
	pManager->UpdateInterface();
}

COPY::~COPY(void)
{
}

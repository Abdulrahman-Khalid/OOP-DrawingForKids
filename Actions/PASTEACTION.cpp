#include "PASTEACTION.h"

PASTEACTION::	PASTEACTION(ApplicationManager *pApp):Action(pApp)

{
}

void PASTEACTION:: ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("choose a Point");
	
	//Read Centre and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);
}
				
void PASTEACTION:: Execute() 
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	
	if((pManager->checkClipboard())){
	pOut->PrintMessage("No Copy or Cut Fig to Paste it ");
	return ;}
	Point ref= pManager->GetClipboard(0)->getPoint();// point from the frist shape (my reference)
	Point new_position;
	for (int i=0;i<200;i++)
	{	if(pManager->GetClipboard(i)!=NULL)
		{
		CFigure*temp =(pManager->GetClipboard(i)->copyFig());
		new_position.x=P1.x+(pManager->GetClipboard(i)->getPoint().x - ref.x);
		new_position.y=P1.y+(pManager->GetClipboard(i)->getPoint().y - ref.y);
		if(temp->move(new_position)->CheckCoordinates())
			{
				pManager->AddFigure(temp);
				pManager->UpdateInterface();
				pOut->PrintMessage("Figures are Pasted ");
			}
		else 
			pOut->PrintMessage("Invalid position ");
		}	
	}

}
				
PASTEACTION::~PASTEACTION()
{
}

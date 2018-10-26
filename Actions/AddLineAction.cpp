#include "AddLineAction.h"
#include "..\Figures\CLine.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"


AddLineAction::AddLineAction(ApplicationManager * pApp):Action(pApp)
{}

AddLineAction::~AddLineAction()
{
}

void AddLineAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Line: Click the first point");
	
	//Read 1st point and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);

	pOut->PrintMessage("New Line: Click the second point");

	//Read 2nd point and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);

	LineGfxInfo.isFilled = true;
	//get drawing, filling colors and pen width from the interface
	LineGfxInfo.DrawClr = pOut->getCrntDrawColor();
	LineGfxInfo.FillClr = LineGfxInfo.DrawClr;
	pOut->ClearStatusBar();
}

//Execute the action
void AddLineAction::Execute() 
{
	//This action needs to read some parameters first
	ReadActionParameters();
	
	//Create a Line with the parameters read from the user
	Line *L=new Line(P1, P2, LineGfxInfo);
	if (L->CheckCoordinates())     //Add the Line to the list  figures
	{
		pManager->AddFigure(L);
		pManager->GetOutput()->PrintMessage("A new line has been added ");
	}
	else
	{
		PlaySound(TEXT("wrong.wav"), NULL, SND_ASYNC);
		pManager->GetOutput()->PrintMessage("Invalid position,Cannot draw this figure");
		delete L;
	}
	
}




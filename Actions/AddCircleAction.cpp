#include "AddCircleAction.h"
#include "..\Figures\CCircle.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
 

 AddCircleAction::AddCircleAction(ApplicationManager * pApp):Action(pApp)
{}

 AddCircleAction::~AddCircleAction()
 {
 }

void AddCircleAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Circle: Click at Centre");
	
	//Read Centre and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);

	pOut->PrintMessage("New Circle: Click at a point On the frame");

	//Read a point one the frame and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);

	if(pOut->getCrntFillColor()==pOut->getBkGrndColor())
		CircGfxInfo.isFilled = false;	//default is not filled
	else
	{
		CircGfxInfo.isFilled = true;
	}
	//get drawing, filling colors and pen width from the interface
	CircGfxInfo.DrawClr = pOut->getCrntDrawColor();
	CircGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

//Execute the action
void AddCircleAction::Execute() 
{
	//This action needs to read some parameters first
	ReadActionParameters();
	
	//Create a Circle with the parameters read from the user
	CCircle *C=new CCircle(P1, P2, CircGfxInfo);
	if (C->CheckCoordinates())
	{
		pManager->AddFigure(C);
		pManager->GetOutput()->PrintMessage("A new circle has been added ");
	}
	else
	{
		PlaySound(TEXT("wrong.wav"), NULL, SND_ASYNC);
		pManager->GetOutput()->PrintMessage("Invalid position,Cannot draw this figure");
		delete C;
	}
}



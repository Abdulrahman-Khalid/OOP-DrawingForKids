#include "AddTriangleAction.h"

#include "..\Figures\CTriangle.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"


AddTriangleAction::AddTriangleAction(ApplicationManager * pApp):Action(pApp)
{}

AddTriangleAction::~AddTriangleAction()
{
}

void AddTriangleAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Triangle: Click the first corner");
	
	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);

	pOut->PrintMessage("New Triangle: Click the second corner");

	//Read 2nd corner and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);

	pOut->PrintMessage("New Triangle: Click the third corner");

	//Read 3nd corner and store in point P3
	pIn->GetPointClicked(P3.x, P3.y);

	if(pOut->getCrntFillColor()==pOut->getBkGrndColor())
		TriGfxInfo.isFilled = false;	//default is not filled
	else
		TriGfxInfo.isFilled = true;
	//get drawing, filling colors and pen width from the interface
	TriGfxInfo.DrawClr = pOut->getCrntDrawColor();
	TriGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

//Execute the action
void AddTriangleAction::Execute() 
{
	ReadActionParameters();
	
	CTriangle *T=new CTriangle(P1, P2,P3, TriGfxInfo);
	if (T->CheckCoordinates())
	{
		pManager->AddFigure(T);
		pManager->GetOutput()->PrintMessage("A new triangle has been added ");
	}
	else
	{
		PlaySound(TEXT("wrong.wav"), NULL, SND_ASYNC);
		pManager->GetOutput()->PrintMessage("Invalid position,Cannot draw this figure");
		delete T;
	}
}

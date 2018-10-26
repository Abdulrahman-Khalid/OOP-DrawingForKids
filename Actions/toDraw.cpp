#include "toDraw.h"
#include "../ApplicationManager.h"


toDraw::toDraw( ApplicationManager * pApp) : Action(pApp)
{

}

void toDraw::ReadActionParameters()
{

}

void toDraw::Execute()
{
	pManager->SwitchToDrawMode();
	pManager->GetOutput()->PrintMessage("Switch to Draw Mode");
	pManager->GetOutput()->CreateDrawToolBar();//simply draw tool bar again
}

toDraw::~toDraw()
{
}

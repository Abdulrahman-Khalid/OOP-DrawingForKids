#include "RandomPlayColor.h"
#include "..\ApplicationManager.h"

RandomPlayColor::RandomPlayColor(ApplicationManager * pApp):Action(pApp)
{
}


RandomPlayColor::~RandomPlayColor()
{
	pManager->UnHide_HiddenFigures(); //This function unhide hidden figures after deleting the object 
}

void RandomPlayColor::ReadActionParameters()
{
	CFigure* RandomFigure;
	RandomFigure = pManager->getRandomFigure();
	if (RandomFigure->IsFilled()) //Ask if Figure is filled
	{
		RandomColor = RandomFigure->getFillClr(); //RandomColor is the fill color of the random figure
	}
	else
	{//RandomColor is UIBkGrndColor if the Randomindex is for a nonfilled figure
		RandomColor = pManager->GetOutput()->getBkGrndColor(); 
	}
}
void RandomPlayColor::Execute()
{
	ReadActionParameters();
	pManager->GetOutput()->PrintMessage("You are playing Pick & Hide By Figure Fill Color");
	string msg;
	msg = "Pick all " + pManager->GetOutput()->ColorToString(RandomColor) + " figures";
	pManager->CountPlayByColor(RandomColor); // Count the number of figures have the same random type
	pManager->GetOutput()->PrintMessageOnToolBar(msg); 

	//Hide the figures that have the same random color and random type, then return score
	float Score = pManager->HideFiguresByColor(RandomColor); 
	if (Score != -1)
	{
		msg = "you picked all targeted figures your Score percentage is " + to_string(Score) + "%";
		pManager->GetOutput()->PrintMessage(msg);
		pManager->GetOutput()->PrintMessageOnToolBar("BRAVOOOOOO!");
		Sleep(1000);
		pManager->GetOutput()->ClearToolBarMessage();
	}
}
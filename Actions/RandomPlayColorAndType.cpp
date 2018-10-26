#include "RandomPlayColorAndType.h"
#include "../ApplicationManager.h"


RandomPlayColorAndType::RandomPlayColorAndType(ApplicationManager*pApp):Action(pApp)
{
}


RandomPlayColorAndType::~RandomPlayColorAndType()
{
	pManager->UnHide_HiddenFigures(); //This function unhide hidden figures after deleting the object 
}

void RandomPlayColorAndType::ReadActionParameters()
{
	CFigure* RandomFigure;
	RandomFigure = pManager->getRandomFigure();
	if (RandomFigure->IsFilled()) //Ask if Figure is filled
	{
		RandomColor = RandomFigure->getFillClr(); //RandomColor is the fill color of the random figure
	}
	else
		RandomColor = pManager->GetOutput()->getBkGrndColor(); //RandomColor is UIBkGrndColor if the Randomindex is for a nonfilled figure
	RandomType = RandomFigure->getFigureType(); //RandomType is the type of the random figure
}

void RandomPlayColorAndType::Execute()
{
	ReadActionParameters();
	pManager->GetOutput()->PrintMessage("You are playing Pick & Hide By Figure Type and Fill Color");
	string msg;
	msg = "Pick all " + pManager->GetOutput()->ColorToString(RandomColor) + " " +
		pManager->GetOutput()->intToType(RandomType) + " figures";
	//Count the number of figures have the same random color and random type 
	pManager->CountPlayByColorAndType(RandomColor,RandomType); 
	pManager->GetOutput()->PrintMessageOnToolBar(msg);
	//Hide the figures that have the same random color and random type, then return score
	float Score = pManager->HideFiguresByColorAndType(RandomColor, RandomType);
	if (Score != -1)
	{
		msg = "you picked all targeted figures your Score percentage is " + to_string(Score) + "%";
		pManager->GetOutput()->PrintMessage(msg);
		pManager->GetOutput()->PrintMessageOnToolBar("BRAVOOOOOO!");
		Sleep(1000);
		pManager->GetOutput()->ClearToolBarMessage();
	}
}

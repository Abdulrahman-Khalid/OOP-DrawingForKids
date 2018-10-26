#include "RandomPlayType.h"
#include "../ApplicationManager.h"

RandomPlayType::RandomPlayType(ApplicationManager * pApp):Action(pApp)
{
}


RandomPlayType::~RandomPlayType()
{
	pManager->UnHide_HiddenFigures(); //This function unhide hidden figures after deleting the object 
}

void RandomPlayType::ReadActionParameters()
{
	RandomType = pManager->getRandomFigure()->getFigureType(); //RandomType is the type of the random figure
}

void RandomPlayType::Execute()
{
	ReadActionParameters();
	pManager->GetOutput()->PrintMessage("You are playing Pick & Hide By Figure Type");
	string msg;
	msg = "Pick all " + pManager->GetOutput()->intToType(RandomType) + " figures";
	pManager->CountPlayByType(RandomType); //Count the number of figures have the same random type 
	pManager->GetOutput()->PrintMessageOnToolBar(msg);

	//Hide the figures that have the same random type, then return score
	float Score = pManager->HideFiguresByType(RandomType); 
	if (Score != -1)
	{
		msg = "you picked all targeted figures your Score percentage is " + to_string(Score) + "%";
		pManager->GetOutput()->PrintMessage(msg);
		pManager->GetOutput()->PrintMessageOnToolBar("BRAVOOOOOO!");
		Sleep(1000);
		pManager->GetOutput()->ClearToolBarMessage();
	}
}

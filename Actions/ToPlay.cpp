#include "toPlay.h"
#include "../ApplicationManager.h"

ToPlay::ToPlay(ApplicationManager * pApp) : Action(pApp)
{

}

ToPlay::~ToPlay()
{

}
void ToPlay::ReadActionParameters()
{

}

void ToPlay::Execute()
{
	if (pManager->SwitchToPlayMode())
	{
		pManager->GetOutput()->PrintMessage("Switch to Play Mode");
		pManager->GetOutput()->CreatePlayToolBar();
	}
	else
	{
		pManager->GetOutput()->PrintMessage("Can't switch to Play Mode");
		PlaySound(TEXT("wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
}


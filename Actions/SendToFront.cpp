#include "SendToFront.h"
#include "../ApplicationManager.h"


SendToFront::SendToFront(ApplicationManager*pApp) :Action(pApp)
{
}


SendToFront::~SendToFront()
{
}

void SendToFront::ReadActionParameters()
{
}

void SendToFront::Execute()
{
	if (pManager->ThereIsSelectedFigs())
	{
		pManager->SendSelectedFigsToFront();
		pManager->GetOutput()->PrintMessage("Sending the selected figures to front.");
	}
	else
	{
		pManager->GetOutput()->PrintMessage("No selected figures to send them to front");
		PlaySound(TEXT("wrong.wav"), NULL, SND_ASYNC);
	}
}

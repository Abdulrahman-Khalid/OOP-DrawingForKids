#include "SendToBack.h"
#include "../ApplicationManager.h"


SendToBack::SendToBack(ApplicationManager*pApp) :Action(pApp)
{
}


SendToBack::~SendToBack()
{
}

void SendToBack::ReadActionParameters()
{
}

void SendToBack::Execute()
{
	if (pManager->ThereIsSelectedFigs())
	{
		pManager->SendSelectedFigsToBack();
		pManager->GetOutput()->PrintMessage("Sending the selected figures to back.");
	}
	else
	{
		pManager->GetOutput()->PrintMessage("No selected figures to send them to back");
		PlaySound(TEXT("wrong.wav"), NULL, SND_ASYNC);
	}
}

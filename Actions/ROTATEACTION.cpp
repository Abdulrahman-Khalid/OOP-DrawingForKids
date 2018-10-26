#include "ROTATEACTION.h"
#include "..\ApplicationManager.h"

ROTATEACTION::ROTATEACTION(ApplicationManager* pApp):Action(pApp)
{
}


ROTATEACTION::~ROTATEACTION()
{
	
}

void ROTATEACTION::ReadActionParameters()
{

}

void ROTATEACTION::Execute()
{
	if (pManager->ThereIsSelectedFigs()) 
	{
		pManager->GetOutput()->CreateRotateToolBar();
		Point p;
		do {
			pManager->GetInput()->GetPointClicked(p.x, p.y);
			if (p.y > pManager->GetOutput()->getUIToolBarHeight())//Click on inplay toolbar
			{
				continue;
			}
			if (Rotate_BACK == (p.x / pManager->GetOutput()->getUIMenuItemWidth()))
			{
				pManager->GetOutput()->CreateDrawToolBar();
				return;
			}
			double angle = 0;
			int successCount = 0;
			string msg;
			if (Rotate_90 == (p.x / pManager->GetOutput()->getUIMenuItemWidth()))
			{
				angle = 90;
				msg = "90 degree rotation";
			}
			if (Rotate_180 == (p.x / pManager->GetOutput()->getUIMenuItemWidth()))
			{
				angle = 180;
				msg = "180 degree rotation";
			}
			if (Rotate_270 == (p.x / pManager->GetOutput()->getUIMenuItemWidth()))
			{
				angle = 270;
				msg = "270 degree rotation";
			}
			for (int i = 0; i < pManager->GetSelectedCount(); i++)
			{
				if (pManager->getSelectedFig(i)->Rotate(angle))
				{
					successCount++;
				}
			}
			int failedCount = pManager->GetSelectedCount() - successCount;
			pManager->UpdateInterface();
			double rate = ((double)(successCount) / (failedCount + successCount)) * 100;
			msg += ", Successfully rotated figures :" + to_string(successCount) + ", Failed to rotate figures :"
				+ to_string(failedCount) + ", Rotatation success rate = " + to_string(rate) + "%";
			pManager->GetOutput()->PrintMessage(msg);
		} while (1);
	}
	else
	{
		pManager->GetOutput()->PrintMessage("There is no selected figures to rotate");
		PlaySound(TEXT("wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
}

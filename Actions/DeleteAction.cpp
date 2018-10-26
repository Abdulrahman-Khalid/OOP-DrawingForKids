#include "DeleteAction.h"
#include "..\ApplicationManager.h"



DeleteAction::DeleteAction(ApplicationManager*pApp):Action(pApp)
{
}

 void DeleteAction:: ReadActionParameters()
 {
 }


 void DeleteAction:: Execute()
 {  
	 Output* pOut = pManager->GetOutput();
	 if (!pManager->ThereIsSelectedFigs())
	{
		pOut->PrintMessage("There is no figure selected to delete");  //No Selected Figs to delete!
		PlaySound(TEXT("wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
	 else                                                             //there are selected figs
	 {
		 pManager->Delete();
		 pOut->PrintMessage("selected figures were deleted!");
		 pManager->ResetSelectedFigs();

	 }

 }

DeleteAction::~DeleteAction()
{
}

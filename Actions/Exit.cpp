#include "Exit.h"
#include "../ApplicationManager.h"

Exit::Exit(ApplicationManager* pApp) :Action(pApp)
{
}


Exit::~Exit()
{
}

void Exit::ReadActionParameters()
{

}

void Exit::Execute()
{//asks if the kid wants to save the file before exiting . 
	pManager->GetOutput()->PrintMessage("If you want to save your last changes type (yes),OtherWise the game will exit without saving ");
	string str = pManager->GetInput()->GetSrting(pManager->GetOutput());
	if (str == "yes" || str == "YES" || str == "Yes"|| str== "yEs" ||str=="yeS"||str=="YEs"||str =="yES" ||str=="YeS")
	{
		pManager->ExecuteAction(SAVE);
	}
}

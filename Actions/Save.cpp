#include "Save.h"
#include "AddRectAction.h"
#include "..\Figures\CRectangle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include <fstream>

Save::Save(ApplicationManager * pApp) :Action(pApp)
{


}

void Save::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("enter the file name");

	fileName = pIn->GetSrting(pOut);


}
void Save::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	OutFile.open(fileName, ios::out);
	OutFile << pOut->ColorToString(pOut->getCrntDrawColor()) << " " << pOut->ColorToString(pOut->getCrntFillColor()) << endl 
		<< pManager->getfigcount() << endl;                      //taking crnt draw colour and filling colour and Figure count
	pManager->Saveall(OutFile);//Calling function Saveall in appmanager *that doesn't have any functionality it just calls save for every figure*
	pOut->PrintMessage("the file is saved");
	OutFile.close();


}
Save::~Save()
{
}



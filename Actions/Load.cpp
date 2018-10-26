#include "Load.h"
#include "AddRectAction.h"
#include "..\Figures\CRectangle.h"
#include "..\Figures\CTriangle.h"
#include "..\Figures\CCircle.h"
#include "..\Figures\CLine.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include <fstream>
Load::Load(ApplicationManager * pApp) :Action(pApp)
{


}
Load:: ~Load() {

}
void Load::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("enter the file name");

	fileName = pIn->GetSrting(pOut);
	InFile.open(fileName, ios::in);
	while (!(InFile.is_open()))//check if the file opens or not if not it keeps asking for a valid name.
	{
		pOut->PrintMessage("please enter valid file name");
		fileName = pIn->GetSrting(pOut);
		InFile.open(fileName, ios::in);
	}
		

}
void Load::Execute()
{

	char crntdraw[50];
	char crntfill[50];
	int fcnt = 0;
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	pManager->clearfiglist();
	InFile >> crntdraw;
	InFile >> crntfill;
	InFile >> fcnt;
	pOut->setCrntDrawColor(pOut->StringToColour(crntdraw));//setting crnt draw colour
	pOut->setCrntFillColor(pOut->StringToColour(crntfill));//setting crnt fill colour
	pManager->setfigcount(0);// doesn't set figures count :D
	CFigure* p;
	string filetype;
	while (!InFile.eof())//as we don't reach end of file continue working
	{
		filetype = "mfesh";
		p = NULL;
		InFile >> filetype;//reads first word in line and check what is the shape and allocate it
		if (filetype == "RECTANGLE")
		{
			p = new CRectangle;
		}
		else if (filetype == "TRIANGLE")
		{
			p = new CTriangle;
		}
		else if (filetype == "CIRCLE")
		{
			p = new CCircle;
		}
		else if (filetype == "LINE")
		{
			p = new Line;
		}
		if (p != NULL) {
			p->Load(InFile,pOut);//load the shape by the (virtual) load to take all its specs
			pManager->AddFigure(p);//add the figure to figlist 
		}
	}
	InFile.close();
	pManager->UpdateInterface();//draw all the figures
	pOut->PrintMessage("the file is Loaded");

}
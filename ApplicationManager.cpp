#include "ApplicationManager.h"
#include "ActionHeaders.h"
//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	SelectedCount = 0;
	FigCount = 0;
	playTargetCount = 0;
	WrongCount = 0;
	CorrectCount = 0;
	pAct = NULL;
	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i<MaxFigCount; i++)
		FigList[i] = NULL;
	for (int i = 0; i<MaxFigCount; i++)
		SelectedFigs[i] = NULL;
	for (int i = 0; i<MaxFigCount; i++)
		Clipboard[i] = NULL;
}
//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType)
{
	pAct = NULL;

	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case DRAW_RECT:
		pAct = new AddRectAction(this);
		break;
	case DRAW_LINE:
		pAct = new AddLineAction(this);
		break;
	case DRAW_CIRC:
		pAct = new AddCircleAction(this);
		break;
	case DRAW_TRI:
		pAct = new AddTriangleAction(this);
		break;
	case SELECT:
		pAct = new SelectAction(this);
		break;
	case CPY:
		pAct=new COPY (this);
		break;

	case CUT:
		pAct=new CUTACTION(this);	
		break;
	
	case PASTE: 
		pAct=new PASTEACTION(this);
		break;
		
	case DEL:
		pAct = new DeleteAction(this);
		break;
	case CHNG_FILL_CLR:
		pAct = new ChangeFillColorAction(this);
		break;
	case CHNG_DRAW_CLR:
		pAct = new ChangeDrwClrAction(this);
		break;
	case ROTATE:
		pAct = new ROTATEACTION(this);
		break;
	case SENDTOFRONT:
		pAct = new SendToFront(this);
		break;
	case SENDTOBACK:
		pAct = new SendToBack(this);
		break;
	case TO_PLAY:
		pAct = new ToPlay(this);
		break;
	case PLAY_COLOR:
		pAct = new RandomPlayColor(this);
		break;
	case PLAY_TYPE:
		pAct = new RandomPlayType(this);
		break;
	case PLAY_COLOR_TYPE:
		pAct = new RandomPlayColorAndType(this);
		break;
	case TO_DRAW:
		pAct = new toDraw(this);
		break;
	case SAVE:
		pAct = new Save(this);
		break;
	case LOAD:
		pAct = new Load (this);
		break;
	case EXIT:
		pAct = new Exit(this);
		break;

	case STATUS:	//a click on the status bar ==> no action
		return;
	case PLAYING_AREA:
		pOut->PrintMessage("Choose a game to play");
		break;		
	case DRAWING_AREA:
		break;
	}

	//Execute the created action
	if (pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if (FigCount < MaxFigCount)
	{
		FigList[FigCount++] = pFig;
	    FigList[FigCount-1]->SetID(FigCount-1);
	}
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(Point p) const
{
	for (int i = FigCount - 1; i >= 0; i--) //From last figure in the figure list
	{
		if (!FigList[i]->IsHidden() && FigList[i]->Select(p))
		{
			return FigList[i];
		}
	}
	return NULL;
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();
	for (int i = 0; i < FigCount; i++)
	{
		if (!FigList[i]->IsHidden())
			FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
	}
}
  //=====================================================================//
 //							Play Mode Functions							//
//=====================================================================//
bool ApplicationManager::NewGameOrBackToDraw(Point ClickedPoint)
{
	if (ClickedPoint.y <= pOut->getUIToolBarHeight() && (ClickedPoint.x / pOut->getUIMenuItemWidth())<PLAY_ITM_COUNT)
		//Click on play mode toolbar
	{
		if (pAct != NULL)
			delete pAct;
		UpdateInterface(); //To show the hidden figures
		switch (ClickedPoint.x / UI.MenuItemWidth)
		{
		case ITM_COLOR: //Click on play by color 
			pOut->PrintMessage("You didn't finish your game, Starting new game ... ");
			Sleep(500); //To have time to show this message
			ExecuteAction(PLAY_COLOR); //Starting new game
			break;
		case ITM_TYPE: //Click on play by type
			pOut->PrintMessage("You didn't finish your game, Starting new game ... ");
			Sleep(500); //To have time to show this message
			ExecuteAction(PLAY_TYPE); //Starting new game
			break;
		case ITM_COLOR_TYPE: //Click on play by color 
			pOut->PrintMessage("You didn't finish your game, Starting new game ... ");
			Sleep(500); //To have time to show this message
			ExecuteAction(PLAY_COLOR_TYPE); //Starting new game
			break;
		case ITM_DRAW:
			pOut->PrintMessage("You didn't finish your game ");
			Sleep(500); //To have time to show this message
			pOut->ClearToolBarMessage();
			ExecuteAction(TO_DRAW); //Switch to play mode
			break;
		}
		return true;
	}
	return false;
}
////////////////////////////////////////////////////////////////////////////////////
float ApplicationManager::HideFiguresByColor(color RandomColor)
{
	Point ClickedPoint;
	CFigure* ClickedFigure;
	string msg;
	CorrectCount = 0;
	WrongCount = 0;
	do {
		pIn->GetPointClicked(ClickedPoint.x, ClickedPoint.y);
		if (NewGameOrBackToDraw(ClickedPoint))
			return -1;
		ClickedFigure = GetFigure(ClickedPoint);
		if (!ClickedFigure)
		{
			continue;
		}
		ClickedFigure->setHidden(true);
		if (RandomColor == pOut->getBkGrndColor()) //non-filled
		{
			if (!(ClickedFigure->IsFilled())) //check if clicked figure is not filled
			{
				msg = "Correct Click, ";
				CorrectCount++;
			}
			else
			{
				msg = "Wrong click, ";
				WrongCount++;
				PlaySound(TEXT("wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
		}
		else //color is filled
		{
			if (ClickedFigure->IsFilled() && (RandomColor == ClickedFigure->getFillClr())) 
			{ //check if clicked figure is filled and its color is the color have to pick
				msg = "Correct click, ";
				CorrectCount++;
			}
			else
			{
				msg = "Wrong click, ";
				WrongCount++;
				PlaySound(TEXT("wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
		}
		msg += "Your correct clicks are " + to_string(CorrectCount) + " Clicks and your Wrong clicks are " 
			+ to_string(WrongCount) + " Clicks";
		pOut->PrintMessage(msg);
		UpdateInterface();
	} while (CorrectCount < playTargetCount);
	return (CorrectCount / (((float)CorrectCount + WrongCount)) * 100);
}
////////////////////////////////////////////////////////////////////////////////////
float ApplicationManager::HideFiguresByType(int RandomType)
{
	Point ClickedPoint;
	CFigure* ClickedFigure;
	string msg;
	CorrectCount = 0;
	WrongCount = 0;
	do {
		pIn->GetPointClicked(ClickedPoint.x, ClickedPoint.y);
		if (NewGameOrBackToDraw(ClickedPoint))
			return -1;
		ClickedFigure = GetFigure(ClickedPoint);
		if (!ClickedFigure)
		{
			continue;
		}
		ClickedFigure->setHidden(true);
		if (RandomType == ClickedFigure->getFigureType())
		{
			msg = "Correct click, ";
			CorrectCount++;
		}
		else
		{
			msg = "Wrong click, ";
			WrongCount++;
			PlaySound(TEXT("wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		msg += "Your correct clicks are " + to_string(CorrectCount) + " Clicks and your Wrong clicks are " + to_string(WrongCount) + " Clicks";
		pOut->PrintMessage(msg);
		UpdateInterface();
	} while (CorrectCount < playTargetCount);
	return (CorrectCount / (((float)CorrectCount + WrongCount)) * 100);
}
////////////////////////////////////////////////////////////////////////////////////
float ApplicationManager::HideFiguresByColorAndType(color RandomColor, int RandomType)
{
	Point ClickedPoint;
	CFigure* ClickedFigure;
	string msg;
	CorrectCount = 0;
	WrongCount = 0;
	do {
		pIn->GetPointClicked(ClickedPoint.x, ClickedPoint.y);
		if (NewGameOrBackToDraw(ClickedPoint))
			return -1;
		ClickedFigure = GetFigure(ClickedPoint);
		if (!ClickedFigure) //ClickedPoint isnot on a figure
		{
			continue; //skip this iteration to take another point
		}
		ClickedFigure->setHidden(true);
		if (RandomColor == pOut->getBkGrndColor())
		{
			if (!(ClickedFigure->IsFilled()) && (RandomType == ClickedFigure->getFigureType()))
			{
				msg = "Correct Click, ";
				CorrectCount++;
			}
			else
			{
				msg = "Wrong click, ";
				WrongCount++;
				PlaySound(TEXT("wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
		}
		else
		{
			if (ClickedFigure->IsFilled() &&
				(RandomColor == ClickedFigure->getFillClr()) &&
				((RandomType == ClickedFigure->getFigureType())))
			{
				msg = "Correct click, ";
				CorrectCount++;
			}
			else
			{
				msg = "Wrong click, ";
				WrongCount++;
				PlaySound(TEXT("wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
		}
		msg += "Your correct clicks are " + to_string(CorrectCount) + " Clicks and your Wrong clicks are " 
			+ to_string(WrongCount) + " Clicks";
		pOut->PrintMessage(msg);
		UpdateInterface();
	} while (CorrectCount < playTargetCount);
	return (CorrectCount / (((float)CorrectCount + WrongCount)) * 100);
}
////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::CountPlayByColor(color c)
{
	playTargetCount = 0; //to make sure it is zero
	if (c == pOut->getBkGrndColor()) //if the random figure is non - filled
	{
		for (int i = 0; i < FigCount; i++)
		{        //if the figure is non-filled as the random figure, increase the play target count by 1
			if (!FigList[i]->IsFilled()) 
				playTargetCount++;
		}
		return;
	}
	for (int j = 0; j < FigCount; j++)
	{ //if the figure has the same type as the random figure, increase the play target count by 1
		if (FigList[j]->IsFilled() && c == FigList[j]->getFillClr()) 
			playTargetCount++;
	}
}
////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::CountPlayByType(int num)
{
	playTargetCount = 0; //to make sure it is zero
	for (int i = 0; i < FigCount; i++)
	{ //if the figure is the same color as the random figure, increase the play target count by 1
		if (num == FigList[i]->getFigureType())  
		{
			playTargetCount++;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::CountPlayByColorAndType(color c, int num)
{
	playTargetCount = 0; //to make sure it is zero
	if (c == pOut->getBkGrndColor())
	{//if the random figure is non - filled
		for (int i = 0; i < FigCount; i++)
		{//if the figure is non-filled as the random figure and has the same type as the random figure,
			//increase the play target count by 1
			if (!FigList[i]->IsFilled() && (num == FigList[i]->getFigureType()))
				playTargetCount++;
		}
		return;
	}
	for (int j = 0; j < FigCount; j++)
	{ //if the figure is the same color&type as the random figure, increase the play target count by 1
		if ((FigList[j]->IsFilled()) && (c == FigList[j]->getFillClr()) && (num == FigList[j]->getFigureType()))
			playTargetCount++;
	}
}
////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::UnHide_HiddenFigures()
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsHidden()) //if figure is hidden unhide it 
		{
			FigList[i]->setHidden(false); 
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////
CFigure * ApplicationManager::getRandomFigure()const
{
	int i = rand()%FigCount; //RandomIndex from 0 to FigCount-1 (existing figure)
	return FigList[i];
}
////////////////////////////////////////////////////////////////////////////////////
bool ApplicationManager::SwitchToPlayMode()
{
	if (FigCount)
	{
		for (int i = 0; i < FigCount; i++)
		{
			if (FigList[i]->IsSelected())
			{
				FigList[i]->SetSelected(false);
			}
		}
		return true;
	}
	return false;
}
////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::SwitchToDrawMode()
{
	for (int i = 0; i < SelectedCount; i++)
	{
		SelectedFigs[i]->SetSelected(true);
	}
}

////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{
	return pIn;
}
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{
	return pOut;
}
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	clearfiglist();
	delete pIn;
	delete pOut;
	ResetClipboard();
}



 

  //=========================================================================================//
 //                                    Delete Actions                                       //
//=========================================================================================//
void ApplicationManager::Delete()
{
	for (int i=0;i<FigCount;i++)
	{
		if(FigList[i]->IsSelected())
			{
				delete FigList[i];

			    for (int k=i;k<FigCount-1;k++)
				{
				   FigList[k]=FigList[k+1];
				   FigList[k]->SetID(k);
				}

			
				FigList[FigCount-1]=NULL;
				--i;
				--FigCount;
		    }
		
	}
}



  //====================================================================================================//
 //                                      To Front/ To Back Functions                                   //
//====================================================================================================//
void ApplicationManager::SendSelectedFigsToFront()
{
	int k = 0;
	int c = 0;
	for (int i = 0; i < FigCount; i++) //Putting all unselected figures first at the start of figure list
	{
		if (!FigList[i]->IsSelected())
		{
			FigList[k] = FigList[i];
			k++;
		}
		else
		{
			SelectedFigs[c] = FigList[i];
			c++;
		}
	}
	for (int j = 0; j < SelectedCount; j++) //Then putting all selected ones at the end of figure list
	{
		FigList[k] = SelectedFigs[j];
		k++;
	}
}

void ApplicationManager::SendSelectedFigsToBack()
{
	int k = FigCount - 1;
	int c = 0;
	for (int i = FigCount - 1; i >= 0; i--) //Putting all unselected figures first at the end of figure list 
	{
		if (!FigList[i]->IsSelected())
		{
			FigList[k] = FigList[i];
			k--;
		}
		else
		{
			SelectedFigs[c] = FigList[i];
			c++;
		}
	}
	for (int j = 0; j < SelectedCount; j++) //Then putting all selected ones at the start of figure list
	{
		FigList[k] = SelectedFigs[j];
		k--;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ApplicationManager::ThereIsSelectedFigs() const
{
	return SelectedCount>0;
}
void ApplicationManager:: AddToClipboard(CFigure* pFig,int i)
{
	Clipboard[i]= pFig;
}
bool ApplicationManager::checkClipboard()
{
	return Clipboard[0]==NULL;
}
void  ApplicationManager::setfigcount(int x) {
	FigCount = x;
}
int  ApplicationManager::getfigcount() {
	return FigCount;
}
void ApplicationManager::Saveall(ofstream &OutFile)
{
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->Save(OutFile,pOut);
	}
}
void ApplicationManager::clearfiglist() {
	for (int i = 0; i < FigCount; i++)
	{
		delete FigList[i];
		FigList[i]=NULL;
	}

}

CFigure* ApplicationManager:: GetClipboard(int i)
{
	return Clipboard[i];
}
void ApplicationManager:: ResetClipboard()
{	for (int i=0;i<MaxFigCount;i++){
		if(Clipboard[i]!=NULL)
			delete Clipboard [i];
		Clipboard[i]=NULL;}
}
void ApplicationManager:: ResetSelectedFigs()
{	for (int i=0;i<SelectedCount;i++)
		SelectedFigs[i]=NULL;
    SelectedCount = 0;
}
CFigure* ApplicationManager::getSelectedFig(int i)
{
	return SelectedFigs[i];
}
void ApplicationManager::setSelectedCount(int a)
{
	if(SelectedCount+a>=0)
	if(a!=0)
		SelectedCount+=a;
	else 
		SelectedCount=0;
}

int ApplicationManager:: GetSelectedCount() const
{
	return SelectedCount;
}

void ApplicationManager:: SetSelectedFig(CFigure* fig,int y)  //used in select action
{
	SelectedFigs[y]=fig;
}



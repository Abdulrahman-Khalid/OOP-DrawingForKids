#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"
#include "GUI\input.h"
#include "GUI\output.h"
#include "Actions/Action.h"
//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200 };	//Max no of figures

private:
	int FigCount;		//Actual number of figures
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)

	CFigure* Clipboard[MaxFigCount];   //Pointer to list of the copied/cut figures
	int playTargetCount; //Counter to the winning figures in play mode
	int CorrectCount; //counter to correct clicks in play mode
	int WrongCount; //counter to wrong clicks in play mode
	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;
	Action* pAct;
	CFigure* SelectedFigs[MaxFigCount];	//Array of pointers to the selected figures
	int SelectedCount;
	//this function just for not repeating the same code in the three hide figures functions
	bool NewGameOrBackToDraw(Point ClickedPoint);
public:	
	ApplicationManager(); 
	~ApplicationManager();

	int GetSelectedCount() const;

	
	

	
	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType) ; //Creates an action and executes it
	
	// -- Figures Management Functions
	void AddFigure(CFigure* pFig);          //Adds a new figure to the FigList
	CFigure * GetFigure(Point p) const;
		
	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;
	//Redraws all the drawing window	
	float HideFiguresByColor(color RandomColor);
	float HideFiguresByType(int RandomType);
	float HideFiguresByColorAndType(color RandomColor, int RandomType);
	void CountPlayByColor(color c);
	void CountPlayByType(int num);
	void CountPlayByColorAndType(color c, int num);
	void UnHide_HiddenFigures();
	CFigure * getRandomFigure() const;
	bool SwitchToPlayMode();
	void SwitchToDrawMode();
	void SendSelectedFigsToFront(); //send selected figures to front
	void SendSelectedFigsToBack(); //send selected figures to back
	bool ThereIsSelectedFigs()const;
	void AddToClipboard(CFigure* pFig,int); 
	void ResetClipboard();//make clipboard points to NULL
	bool checkClipboard();//if clipboard points to something
	void setfigcount(int);
	void clearfiglist();
	int getfigcount();
	void Saveall(ofstream &OutputFile);//Just calls (virtual)save for every figure
	void Delete();
	CFigure*GetClipboard(int);
	CFigure* getSelectedFig(int);
	void setSelectedCount(int );
	void ResetSelectedFigs();

	void SetSelectedFig(CFigure* fig,int y);
	
	
};
#endif
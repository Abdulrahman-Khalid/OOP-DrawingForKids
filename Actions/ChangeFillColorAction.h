#pragma once
#include "Action.h"
class ChangeFillColorAction :
	public Action
{
	
public:
	ChangeFillColorAction(ApplicationManager * pApp);
	virtual ~ChangeFillColorAction();

	color GetColor(Point p);
	void ChngSelectedFigsFillClr(color c);

	virtual void ReadActionParameters();
	virtual void Execute();
};


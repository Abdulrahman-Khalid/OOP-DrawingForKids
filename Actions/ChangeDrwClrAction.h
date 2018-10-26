#pragma once
#include "Action.h"
class ChangeDrwClrAction :
	public Action
{
	
public:
	ChangeDrwClrAction(ApplicationManager*pApp);
	virtual ~ChangeDrwClrAction();

	color GetColor(Point p);
	void ChngSelectedFigsDrwClr(color c);


	virtual void ReadActionParameters();
	virtual void Execute();
};


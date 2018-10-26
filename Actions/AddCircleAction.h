#ifndef ADD_CIRCLE_ACTION_H
#define ADD_CIRCLE_ACTION_H

#include "Action.h"

class AddCircleAction :
	public Action
{
private:
	Point P1, P2;    //Circle two Points Corners
	GfxInfo CircGfxInfo;
public:
	AddCircleAction(ApplicationManager *pApp);
	virtual ~AddCircleAction();
	//Reads Circle parametersx
	virtual void ReadActionParameters();
	
	//Add Circle to the ApplicationManager
	virtual void Execute() ;
};
#endif

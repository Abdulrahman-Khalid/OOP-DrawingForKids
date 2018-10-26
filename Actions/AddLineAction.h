#ifndef ADD_LINE_ACTION_H
#define ADD_LINE_ACTION_H


#include "Action.h"

class AddLineAction : public Action
{private:
	Point P1, P2; //Line corners
	GfxInfo LineGfxInfo;
public:
	AddLineAction(ApplicationManager *pApp);
	virtual ~AddLineAction();

	//Reads Line parameters
	virtual void ReadActionParameters();
	
	//Add Line to the ApplicationManager
	virtual void Execute() ;


};
#endif


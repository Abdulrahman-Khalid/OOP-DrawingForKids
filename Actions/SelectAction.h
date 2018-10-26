#ifndef SELECT_ACTION_H
#define ADD_RECT_ACTION_H

#include "Action.h"
class SelectAction :
	public Action
{
public:
	SelectAction(ApplicationManager *pApp);
	virtual ~SelectAction();
	virtual void ReadActionParameters();
	virtual void Execute();
};
#endif


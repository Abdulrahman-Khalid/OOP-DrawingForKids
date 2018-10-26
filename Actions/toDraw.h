#pragma once
#include "Action.h"
class toDraw :
	public Action
{
public:
	toDraw(ApplicationManager * pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~toDraw();
};


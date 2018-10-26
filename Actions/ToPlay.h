#pragma once
#include "Action.h"
class ToPlay :
	public Action
{
public:
	ToPlay(ApplicationManager * pApp);
	virtual ~ToPlay();

	virtual void ReadActionParameters();
	virtual void Execute();
};


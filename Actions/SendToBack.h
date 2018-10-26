#pragma once
#include "Action.h"
class SendToBack :
	public Action
{
public:
	SendToBack(ApplicationManager*pApp);
	virtual ~SendToBack();

	virtual void ReadActionParameters();
	virtual void Execute();
};


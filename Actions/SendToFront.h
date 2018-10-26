#pragma once
#include "Action.h"
class SendToFront :
	public Action
{
public:
	SendToFront(ApplicationManager*pApp);
	virtual ~SendToFront();

	virtual void ReadActionParameters();
	virtual void Execute();
};


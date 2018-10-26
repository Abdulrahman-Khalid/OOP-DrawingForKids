#pragma once
#include "Action.h"
class RandomPlayColorAndType :
	public Action
{
	int RandomType;
	color RandomColor;
public:
	RandomPlayColorAndType(ApplicationManager*pApp);
	virtual ~RandomPlayColorAndType();

	virtual void ReadActionParameters();
	virtual void Execute();
};


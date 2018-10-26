#pragma once
#include "Action.h"
class RandomPlayType :
	public Action
{
	int RandomType;
public:
	RandomPlayType(ApplicationManager * pApp);
	virtual ~RandomPlayType();

	virtual void ReadActionParameters();
	virtual void Execute();

};


#pragma once
#include "Action.h"
class ROTATEACTION :
	public Action
{
public:
	ROTATEACTION(ApplicationManager* pApp);
	virtual ~ROTATEACTION();

	virtual void ReadActionParameters();
	virtual void Execute();
};
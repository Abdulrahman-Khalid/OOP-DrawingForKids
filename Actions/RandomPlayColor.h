#pragma once
#include "Action.h"
class RandomPlayColor 
	: public Action
{
	color RandomColor;
public:
	RandomPlayColor(ApplicationManager * pApp);
	virtual ~RandomPlayColor();

	virtual void ReadActionParameters();
	virtual void Execute();
};
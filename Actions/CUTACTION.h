#pragma once
#include "..\ApplicationManager.h"
#include "Action.h"
	
class CUTACTION:public Action
{
public:
	CUTACTION(ApplicationManager *pApp);
	void ReadActionParameters();
	void Execute() ;
	virtual ~CUTACTION();
};


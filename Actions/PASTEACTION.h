#pragma once
#include "..\ApplicationManager.h"
#include "Action.h"
	

class PASTEACTION:public Action
{ Point P1;
 
public:
	PASTEACTION(ApplicationManager *pApp);
	void ReadActionParameters();
	void Execute() ;
	virtual ~PASTEACTION();
};


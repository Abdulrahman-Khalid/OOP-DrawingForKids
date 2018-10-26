#pragma once
#include "..\ApplicationManager.h"
#include "Action.h"
class COPY:public Action
{
public:
	COPY(ApplicationManager *pApp);
	void ReadActionParameters();
	void Execute() ;
	virtual ~COPY();
};
	



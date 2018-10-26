#pragma once
#include "Action.h"
#include<fstream>
class Save :
	public Action
{
	ofstream OutFile;
	string fileName;

public:
	Save(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	
	virtual~Save();
};


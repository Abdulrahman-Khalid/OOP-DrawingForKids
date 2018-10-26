#pragma once
#include "Action.h"
#include<fstream>
class Load : public Action
{
	ifstream InFile;
	string fileName;

public:
	Load(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual~Load();
};


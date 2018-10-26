#ifndef ADD_TRIANGLE_ACTION_H
#define ADD_TRIANGLE_ACTION_H

#include "Action.h"

class AddTriangleAction :	public Action
{private:
	Point P1, P2,P3; //Triangle Corners
	GfxInfo TriGfxInfo;
public:
	AddTriangleAction(ApplicationManager *pApp);
	virtual ~AddTriangleAction();

	//Reads Triangle parameters
	virtual void ReadActionParameters();
	
	//Add Triangle to the ApplicationManager
	virtual void Execute() ;


};
#endif


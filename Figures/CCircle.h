#ifndef CCIRCLE_H
#define CCIRCLE_H

#include "CFigure.h"

class CCircle : public CFigure
{private:
Point centre;
Point OnFrame;

public:
	CCircle();
	CCircle(Point p1, Point p2, GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual bool Select(Point p)const;
    virtual void PrintInfo(Output* pOut)const;
	// Inherited via CFigure
	virtual int getFigureType() const;

	// Inherited via CFigure
	virtual bool CheckCoordinates() const;
	virtual bool Rotate(double angle);
	virtual CFigure* &copyFig ();
	virtual CFigure* move (Point);
	virtual Point getPoint();
	virtual void Save(ofstream &OutFile, Output * pOut);
	virtual void Load(ifstream &InFile, Output * pOut);
};
#endif

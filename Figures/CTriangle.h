#ifndef CTRI_H
#define CTRI_H

#include "CFigure.h"

class CTriangle : public CFigure
{
private:
	Point Corner1;	
	Point Corner2;
	Point Corner3;
public:
	CTriangle();
	CTriangle(Point , Point,Point, GfxInfo FigureGfxInfo );
	virtual void Draw(Output* pOut) const;
	virtual void PrintInfo(Output* pOut) const;
	virtual bool Select(Point p) const;
	virtual int getFigureType() const;

	// Inherited via CFigure
	virtual bool CheckCoordinates() const;
	virtual bool Rotate(double angle);
	virtual CFigure*& copyFig ();
	virtual CFigure* move (Point);
	virtual Point getPoint();
	virtual void Save(ofstream &OutFile, Output * pOut);
	virtual void Load(ifstream &InFile, Output * pOut);
};
#endif

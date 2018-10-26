#ifndef CRECT_H
#define CRECT_H

#include "CFigure.h"

class CRectangle : public CFigure
{
private:
	Point Corner1;	
	Point Corner2;
public:
	CRectangle();
	CRectangle(Point , Point, GfxInfo FigureGfxInfo );
	virtual void Draw(Output* pOut) const;
	virtual void PrintInfo(Output* pOut)const;

	// Inherited via CFigure
	virtual bool Select(Point p) const;
	virtual int getFigureType()const;

	// Inherited via CFigure
	virtual bool CheckCoordinates() const override;
	virtual bool Rotate(double angle);
	virtual CFigure*& copyFig ();
	virtual CFigure* move (Point);
	virtual Point getPoint();
	virtual void Save(ofstream &OutFile, Output * pOut);
	virtual void Load(ifstream &InFile, Output * pOut);
};

#endif
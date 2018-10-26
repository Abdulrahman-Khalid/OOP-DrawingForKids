#ifndef ClINE_H
#define ClINE_H

#include "CFigure.h"

class Line : public CFigure
{
private:
	Point p1;
	Point p2;
public:
	Line();
	Line(Point , Point, GfxInfo FigureGfxInfo );
	virtual void Draw(Output* pOut) const;
	virtual bool Select(Point p)const;
	virtual void PrintInfo(Output* pOut) const;

	// Inherited via CFigure
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


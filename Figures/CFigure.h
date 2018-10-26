#ifndef CFIGURE_H
#define CFIGURE_H
#include <fstream>
#include "..\defs.h"
#include "..\GUI\Output.h"
# define M_PI           3.14159265358979323846

//Base class for all figures
class CFigure
{
protected:
	int ID;	//Each figure has an ID
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
	bool Hidden;
	CFigure*temp;
public:
	CFigure(GfxInfo FigureGfxInfo);
	CFigure();
	
	void SetID(int id);           //set fig's ID
	int GetID()const;             //get fig's ID

	void SetSelected(bool s);	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected

	virtual void Draw(Output* pOut) const  = 0 ;		//Draw the figure
	virtual void PrintInfo(Output* pOut)const = 0;	    //print all figure info on the status bar
	
	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color
	
	bool IsHidden() const;          //check if the fig is hidden
	void setHidden(bool b);         //hide/unhide the fig
	 
	bool IsFilled() const;           //check if the fig is filled
	color getFillClr() const;        //get the fill color of the fig
	void setFilled(bool b);          //fill/unfill the fig
	
	virtual bool Select(Point p)const = 0;         //check if the point p is on the fig
	virtual int getFigureType()const = 0;          //get the the type of the figure
	virtual bool CheckCoordinates()const = 0;      //
	virtual bool Rotate(double angle) = 0;   //rotate the fig
	virtual CFigure*& copyFig ()=0;
	virtual CFigure* move (Point)=0;
	virtual Point getPoint()=0;
	virtual void Save(ofstream &OutFile, Output * pOut) = 0;	//Save the figure parameters to the file
	virtual void Load(ifstream &Infile, Output * pOut) = 0;	//Load the figure parameters to the file
	
	
};

#endif
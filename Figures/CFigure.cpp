#include "CFigure.h"
CFigure::CFigure() {
	Selected = false;
	Hidden = false;
}

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	Hidden = false;

}


void CFigure::SetID(int id)
{
	ID=id;
}

int CFigure::GetID() const
{
	return ID;
} 


void CFigure::SetSelected(bool s)
{Selected = s;}

bool CFigure::IsSelected() const
{	return Selected; }

void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}
bool CFigure::IsHidden()const
{
	return Hidden;
}
bool CFigure::IsFilled() const
{
	return FigGfxInfo.isFilled;
}
void CFigure::setHidden(bool b)
{
	Hidden = b;
}
color CFigure::getFillClr() const
{
	return FigGfxInfo.FillClr;
}

void CFigure::setFilled(bool b)
{
	FigGfxInfo.isFilled = b;
}


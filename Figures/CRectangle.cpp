#include "CRectangle.h"
CRectangle::CRectangle()
{


}

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
}
	

void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}

void CRectangle::PrintInfo(Output* pOut) const
{
	int hight=abs(Corner1.y-Corner2.y);           //rectangle's hight
	int width=abs(Corner1.x-Corner2.x);           //rectangle's width

	pOut->PrintMessage ("Rctangle ID: "+to_string(ID)+".. starts at:("+to_string(Corner1.x)+","+to_string(Corner1.y)
		+")..ends at:("+to_string(Corner2.x)+","+to_string(Corner2.y)+")..Hight:"+to_string(hight)+"..Width:"
		+to_string(width)+"..");
}

bool CRectangle::Select(Point p) const
{
	if (((p.x >= Corner1.x && p.x <= Corner2.x) && (p.y >= Corner1.y && p.y <= Corner2.y)) ||
		((p.x >= Corner1.x && p.x <= Corner2.x) && (p.y <= Corner1.y && p.y >= Corner2.y)) ||
		((p.x <= Corner1.x && p.x >= Corner2.x) && (p.y <= Corner1.y && p.y >= Corner2.y)) ||
		((p.x <= Corner1.x && p.x >= Corner2.x) && (p.y >= Corner1.y && p.y <= Corner2.y)))
	{
		return true;
	}
	return false;
}

int CRectangle::getFigureType() const
{
	return RECTANGLE;
}

bool CRectangle::CheckCoordinates() const
{
	if (Corner1.y <= UI.ToolBarHeight || Corner2.y <= UI.ToolBarHeight 
		|| Corner1.y >= UI.height - UI.StatusBarHeight ||Corner2.y >= UI.height - UI.StatusBarHeight
		||Corner1.x<0 || Corner2.x<0|| Corner1.y<0 || Corner2.y<0)
	{
		return false;
	}
	return true;
}
bool CRectangle::Rotate(double angle)
{
	if (angle == 180)
		return true;
	//Temp points because it could fail
	Point temp_p1 = Corner1;
	Point temp_p2 = Corner2;
	Point Center;
	Center.x = (Corner1.x + Corner2.x) / 2;
	Center.y = (Corner1.y + Corner2.y) / 2;
	angle = ((360 - angle) / 180) * M_PI; //degree to rad
	//The new points
	Corner1.x = (int)((temp_p1.x - Center.x) * cos(angle) - (temp_p1.y - Center.y) * sin(angle) + Center.x);
	Corner1.y = (int)((temp_p1.x - Center.x) * sin(angle) + (temp_p1.y - Center.y) * cos(angle) + Center.y);
	Corner2.x = (int)((temp_p2.x - Center.x) * cos(angle) - (temp_p2.y - Center.y) * sin(angle) + Center.x);
	Corner2.y = (int)((temp_p2.x - Center.x) * sin(angle) + (temp_p2.y - Center.y) * cos(angle) + Center.y);
	bool flag = CheckCoordinates();
	if (flag)
	{
		return true;
	}
	else
	{
		Corner1 = temp_p1;
		Corner2 = temp_p2;
		return false;
	}
}
CFigure*& CRectangle:: copyFig ()
{
	temp=new CRectangle (*this);
	temp->SetSelected(false);
	return temp;
}
CFigure*CRectangle:: move (Point a)
{	
	Corner2.x=a.x+(Corner2.x-Corner1.x);
	Corner2.y=a.y+(Corner2.y-Corner1.y);
	Corner1=a;
	return this;
}
Point CRectangle:: getPoint()
{
	return Corner1;
}
void CRectangle::Save(ofstream &OutFile, Output * pOut)
{
	
	OutFile << pOut->intToType(getFigureType()) << "   " << GetID() << "   " << Corner1.x << "   " << Corner1.y 
		<< "   " << Corner2.x << "   " << Corner2.y << "   " << pOut->ColorToString(FigGfxInfo.DrawClr) 
		<< "   " << pOut->ColorToString(FigGfxInfo.FillClr) << endl;


}
void CRectangle::Load(ifstream &InFile, Output * pOut)
{

	string dclr, fclr;
	InFile >> ID >> Corner1.x >> Corner1.y >> Corner2.x >> Corner2.y >> dclr >> fclr;

	FigGfxInfo.DrawClr = (pOut->StringToColour(dclr));

	if (UI.BkGrndColor != pOut->StringToColour(fclr))
	{
		FigGfxInfo.FillClr = (pOut->StringToColour(fclr));
		FigGfxInfo.isFilled = true;
	}
	else
	{
		FigGfxInfo.isFilled = false;
		FigGfxInfo.FillClr = LIGHTBLUE;
	}
}
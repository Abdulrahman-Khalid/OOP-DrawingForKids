#include "CTriangle.h"

CTriangle::CTriangle() {

}

CTriangle::CTriangle (Point P1, Point P2, Point P3, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	Corner3 = P3;
}
	

void CTriangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawTriangle(Corner1, Corner2, Corner3, FigGfxInfo, Selected);
}
void CTriangle::PrintInfo(Output* pOut)const
{
	pOut->PrintMessage ("Triangle ID: "+to_string(ID)+".. corner1:("+to_string(Corner1.x)+","+to_string(Corner1.y)
		+")..corner2:("+to_string(Corner2.x)+","+to_string(Corner2.y)+")..corner3:("+to_string(Corner3.x)+","
		+to_string(Corner3.y)+")..");
}


bool CTriangle::Select(Point p) const
{
	Point p1; p1.x = Corner2.x - Corner1.x;  //vector P1
	p1.y = Corner2.y - Corner1.y;
	Point p2; p2.x = Corner3.x - Corner2.x;  //vector P2
	p2.y = Corner3.y - Corner2.y;

	double A = abs((p1.x*p2.y) - (p2.x*p1.y)); //Total Triangle (corner1-corner2-corner3) Area

	Point v1; v1.x = Corner1.x - p.x;   //vector from the clicked point to corner1 
	v1.y = Corner1.y - p.y;
	Point v2; v2.x = Corner2.x - p.x;   //vector from the clicked point to corner2 
	v2.y = Corner2.y - p.y;
	Point v3; v3.x = Corner3.x - p.x;   //vector from the clicked point to corner3
	v3.y = Corner3.y - p.y;

	int A12 = abs((v1.x*v2.y) - (v2.x*v1.y)); //double the area of tri (p-corner1-corner2)
	int A13 = abs((v1.x*v3.y) - (v3.x*v1.y)); //double the area of tri (p-corner1-corner3)
	int A32 = abs((v3.x*v2.y) - (v2.x*v3.y)); //double the area of tri (p-corner3-corner2)
	if (A12 + A13 + A32 == A)
	{
		return true;
	}
	else
	{
		return false;
	}

}
int CTriangle::getFigureType() const
{
	return TRIANGLE;
}

bool CTriangle::CheckCoordinates() const
{
	if (Corner1.y <= UI.ToolBarHeight || Corner2.y <= UI.ToolBarHeight ||
		Corner3.y <= UI.ToolBarHeight || Corner1.y >= UI.height - UI.StatusBarHeight || 
		Corner2.y >= UI.height - UI.StatusBarHeight || Corner3.y >= UI.height - UI.StatusBarHeight
		|| Corner1.x<0|| Corner2.x<0|| Corner3.x<0 || Corner1.y<0 || Corner2.y<0 || Corner3.y<0)
	{
		return false;
	}
	return true;
}
bool CTriangle::Rotate(double angle)
{
	//Temp points because it could fail
	Point temp_p1 = Corner1;
	Point temp_p2 = Corner2;
	Point temp_p3 = Corner3;
	Point Center;
	Center.x = (Corner1.x + Corner2.x + Corner3.x) / 3;
	Center.y = (Corner1.y + Corner2.y + Corner3.y) / 3;
	angle = ((360 - angle) / 180) * M_PI; //degree to rad
	//The new points
	Corner1.x = (int)((temp_p1.x - Center.x) * cos(angle) - (temp_p1.y - Center.y) * sin(angle) + Center.x);
	Corner1.y = (int)((temp_p1.x - Center.x) * sin(angle) + (temp_p1.y - Center.y) * cos(angle) + Center.y);
	Corner2.x = (int)((temp_p2.x - Center.x) * cos(angle) - (temp_p2.y - Center.y) * sin(angle) + Center.x);
	Corner2.y = (int)((temp_p2.x - Center.x) * sin(angle) + (temp_p2.y - Center.y) * cos(angle) + Center.y);
	Corner3.x = (int)((temp_p3.x - Center.x) * cos(angle) - (temp_p3.y - Center.y) * sin(angle) + Center.x);
	Corner3.y = (int)((temp_p3.x - Center.x) * sin(angle) + (temp_p3.y - Center.y) * cos(angle) + Center.y);
	bool flag = CheckCoordinates();
	if (flag)
	{
		return true;
	}
	else
	{
		Corner1 = temp_p1;
		Corner2 = temp_p2;
		Corner3 = temp_p3;
		return false;
	}
}
CFigure*& CTriangle:: copyFig ()
{
	temp=new CTriangle (*this);
	temp->SetSelected(false);
	return temp;

}

CFigure*CTriangle:: move (Point a)
{	
	
	Corner2.x=a.x+(Corner2.x-Corner1.x);
	Corner2.y=a.y+(Corner2.y-Corner1.y);
	Corner3.x=a.x+(Corner3.x-Corner1.x);
	Corner3.y=a.y+(Corner3.y-Corner1.y);
	Corner1=a;
	
	
	
	return this;
}
Point CTriangle:: getPoint()
{
	return Corner1;
}
void CTriangle::Save(ofstream &OutFile, Output * pOut)
{
	
	OutFile << pOut->intToType(getFigureType()) << "   " << GetID() << "   " << Corner1.x << " " << Corner1.y << "   " << Corner2.x 
		<< " " << Corner2.y << "   " << Corner3.x << " " << Corner3.y << "   " << pOut->ColorToString(FigGfxInfo.DrawClr) 
		<< "   " << pOut->ColorToString(FigGfxInfo.FillClr) << endl;

}
void CTriangle::Load(ifstream &InFile, Output * pOut)
{
	
	string dclr, fclr;
	InFile >> ID >> Corner1.x >> Corner1.y >> Corner2.x >> Corner2.y >> Corner3.x >> Corner3.y >> dclr >> fclr;
	FigGfxInfo.DrawClr = (pOut->StringToColour(dclr));

	if (UI.BkGrndColor != pOut->StringToColour(fclr))
	{
		FigGfxInfo.FillClr = (pOut->StringToColour(fclr));
		FigGfxInfo.isFilled = true;
	}
	else
	{
		FigGfxInfo.isFilled = false;
		FigGfxInfo.FillClr = LIGHTBLUE;//because i don't want it to take garbage
	}
}
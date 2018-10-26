#include "CLine.h"

Line::Line() {

}

Line::Line(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	p1=P1;
	p2=P2;
}

void Line::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawLine(p1, p2, FigGfxInfo, Selected);
}

bool Line:: Select(Point p)const
{ 
	int d1=(int)sqrt(pow((p.x - p1.x),2) + pow((p.y - p1.y),2));          //length between p1 & clicked point
	int d2=(int)sqrt(pow((p.x - p2.x),2)+ pow((p.y - p2.y),2));           //length between p2 & clicked point
	int dis=(int)sqrt(pow((p1.x - p2.x),2) + pow((p1.y - p2.y),2));       //line's length
   if(d1+d2==dis)
      {return true;}
   else 
   {return false;}
}

void Line::PrintInfo(Output* pOut)const
{
	int dis=(int)sqrt(pow((p1.x - p2.x),2) + pow((p1.y - p2.y),2));   //line's length

	pOut->PrintMessage ("Line ID: "+to_string(ID)+".. starts at:("+to_string(p1.x)+","+to_string(p1.y)
		+")..ends at:("+to_string(p2.x)+","+to_string(p2.y)+")..Length:"+to_string(dis)+".."); 
}   

int Line::getFigureType() const
{
	return LINE;
}

bool Line::CheckCoordinates() const
{
	if (p1.y <= UI.ToolBarHeight || p2.y <= UI.ToolBarHeight ||
		p1.y >= UI.height - UI.StatusBarHeight || p2.y >= UI.height - UI.StatusBarHeight||p1.x<0||p2.x<0||p1.y<0||p2.y<0)
	{
		return false;
	}
	return true;
}
bool Line::Rotate(double angle) 
{
	if (angle == 180)
		return true;
	//Temp points because it could fail
	Point temp_p1 = p1;
	Point temp_p2 = p2;
	Point Center;
	Center.x = (p1.x + p2.x) / 2;
	Center.y = (p1.y + p2.y) / 2;
	angle = ((360-angle) / 180) * M_PI; //Degree to Rad
	//The new points
	p1.x = (int)((temp_p1.x - Center.x) * cos(angle) - (temp_p1.y - Center.y) * sin(angle) + Center.x);
	p1.y = (int)((temp_p1.x - Center.x) * sin(angle) + (temp_p1.y - Center.y) * cos(angle) + Center.y);
	p2.x = (int)((temp_p2.x - Center.x) * cos(angle) - (temp_p2.y - Center.y) * sin(angle) + Center.x);
	p2.y = (int)((temp_p2.x - Center.x) * sin(angle) + (temp_p2.y - Center.y) * cos(angle) + Center.y);
	bool flag = CheckCoordinates();
	if (flag)
		return true;
	else
	{
		p1 = temp_p1;
		p2 = temp_p2;
		return false;
	}
}
CFigure*& Line:: copyFig ()
{
	temp=new Line (*this);
	temp->SetSelected(false);
	return temp;

}	
CFigure*Line:: move (Point a)
{	p2.x=a.x+(p2.x-p1.x);
	p2.y=a.y+(p2.y-p1.y);
	p1=a;
	return this;
}
	
Point Line:: getPoint()
{
	return p1;
}
				

void Line::Save(ofstream &OutFile, Output * pOut)
{
	
	OutFile << pOut->intToType(getFigureType()) << "  " << GetID() << "  " << p1.x << " " << p1.y << "  " << p2.x 
		<< " " << p2.y << "  " << pOut->ColorToString(FigGfxInfo.DrawClr) << endl;

}
void Line::Load(ifstream &InFile, Output * pOut)
{
	string dclr;
	InFile >> ID >> p1.x >> p1.y >> p2.x >> p2.y >> dclr;
	FigGfxInfo.DrawClr = (pOut->StringToColour(dclr));
	FigGfxInfo.FillClr = FigGfxInfo.DrawClr;
	FigGfxInfo.isFilled = true;
}

#include "CCircle.h"

CCircle::CCircle()
{


}

CCircle::CCircle (Point p1, Point p2, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{ centre=p1;
  OnFrame=p2;
}


void CCircle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a circle on the screen	
	pOut->DrawCircle( centre, OnFrame, FigGfxInfo, Selected);
}

void CCircle::PrintInfo(Output* pOut) const
{   int Radius = (int)sqrt((centre.x - OnFrame.x)*(centre.x - OnFrame.x)    //reduis
                    + (centre.y - OnFrame.y)*(centre.y - OnFrame.y));
	
    pOut->PrintMessage ("Circle ID: "+to_string(ID)+".. centre:("+to_string(centre.x)+","
		+to_string(centre.y)+")..Raduis:"+to_string(Radius)+"..");             //print circle info
}

bool CCircle::Select(Point p)const
{
	double dis=sqrt(pow((p.x - centre.x),2) + pow((p.y - centre.y),2));
	double Radius=sqrt(pow((OnFrame.x-centre.x),2)+pow((OnFrame.y-centre.y),2));
	   if(dis<=Radius)
      {return true;}
   else 
      {return false;}
}
int CCircle::getFigureType() const
{
	return CIRCLE;
}

bool CCircle::CheckCoordinates() const
{
	int Radius = (int)sqrt((centre.x - OnFrame.x)*(centre.x - OnFrame.x) + (centre.y - OnFrame.y)*(centre.y - OnFrame.y));
	if (centre.y <= UI.ToolBarHeight || centre.y - Radius <= UI.ToolBarHeight || centre.x - Radius<0 
		|| centre.x + Radius>UI.width || centre.y + Radius >= UI.height - UI.StatusBarHeight)
	{
		return false;
	}
	return true;
}
bool CCircle::Rotate(double angle)
{
	return true;
}
CFigure*& CCircle:: copyFig ()
{
	temp=new CCircle (*this);
	temp->SetSelected(false);
	return temp;

}

CFigure*CCircle:: move (Point a)
{
	OnFrame.x=a.x+(OnFrame.x-centre.x);
	OnFrame.y=a.y+(OnFrame.y-centre.y);
	centre=a;
	return this;
}
Point CCircle:: getPoint()
{return centre;}	
void CCircle::Save(ofstream &OutFile, Output * pOut)
{
	
	OutFile << pOut->intToType(getFigureType()) << "   " << GetID() << "   " << centre.x << " " << centre.y 
		<< "  " << OnFrame.x << "  " << OnFrame.y << "   " << pOut->ColorToString(FigGfxInfo.DrawClr) 
		<< "   " << pOut->ColorToString(FigGfxInfo.FillClr) << endl;

}
void CCircle::Load(ifstream &InFile, Output * pOut)
{
	string dclr, fclr;

	InFile >> ID >> centre.x >> centre.y >> OnFrame.x >> OnFrame.y >> dclr >> fclr;
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
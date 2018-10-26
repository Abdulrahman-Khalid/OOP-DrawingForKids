#ifndef OUPTUT_H
#define OUPTUT_H
#include "Input.h"

class Output	//The application manager should have a pointer to this class
{
private:
	window* pWind;	//Pointer to the Graphics Window
public:
	Output();

	window* CreateWind(int, int, int, int) const; //creates the application window
	void CreateDrawToolBar() const;	//creates Draw mode toolbar & menu
	void CreateColorToolBar() const;
	void CreatePlayToolBar() const;	//creates Play mode toolbar & menu
	void CreateRotateToolBar() const;
	void CreateStatusBar() const;	//create the status bar

	Input* CreateInput() const; //creates a pointer to the Input object
	color getBkGrndColor() const;
	int getUIMenuItemWidth() const;
	int getUIToolBarHeight() const;
	void ClearToolBarMessage() const;
	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area

								// -- Figures Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected = false) const;  //Draw a rectangle
	void DrawLine(Point P1, Point P2, GfxInfo LineGfxInfo, bool selected) const;
	void DrawCircle(Point P1, Point P2, GfxInfo CircleGfxInfo, bool selected) const;
	void DrawTriangle(Point P1, Point P2, Point P3, GfxInfo CircleGfxInfo, bool selected) const;
	void setUIFillColor(color c);
	///Make similar functions for drawing all other figures.

	void PrintMessage(string msg) const;	//Print a message on Status bar

	void PrintMessageOnToolBar(string msg) const;

	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;	//get current filling color
	int getCrntPenWidth() const;		//get current pen width
	void setCrntDrawColor(color);
	void setCrntFillColor(color);
	string ColorToString(color c)const;
	string intToType(int i)const;
	color StringToColour(string c) const;
	~Output();
};

#endif
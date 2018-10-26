#include "Output.h"


Output::Output()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;

	UI.width = 1250;
	UI.height = 650;
	UI.wx = 5;
	UI.wy = 5;


	UI.StatusBarHeight = 40;
	UI.ToolBarHeight = 60;
	UI.MenuItemWidth = 60;

	UI.MsgColor = GRAY;		//Messages color
	UI.BkGrndColor = LIGHTBLUE;	//Background color
	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = UI.BkGrndColor;	//Filling color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = DARKBLUE;
	UI.PenWidth = 6;	//width of the figures frames
						//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	pWind->DrawImage("images\\MenuItems\\welcome.jpg", 0, 0, UI.width, UI.height);
	Sleep(5000);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");

	CreateDrawToolBar();
	CreateStatusBar();
}
//////////////////////////////////////////////////////////////////////////////////////////
Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}
//////////////////////////////////////////////////////////////////////////////////////////
color Output::getBkGrndColor()const
{
	return UI.BkGrndColor;
}
//////////////////////////////////////////////////////////////////////////////////////////
int Output::getUIMenuItemWidth()const
{
	return UI.MenuItemWidth;
}
//////////////////////////////////////////////////////////////////////////////////////////
int Output::getUIToolBarHeight()const
{
	return UI.ToolBarHeight;
}
//======================================================================================//
//								Interface Functions										//
//======================================================================================//
window* Output::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearToolBarMessage()const
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(500, UI.wy, UI.width, UI.ToolBarHeight-5, FILLED);
}
//////////////////////////////////////////////////////////////////////////////////////////	
void Output::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateDrawToolBar() const
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight, FILLED);

	UI.InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_LINE] = "images\\MenuItems\\line.jpg";
	MenuItemImages[ITM_TRIAN] = "images\\MenuItems\\triangle.jpg";
	MenuItemImages[ITM_RECT] = "images\\MenuItems\\rectangle.jpg";
	MenuItemImages[ITM_CIRC] = "images\\MenuItems\\circle.jpg";
	MenuItemImages[ITM_DrawClr] = "images\\MenuItems\\stroke.jpg";
	MenuItemImages[ITM_FillClr] = "images\\MenuItems\\fill.jpg";
	MenuItemImages[ITM_SELECT] = "images\\MenuItems\\select.jpg";
	MenuItemImages[ITM_DELETE] = "images\\MenuItems\\delete.jpg";
	MenuItemImages[ITM_COPY] = "images\\MenuItems\\copy.jpg";
	MenuItemImages[ITM_CUT] = "images\\MenuItems\\cut.jpg";
	MenuItemImages[ITM_PASTE] = "images\\MenuItems\\paste.jpg";
	MenuItemImages[ITM_ROTATE] = "images\\MenuItems\\rotate.jpg";
	MenuItemImages[ITM_SENDTOFRONT] = "images\\MenuItems\\sendtofront.jpg";
	MenuItemImages[ITM_SENDTOBACK] = "images\\MenuItems\\sendtoback.jpg";
	MenuItemImages[ITM_PLAY_MODE] = "images\\MenuItems\\play.jpg";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\save.jpg";
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\load.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\exit.jpg";

																
	for (int i = 0; i<DRAW_ITM_COUNT; i++) //Draw menu item one image at a time
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(DARKBLUE, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateColorToolBar() const
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight, FILLED);
	string MenuItemImages[CLR_ITM_COUNT];
	MenuItemImages[CLR_WHITE] = "images\\MenuItems\\white.jpg";
	MenuItemImages[CLR_GREEN] = "images\\MenuItems\\green.jpg";
	MenuItemImages[CLR_BLUE] = "images\\MenuItems\\blue.jpg";
	MenuItemImages[CLR_RED] = "images\\MenuItems\\red.jpg";
	MenuItemImages[CLR_BLACK] = "images\\MenuItems\\black.jpg";
	MenuItemImages[CLR_BACK] = "images\\MenuItems\\back.jpg";
	for (int i = 0; i<CLR_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->SetPen(DARKBLUE, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateRotateToolBar()const
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight, FILLED);
	string MenuItemImages[Rotate_ITM_COUNT];
	MenuItemImages[Rotate_BACK] = "images\\MenuItems\\back.jpg";
	MenuItemImages[Rotate_90] = "images\\MenuItems\\90.jpg";
	MenuItemImages[Rotate_180] = "images\\MenuItems\\180.jpg";
	MenuItemImages[Rotate_270] = "images\\MenuItems\\270.jpg";
	for (int i = 0; i<Rotate_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->SetPen(DARKBLUE, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreatePlayToolBar() const
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight, FILLED);

	UI.InterfaceMode = MODE_PLAY;

	string MenuItemImages[PLAY_ITM_COUNT];
	MenuItemImages[ITM_COLOR] = "images\\MenuItems\\BY_COLOR.jpg";
	MenuItemImages[ITM_TYPE] = "images\\MenuItems\\BY_SHAPE.jpg";
	MenuItemImages[ITM_COLOR_TYPE] = "images\\MenuItems\\BY_SHAPE_COLOR.jpg";
	MenuItemImages[ITM_DRAW] = "images\\MenuItems\\draw_mode.jpg";
	for (int i = 0; i<PLAY_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->SetPen(DARKBLUE, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearDrawArea() const
{
	pWind->FlushMouseQueue();
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight+2, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight / 1.1), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::PrintMessageOnToolBar(string msg) const	//Prints a message on tool bar
{
	ClearToolBarMessage();
	pWind->SetPen(DARKBLUE, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(500, (int)(UI.ToolBarHeight / 1.8), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::setCrntDrawColor(color DrwClr) {
	UI.DrawColor = DrwClr;
}
void Output::setCrntFillColor(color FillClr) {
	UI.FillColor = FillClr;
}
//////////////////////////////////////////////////////////////////////////////////////////
string Output::ColorToString(color c) const
{
	if (c == BLACK)
		return "BLACK";
	else if (c == WHITE)
		return "WHITE";
	else if (c == GREEN)
		return "GREEN";
	else if (c == BLUE)
		return "BLUE";
	else if (c == RED)
		return "RED";
	return "Non-filled";
}
color Output::StringToColour(string c) const
{
	if ("Non-filled" == c)
		return LIGHTBLUE;
	if ("BLACK" == c)
		return BLACK;
	else if (c == "WHITE")
		return WHITE;
	else if (c == "GREEN")
		return GREEN;
	else if (c == "BLUE")
		return BLUE;
	else if (c == "RED")
		return RED;

}

//////////////////////////////////////////////////////////////////////////////////////////
string Output::intToType(int i) const
{
	if (i == CIRCLE)
		return "CIRCLE";
	else if (i == LINE)
		return "LINE";
	else if (i == RECTANGLE)
		return "RECTANGLE";
	else if (i == TRIANGLE)
		return "TRIANGLE";
	return " "; //to eleminate the warning
}
//////////////////////////////////////////////////////////////////////////////////////////
color Output::getCrntDrawColor() const	//get current drwawing color
{
	return UI.DrawColor;
}
//////////////////////////////////////////////////////////////////////////////////////////
color Output::getCrntFillColor() const	//get current filling color
{
	return UI.FillColor;
}
//////////////////////////////////////////////////////////////////////////////////////////
int Output::getCrntPenWidth() const		//get current pen width
{
	return UI.PenWidth;
}
//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//
void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);

}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::DrawLine(Point P1, Point P2, GfxInfo LineGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = LineGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);

	pWind->DrawLine(P1.x, P1.y, P2.x, P2.y, FRAME);

}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::DrawCircle(Point P1, Point P2, GfxInfo CircleGfxInfo, bool selected) const
{
	int Radius = (int)sqrt((P1.x - P2.x)*(P1.x - P2.x) + (P1.y - P2.y)*(P1.y - P2.y));
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = CircleGfxInfo.DrawClr;
	drawstyle style;
	if (CircleGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(CircleGfxInfo.FillClr);
	}
	else
		style = FRAME;
	pWind->SetPen(DrawingClr, 1);

	pWind->DrawCircle(P1.x, P1.y, Radius, style);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::DrawTriangle(Point P1, Point P2, Point P3, GfxInfo TriangleGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = TriangleGfxInfo.DrawClr;
	drawstyle style;
	if (TriangleGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(TriangleGfxInfo.FillClr);
	}
	else
		style = FRAME;
	pWind->SetPen(DrawingClr, 1);

	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);
}
void Output::setUIFillColor(color c)
{
	UI.FillColor = c;
}
//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}
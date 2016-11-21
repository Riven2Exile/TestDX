#include "stdafx.h"
#include "draw_something.h"
#include "..\..\LineSprite.h"


unsigned long g_point_color = 0xffffffff;

unsigned long g_line_color = 0xffffffff;

unsigned long g_rect_frame_color = 0xffffffff;


void set_current_point_color(const unsigned long& dwColor)
{
	g_point_color = dwColor;
}

unsigned long get_current_point_color()
{
	return g_point_color;
}

void draw_point(const int& x, const int& y)
{

}

/////
void draw_line(const int& x1, const int& y1, const int& x2, const int& y2){
	static CLineSprite line;
	line.set_line(x1, y1, x2, y2);
	line.set_color(g_line_color);
	line.draw();
}

void set_current_line_color(const unsigned long& dwColor){
	g_line_color = dwColor;
}

void draw_rect_frame(const int& left, const int& top, const int& right, const int& bottom)
{
	static CLineSprite u;
	u.set_line(left, top, right, top);
	u.set_color(g_rect_frame_color);
	u.draw();

	static CLineSprite l;
	l.set_line(left, top, left, bottom);
	l.set_color(g_rect_frame_color);
	l.draw();

	static CLineSprite r;
	r.set_line(right, top, right, bottom);
	r.set_color(g_rect_frame_color);
	r.draw();

	static CLineSprite d;
	d.set_line(left, bottom, right, bottom);
	d.set_color(g_rect_frame_color);
	d.draw();
}

void set_current_rect_frame_color(const unsigned long& dwColor)
{
	g_rect_frame_color = dwColor;
}

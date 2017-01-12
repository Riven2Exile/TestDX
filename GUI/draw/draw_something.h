
/*
	绘制一些东西
*/



void set_current_point_color(const unsigned long& dwColor);
unsigned long get_current_point_color();
void draw_point(const int& x, const int& y);

//void draw_a_line(const int& x_start, const int);
void draw_line(const int& x1, const int& y1, const int& x2, const int& y2);
void set_current_line_color(const unsigned long& dwColor);
//void draw a rect frame
void draw_rect_frame(const int& left, const int& top, const int& right, const int& bottom);
void set_current_rect_frame_color(const unsigned long& dwColor);
//void draw a rect
#include "color_t.cpp"
#ifndef PEN_T
#define PEN_T

class pen_t{
	private:
	color_t pen_color; //default white color
	float line_width;   //default line width = 2.0f
	bool eraser_mode;  //default false
	color_t background_color; //defualt color assumed to be black
	public:
	void set_pen_color(color_t c){pen_color=c;}
	void set_line_width(float lw){line_width=lw;}
	void set_eraser_mode(bool em){eraser_mode=em;}
	void set_background_color(color_t c){background_color=c;}
	color_t get_pen_color(){return pen_color;}
	color_t get_background_color(){return background_color;}
	color_t get_draw_color(){if(eraser_mode)return background_color;else return pen_color;}
	float get_line_width(){return line_width;}
	bool get_eraser_mode(){return eraser_mode;}
	pen_t(color_t c = *(new color_t(255,255,255)),float lw=2.0f,color_t c2 = *(new color_t(0,0,0)),bool em=false):pen_color(c),line_width(lw),eraser_mode(em),background_color(c2){};
};

#endif

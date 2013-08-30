#include "color_t.cpp"

#ifndef POINT_T
#define POINT_T

class point_t{
	private:
	color_t point_color; //default green
	float point_width; //default 2.0f
	float pos_x; //default 0
	float pos_y; //default 0
	public:
	color_t get_color(){return point_color;}
	float get_x(){return pos_x;}
	float get_y(){return pos_y;}
	void set_x(float x){pos_x=x;}
	void set_y(float y){pos_y=y;}
	void set_color(color_t c){point_color=c;}
	void draw(){
		glColor3f(((float)point_color.getRed())/(float)255, ((float)point_color.getGreen())/(float)255, ((float)point_color.getBlue())/(float)255);
  		glPointSize(point_width);
  		glBegin(GL_POINTS);
    	glVertex2f(pos_x, pos_y);
  		glEnd();
	}
	point_t(float x=0,float y=0,float pw=2.0f,color_t c = *(new color_t(0,255,0))):pos_x(x),pos_y(y),point_width(pw),point_color(c){};
};

#endif

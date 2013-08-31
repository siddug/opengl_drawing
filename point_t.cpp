#include "color_t.cpp"
#include <sstream>

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
	float get_point_width(){return point_width;}
	void draw(){
		glColor3f(((float)point_color.getRed())/(float)255, ((float)point_color.getGreen())/(float)255, ((float)point_color.getBlue())/(float)255);
  		glPointSize(point_width);
  		glBegin(GL_POINTS);
    	glVertex2f(pos_x, pos_y);
  		glEnd();
	}
	point_t(float x=0,float y=0,float pw=2.0f,color_t c = *(new color_t(0,255,0))):pos_x(x),pos_y(y),point_width(pw),point_color(c){};
	std::string print(){
		std::stringstream s;
		s<<point_width;
		std::string strw=s.str();
		s<<pos_x;
		std::string strx=s.str();
		s<<pos_y;
		std::string stry=s.str();
		return point_color.print()+std::string("\t")+strw+std::string("\t")+strx+std::string("\t")+stry;
	}
};

#endif

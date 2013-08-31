#include "point_t.cpp"

#ifndef LINE_T
#define LINE_T

class line_t{
	private:
	point_t point1; // default point
	point_t point2; // defualt point
	color_t line_color; // default color
	float line_width; // default 2.0f
	public:
	point_t get_point1(){return point1;}
	point_t get_point2(){return point2;}
	color_t get_color(){return line_color;}
	float get_line_width(){return line_width;}
	void set_point1(point_t p){point1=p;}
	void set_point2(point_t p){point2=p;}
	void set_color(color_t c){line_color=c;}
	void set_line_width(float lw){line_width=lw;}
	line_t(point_t p1=*(new point_t()), point_t p2=*(new point_t()),float lw=2.0f, color_t c=*(new color_t())):point1(p1),point2(p2),line_width(lw),line_color(c){};
	void draw(){draw_points(point1.get_x(),point1.get_y(),point2.get_x(),point2.get_y());}
	//took from sir's code. replace it.
	void swap (float &x,float &y){float temp=x;x=y;y=temp;}
	void draw_points(float x0, float y0, float x1, float y1){
  		bool steep = abs(y1 - y0) > abs(x1 - x0);
  		if (steep){swap(x0, y0);swap(x1, y1);}
  		if (x0 > x1){swap(x0, x1);swap(y0, y1);}
		float deltax = x1 - x0;
  		float deltay = abs(y1 - y0);
  		float error = 0.0;
  		float deltaerr = (float)deltay / (float)deltax;
  		float ystep;
  		float y = y0;
		if (y0 < y1) ystep = 1; else ystep = -1;
  		for (float x=x0; x < x1; x++){
        	if (steep) {point_t p(y,x,line_width,line_color); p.draw();}
      		else {point_t p(x,y,line_width,line_color); p.draw();}
      		error = error + deltaerr;
      		if (error >= 0.5) {y = y + ystep;error = error - 1.0;}
    	}
	}
	
	std::string print(){
		std::stringstream buffer;
		buffer << line_width;
		std::string s = point1.print() + std::string("\t") + point2.print() + std::string(" \t") + line_color.print() + std::string("\t") + buffer.str();
		return s; 
	}

};

#endif

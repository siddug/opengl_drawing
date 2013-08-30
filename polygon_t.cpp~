#include "line_t.cpp"
#include "fill_t.cpp"
#include "point_t.cpp"
#include <vector>

#ifndef POLYGON_T
#define POLYGON_T

class polygon_t{
	private:
	std::vector<point_t> points;
	color_t current_fill_color;
	color_t current_fill_color2;
	color_t current_border_color;
	float mesh_width;
	bool current_fill_mode;// true if chcker mode is on
	bool filled;
	public:
	polygon_t(std::vector<point_t> p= *(new std::vector<point_t>), color_t c=*(new color_t(0,0,255)), color_t c2=*(new color_t(255,0,0)), color_t c3=*(new color_t(0,255,0)), float mw=0.2f, bool cfm=false, bool f=false):points(p), current_fill_color(c), current_fill_mode(cfm), filled(f), current_fill_color2(c2), mesh_width(mw), current_border_color(c3){};
	std::vector<point_t> get_points(){return points;}
	color_t get_current_fill_color(){return current_fill_color;}
	color_t get_current_fill_color2(){return current_fill_color2;}
	color_t get_current_border_color(){return current_border_color;}
	bool get_current_fill_mode(){return current_fill_mode;}
	bool get_filled(){return filled;}
	float get_mesh_width(){return mesh_width;}
	void set_points(std::vector <point_t> p){points=p;}
	void set_current_fill_color(color_t c){current_fill_color=c;}
	void set_current_fill_color2(color_t c){current_fill_color2=c;}
	void set_current_border_color(color_t c){current_border_color=c;}
	void set_filled(bool f){filled=f;}
	void set_mesh_width(float mw){mesh_width=mw;}
	void draw(){
		bool tofill=false;
		if(!tofill && points.size()>=3){
			for(int i=0;i<points.size()-1;i++){//draw lines
				line_t l(points.at(i),points.at(i+1), mesh_width, current_border_color); 
				l.draw(); 
			}
			line_t l(points.at(points.size()-1),points.at(0), mesh_width, current_border_color);
			l.draw();			
		}
		if(tofill){}// fill
	
	}
};

#endif

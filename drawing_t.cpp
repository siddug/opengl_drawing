#include "line_t.cpp"
#include "point_t.cpp"
#include "polygon_t.cpp"

#include <vector>

#ifndef DRAWING_T
#define DRAWING_T

class drawing_t{
	private:
	std::vector<line_t> lines;
	std::vector<point_t> points;
	std::vector<polygon_t> polygons; 
	public:
	drawing_t(std::vector<line_t> l=*(new std::vector<line_t>), std::vector<point_t> p=*(new std::vector<point_t>), std::vector<polygon_t> po=*(new std::vector<polygon_t>)) : lines(l), points(p), polygons(po) {};
	void insert_line(line_t l){lines.push_back(l);}
	void insert_point(point_t p){points.push_back(p);}
	void insert_polygon(polygon_t po){polygons.push_back(po);}
	std::vector<line_t> get_lines(){return lines;}
	std::vector<point_t> get_points(){return points;}
	std::vector<polygon_t> get_polygons(){return polygons;}
	void draw(){
		for(int i=0;i<lines.size();i++){lines.at(i).draw();}
		for(int i=0;i<points.size();i++){points.at(i).draw();}
		for(int i=0;i<polygons.size();i++){polygons.at(i).draw();}
	}
	void clear(){lines.clear();points.clear();polygons.clear();}
};

#endif

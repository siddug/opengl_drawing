#include "drawing_t.cpp"
#include <vector>

#ifndef CANVAS_T
#define CANVAS_T

class canvas_t{
	public:
	color_t background_color;
	int width;
	int height;
	drawing_t current_drawing;
	std::vector<std::vector<color_t> > pixel_array;
	canvas_t(int w, int h, color_t c=*(new color_t(0,0,0))){
		width=w;
		height=h;
		background_color=c;
		for(int i=0;i<width;i++){
			std::vector<color_t> vec;
			for(int j=0;j<height;j++){
				
				vec.push_back(c); 
				
			}
			pixel_array.push_back(vec);
		}
		current_drawing=*(new drawing_t());
	}
	void clear(){
		//current_drawing.clear();
		for(int i=0;i<width;i++){
			std::vector<color_t> vec;
			for(int j=0;j<height;j++){
				
				vec.push_back(background_color); 
				
			}
			pixel_array.at(i)=vec;
		}
		
	}
};

#endif

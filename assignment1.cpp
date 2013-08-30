#include <cstdlib>
#include <iostream>
#include <string>
#include <GL/glut.h>
#include "pen_t.cpp"
#include "fill_t.cpp"
#include "point_t.cpp"
#include "line_t.cpp"
#include "polygon_t.cpp"
#include "drawing_t.cpp"
#include "canvas_t.cpp"

int window_width = 1000;
int window_height = 600;
color_t bg_color(255,255,255);
pen_t current_pen(*(new color_t(255,0,0)),3.0f,bg_color);
fill_t current_fill(*(new color_t(0,0,255)),*(new color_t(0,255,0)),*(new color_t(0,0,255)));
bool fill_view=false;
canvas_t current_canvas(window_width,window_height,bg_color);
bool drawing_lines=false;
bool drawing_polygon=false;
std::string current_op="points";
std::vector<point_t> input_storage;


void print_string(float x, float y, float z, void *font, color_t c=*(new color_t(255,255,255)), std::string str="") 
{  
  glColor3f(((float)c.getRed())/(float)255, ((float)c.getGreen())/(float)255, ((float)c.getBlue())/(float)255);
  glRasterPos3f(x, y,z);
  for (int i=0; i <= str.length(); i++) 
    {
      glutBitmapCharacter(font, str[i]);
    }
}


void swap (float &x,float &y){float temp=x;x=y;y=temp;}
void add_pixels(float x0, float y0, float x1, float y1){
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
    	if (steep) {
    		point_t p((int)y,(int)x,current_pen.get_line_width(),current_pen.get_draw_color());
    		current_canvas.pixel_array[(int)y][(int)x]=current_pen.get_draw_color();
		}
  		else {
  			point_t p((int)x,(int)y,current_pen.get_line_width(),current_pen.get_draw_color());
  			current_canvas.pixel_array[(int)x][(int)y]=current_pen.get_draw_color();
		}
  		error = error + deltaerr;
  		if (error >= 0.5) {y = y + ystep;error = error - 1.0;}
   	}
}


void display( void )
{
    
    glClear( GL_COLOR_BUFFER_BIT );    
    
    /*
    point_t p4(150.0f, 180.0f, 4.0f, *(new color_t(255,0,0)));
    point_t p5(150.0f, 310.0f, 4.0f, *(new color_t(255,0,0)));
    point_t p6(220.0f, 220.0f, 4.0f, *(new color_t(255,0,0)));
    point_t p7(280.0f, 280.0f, 4.0f, *(new color_t(255,0,0)));
    point_t p(250.0f, 250.0f, 4.0f, *(new color_t(255,0,0)));
    point_t p2(350.0f, 270.0f, 4.0f, *(new color_t(255,0,0)));
    point_t p3(270.0f, 350.0f, 4.0f, *(new color_t(255,0,0)));
    line_t l(p, p2, 4.0f, *(new color_t(255,0,0)));
    line_t l2(p2, p3, 4.0f, *(new color_t(255,0,0)));
    line_t l3(p3, p, 4.0f, *(new color_t(255,0,0)));
    line_t l4(p6, p7, 4.0f, *(new color_t(0,0,255)));
    
    std::vector<point_t> v = *(new std::vector<point_t>);
    v.push_back(p); v.push_back(p2); v.push_back(p3);
    polygon_t poly(v, *(new color_t(0,255,0)), *(new color_t(0,0,255)), *(new color_t(255,0,0)),2.0f);
    
    
    c.current_drawing.insert_point(p4);
    c.current_drawing.insert_point(p5);
    c.current_drawing.insert_line(l4);
    c.current_drawing.insert_polygon(poly);
    c.current_drawing.draw();
    */
    
    if(!fill_view){
    if(current_op=="lines"){
    	for(int i=0;i<input_storage.size();i++){
    		input_storage.at(i).draw();
    	}
    }
    else if(current_op=="polygon"){
    	if(input_storage.size()>1){
    		for(int i=0;i<input_storage.size()-1;i++){
    			line_t l(input_storage.at(i), input_storage.at(i+1), current_pen.get_line_width(), current_pen.get_draw_color());
    			l.draw();
    		}
		}
		else if(input_storage.size()==1){
			input_storage.at(0).draw();
		}
    }
    current_canvas.current_drawing.draw();    
    }
    else{
    //if(fill_view){
	    for(int i=1;i<window_width-1;i++){
    		for(int j=1;j<window_height-1;j++){
    			point_t p((float)i,(float)j,(float)4.0f,current_canvas.pixel_array[i+1][j]);
    			point_t p2((float)i+1,(float)j,(float)4.0f,current_canvas.pixel_array[i][j]);
    			line_t l(p,p2,4.0,current_canvas.pixel_array[i][j]);
    			//current_canvas.current_drawing.insert_point(p);
    			//p.draw();
    			l.draw();
    		}
    	}
	}
	current_canvas.current_drawing.draw();   
    //}
    
    
    if(!fill_view){
    	print_string(window_width/2-30,10, 0 , GLUT_BITMAP_HELVETICA_12, *(new color_t(255-bg_color.getRed(),255-bg_color.getGreen(),255-bg_color.getRed())), "Drawing Mode");
    	print_string(5,window_height/2, 0 , GLUT_BITMAP_HELVETICA_12, *(new color_t(255-bg_color.getRed(),255-bg_color.getGreen(),255-bg_color.getRed())), "PEN");
		point_t p(7,window_height/2-20,current_pen.get_line_width(),current_pen.get_draw_color()); //p.draw();
		point_t p2(30,window_height/2-20,current_pen.get_line_width(),current_pen.get_draw_color()); //p.draw();
		line_t l(p,p2,current_pen.get_line_width(),current_pen.get_draw_color()); l.draw();
    	}
    
    else{
    	print_string(window_width/2-30, 10, 0, GLUT_BITMAP_HELVETICA_12, *(new color_t(255-bg_color.getRed(),255-bg_color.getGreen(),255-bg_color.getRed())), "Filling Mode");
    	
    	print_string(5,window_height/2, 0 , GLUT_BITMAP_HELVETICA_12, *(new color_t(255-bg_color.getRed(),255-bg_color.getGreen(),255-bg_color.getRed())), "FILL");
    	
		point_t p(7,window_height/2-20,current_pen.get_line_width(),current_fill.get_sfc()); //p.draw();
		point_t p2(30,window_height/2-20,current_pen.get_line_width(),current_fill.get_sfc()); //p.draw();
		line_t l(p,p2,current_pen.get_line_width(),current_fill.get_sfc()); l.draw();
		
		point_t p3(7,window_height/2-30,current_pen.get_line_width(),current_fill.get_cfc1()); //p.draw();
		point_t p4(30,window_height/2-30,current_pen.get_line_width(),current_fill.get_cfc1()); //p.draw();
		line_t l2(p3,p4,current_pen.get_line_width(),current_fill.get_cfc1()); l2.draw();
		
		point_t p5(7,window_height/2-40,current_pen.get_line_width(),current_fill.get_cfc2()); //p.draw();
		point_t p6(30,window_height/2-40,current_pen.get_line_width(),current_fill.get_cfc2()); //p.draw();
		line_t l3(p5,p6,current_pen.get_line_width(),current_fill.get_cfc2()); l3.draw();
		
		
    	}
    
    
    glutSwapBuffers();
    
}

void reshape( int w, int h )
{
    if( h == 0 )h = 1;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glOrtho( 0, (float)w, 0, (float)h, -1., 1. );
    glViewport( 0, 0, w, h );

    window_width = w;
    window_height = h;

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) 
{
    switch(key) {
    	case 27: 
        	exit(0);
        	break;
    	case 49:
    		if(!fill_view&&current_op=="points"){
    			drawing_lines=true;
    			current_op="lines";
    		}
    		else if(!fill_view&&current_op=="lines"){
    			drawing_lines=false;
    			current_op="points";
    			if(input_storage.size()>1){
    				current_canvas.current_drawing.insert_point(input_storage.at(0));
    			}
    			input_storage.clear();
    			glutPostRedisplay();
			}
    		break;
		case 50:
			if(!fill_view&&current_op=="points"){
    			drawing_polygon=true;
    			current_op="polygon";
    		}
    		else if(!fill_view&&current_op=="polygon"){
    			drawing_polygon=false;
    			current_op="points";
    			polygon_t poly(input_storage, current_pen.get_draw_color(), current_pen.get_draw_color(), current_pen.get_draw_color(), current_pen.get_line_width());
    			current_canvas.current_drawing.insert_polygon(poly);
    			if(input_storage.size()>1){
    				for(int i=0;i<input_storage.size()-1;i++){
    					add_pixels(input_storage.at(i).get_x(), input_storage.at(i).get_y(), input_storage.at(i+1).get_x(), input_storage.at(i+1).get_y());
    				}
    					add_pixels(input_storage.at(0).get_x(), input_storage.at(0).get_y(), input_storage.at(input_storage.size()-1).get_x(), input_storage.at(input_storage.size()-1).get_y());
    			}
    			input_storage.clear();
    			glutPostRedisplay();
			}
    		break;
		case 70:
		case 102:
			fill_view=!fill_view;
			glutPostRedisplay();
			break;
		case 67:
		case 99:
			if(!fill_view){
				//take in pen attributes
				int r,g,b; float w;
				std::cin>>r>>g>>b>>w;
				current_pen.set_pen_color(*(new color_t(r,g,b)));
				current_pen.set_line_width(w);
				glutPostRedisplay();
			}
			else {
				int r,g,b,r1,g1,b1,r2,g2,b2;
				std::cin>>r>>g>>b>>r1>>g1>>b1>>r2>>g2>>b2;
				current_fill.set_sfc(*(new color_t(r,g,b)));
				current_fill.set_cfc1(*(new color_t(r1,g1,b1)));
				current_fill.set_cfc2(*(new color_t(r2,g2,b2)));
				glutPostRedisplay();
				//take in fill attributes 
			}
			break;
		case 110:
		case 78:
			//delete &current_canvas;
			current_canvas.clear();
			glutPostRedisplay();
			break;
		case 68:
		case 100:
			//delete current_drawing
			current_canvas.current_drawing.clear();
			glutPostRedisplay();
			break;
		case 115:
		case 83:
			//save canvas
			break;
		case 76:
		case 108:
			//load canvas
			break;
    }
}

void mouse(int button, int state, int x, int y) 
{
   if (state == GLUT_DOWN) 
     {
       if (button == GLUT_LEFT_BUTTON) {
	   		if (!fill_view&&current_op=="points" ){
	   			point_t p((float)x,(float)window_height-y,current_pen.get_line_width(),current_pen.get_draw_color());
	   			current_canvas.current_drawing.insert_point(p);
	   			current_canvas.pixel_array[x][window_height-y]=current_pen.get_draw_color();
	   		}
	   		else if(!fill_view&&current_op=="lines"){
	   			point_t p((float)x,(float)window_height-y,current_pen.get_line_width(),current_pen.get_draw_color());
	   			if(input_storage.size()%2==0){
	   				input_storage.push_back(p);
	   			}
	   			else{
	   				point_t p2 = input_storage.at(input_storage.size()-1);
	   				line_t l(p,p2,current_pen.get_line_width(),current_pen.get_draw_color());
	   				current_canvas.current_drawing.insert_line(l);
	   				input_storage.pop_back();
	   				add_pixels(p.get_x(),p.get_y(),p2.get_x(),p2.get_y());
	   			}
	   		}
	   		else if(!fill_view&&current_op=="polygon"){
	   			point_t p((float)x,(float)window_height-y,current_pen.get_line_width(),current_pen.get_draw_color());
	   			input_storage.push_back(p);
	   		}
	   		else if(fill_view){
	   			//current_fill.set_cfm(true);
	   			current_fill.draw(current_canvas.pixel_array, x+7, window_height-y+7, window_width, window_height);
	   		}
	   }
     }
   glutPostRedisplay();
}

int main (int argc, char *argv[]) 
{
    //initializing a window with width and height as specified
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowSize( window_width, window_height );	
    glutCreateWindow( "Assignment1" );
    //clearing window with black pixels
    glClearColor((float)bg_color.getRed()/(float)255, (float)bg_color.getGreen()/(float)255, (float)bg_color.getBlue()/(float)255, 1.0f);
	//attaching handlers
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
 	
    glutMainLoop();
}


//----------WHATS LEFT-----------//
//checker filling - contact revent
//saving and loading canvas
//clearing canvas and drawing
//report
//publishing at /~

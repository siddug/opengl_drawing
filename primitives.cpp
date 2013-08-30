#include <cstdlib>
#include <iostream>
#include <string>
#include <GL/glut.h>

int win_width = 512;
int win_height = 512;

bool wire=false;


//OpenGL Primitives
unsigned int primitives[]=
{
  GL_POINTS,
  GL_LINES,
  GL_LINE_LOOP,
  GL_LINE_STRIP,

  GL_TRIANGLES,
  GL_TRIANGLE_STRIP,
  GL_TRIANGLE_FAN,
  
  GL_QUADS,
  GL_QUAD_STRIP,

  GL_POLYGON
};

std::string str_primitives[]=
{
  "Points",
  "Lines",
  "Line Loop",
  "Line Strip",

  "Triangles",
  "Triangle Strip",
  "Triangle Fan",

  "Quads",
  "Quad Strip",

  "Polygon",
};

int prim_id=0;
int numprims = sizeof(primitives)/sizeof(unsigned int);

void render_bitmap_string(float x, float y, float z, void *font, const char *string) 
{  
  const char *c;
  glRasterPos3f(x, y,z);
  for (c=string; *c != '\0'; c++) 
    {
      glutBitmapCharacter(font, *c);
    }
}

void display( void )
{
  glClear( GL_COLOR_BUFFER_BIT );

  unsigned int p = primitives[prim_id];

  if ( p == GL_POINTS ) 
    glPointSize(4.0f);
  
  else if ((p == GL_LINES) || (p == GL_LINE_STRIP) || (p == GL_LINE_LOOP))
    glLineWidth(4.0f);

  else 
    {
      if ( wire ) 
	{
	  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
	  glColor3f(1.0, 0.0, 0.0);
	  render_bitmap_string(2.0f,-3.5, 0, GLUT_BITMAP_HELVETICA_18, "Wireframe"); 
	}
      else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

  glColor3f(0.0, 1.0, 0.0);
  glBegin(primitives[prim_id]);
    glVertex2f(-2.0, 2.0);
    glVertex2f(2.0, 2.0);
    glVertex2f(3.0, 0.0);
    glVertex2f(2.0, -2.0);
    glVertex2f(-2.0, -2.0);
  glEnd();

  render_bitmap_string(-3.0f,-3.0, 0, GLUT_BITMAP_HELVETICA_18, str_primitives[prim_id].c_str()); 
  glutSwapBuffers();
}

void reshape( int w, int h )
{
  if  ( h == 0 ) h = 1;

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  glOrtho( -4.0, 4.0, -4.0, 4.0, -1., 1. );
  glViewport( 0, 0, w, h );

  win_width = w;
  win_height = h;

  glutPostRedisplay();
}

void keyboard( unsigned char key, int x, int y ) 
{
  switch(key) {
  case 27: 
    exit(0);
    break;
  case ' ':
    prim_id = (prim_id + 1) % numprims;
    glutPostRedisplay();
    break;
  case 'w':
    wire = !wire;
    glutPostRedisplay();
    break;
  }
}

int main (int argc, char *argv[]) 
{

  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
  glutInitWindowSize( win_width, win_height );

  glutCreateWindow( "OpenGL Primitives" );

  prim_id=0;
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glutDisplayFunc( display );
  glutReshapeFunc( reshape );
  glutKeyboardFunc( keyboard );
 
  glutMainLoop();
}

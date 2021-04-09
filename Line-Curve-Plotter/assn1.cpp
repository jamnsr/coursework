#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>   // The GL Utility Toolkit (Glut) Header

#define WIDTH 500
#define HEIGHT 500


#include <vector>
#include <math.h>
#include <stdlib.h>
#include <algorithm>

int x_last,y_last;
int MODE = 0;
int numClicks = 0;


struct Point {
  double x;
  double y;
  double r;
  double g;
  double b;
  Point(double initX, double initY, double initR, double initG, double initB){
    x = initX;
    y = initY;
    r = initR;
    g = initG;
    b = initB;
  }
  Point(double initX, double initY){
    x = initX;
    y = initY;
    r = 1.0;
    g = 1.0;
    b = 1.0;
  }
};

std::vector<Point> frameBuffer;
std::vector<Point> lineCords;
std::vector<Point> curveCords;

/***************************************************************************/

void init_window()
                 /* Clear the image area, and set up the coordinate system */
{

        					       /* Clear the window */
        glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_SMOOTH);
        glOrtho(0,WIDTH,0,HEIGHT,-1.0,1.0);
}

/***************************************************************************/

void write_pixel(int x, int y, double r, double g, double b)
                                         /* Turn on the pixel found at x,y */
{

        glColor3f (r, g, b);                 
        glBegin(GL_POINTS);
           glVertex3i( x, y, 0);
        glEnd();	
}

//***************************************************************************/

void display ( void )   // Create The Display Function
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	      // Clear Screen 

  for(Point p : frameBuffer){
	  write_pixel(p.x, p.y, p.r, p.g, p.b);
  }


  glutSwapBuffers();                                      // Draw Frame Buffer 
}
/***************************************************************************/



/***************************************************************************/
Point evaluateBezier(std::vector<Point>& ctrlPts, double t)
{
  // Takes in a vector of 4 control points and evaluates the curve:
  // B(t) = (1-t)^3 P0 + 3t(1-t)^2 P1 + 3(1-t)t^2 P2 + t^3 P3, 0 <= t <= 1
  
  double x = (pow((1-t), 3) * ctrlPts[0].x) + ((3 * t) * pow((1-t), 2) * ctrlPts[1].x) + 
                                  (3 * (1-t) * pow(t, 2) * ctrlPts[2].x) + (pow(t, 3) * ctrlPts[3].x);
  
  double y = (pow((1-t), 3) * ctrlPts[0].y) + ((3 * t) * pow((1-t), 2) * ctrlPts[1].y) + 
                                  (3 * (1-t) * pow(t, 2) * ctrlPts[2].y) + (pow(t, 3) * ctrlPts[3].y);


  // Linear interpolation of colors between the first and fourth control point
  double r = curveCords[0].r * (1.0 - t) + curveCords[3].r * t;
  double g = curveCords[0].g * (1.0 - t) + curveCords[3].g * t;
  double b = curveCords[0].b * (1.0 - t) + curveCords[3].b * t;

  return Point(x, y, r, g, b);

}

/***************************************************************************/
bool sortX (Point i, Point j) { return (i.x < j.x); }
bool sortY (Point i, Point j) { return (i.y < j.y); }

void drawLine(std::vector<Point>& p)
{
  //Takes in two points passed in by reference and draws a line between them
  //based on the DDA algorithm. Color is interpolated linearly.
  
  //Calculate slope: m = (y2 - y1)/(x2 - x1)
  //Linear interpolation: interpolatedColor = p1.color * (1.0 - u) + p2 * u;

  double m = (p[1].y - p[0].y) / (double)(p[1].x - p[0].x);

  double r1 = p[0].r;
  double g1 = p[0].g;
  double b1 = p[0].b;

  double r2 = p[1].r;
  double g2 = p[1].g;
  double b2 = p[1].b;

  if(m < 1.0 && m > -1.0){
    std::sort(p.begin(), p.end(), sortX);
    int x = p[0].x;
    double y = p[0].y;
    while(x <= p[1].x){
      double u = (x - p[0].x) / (p[1].x - p[0].x);
      double red = r1 * (1.0 - u) + r2 * u;
      double green = g1 * (1.0 - u) + g2 * u;
      double blue = b1 * (1.0 - u) + b2 * u;
      //printf("slope is %f, u is %f, r: %g, g: %f, b: %f\n", m, u, red, green, blue);
      frameBuffer.push_back(Point(x, round(y), red, green, blue)); 
      x = x + 1;
      y += m;
    }
  } else{
    std::sort(p.begin(), p.end(), sortY);
    double x = p[0].x;
    int y = p[0].y;
    while(y <= p[1].y){
      double u = (y - p[0].y) / (p[1].y - p[0].y);
      double red = r1 * (1.0 - u) + r2 * u;
      double green = g1 * (1.0 - u) + g2 * u;
      double blue = b1 * (1.0 - u) + b2 * u;
      frameBuffer.push_back(Point(round(x), y, red, green, blue)); 
      y = y + 1;
      x += 1/m;
    }
  }


}


/***************************************************************************/

void drawCurve(std::vector<Point>& p){

  //Rearrange points to always go from left to right or bottom to top
  if(p[0].x > p[3].x || p[0].y > p[3].y)
    std::reverse(p.begin(), p.end());

  //Initialize first point with correct color and coordinates
  Point first = evaluateBezier(curveCords, 0.0);

  //Polyline approximation of the curve using step size .025
  for(double u = 0.025; u <= 1.0; u += 0.025){

    Point nextP = evaluateBezier(curveCords, u);

    lineCords.push_back(first);
    lineCords.push_back(nextP);
    drawLine(lineCords);
    lineCords.clear();

    first = nextP;
    first.r = nextP.r;
    first.g = nextP.g;
    first.b = nextP.b;
  }

}

/***************************************************************************/
void mouse(int button, int state, int x, int y)
{
/* This function I finessed a bit, the value of the printed x,y should
   match the screen, also it remembers where the old value was to avoid multiple
   readings from the same mouse click.  This can cause problems when trying to
   start a line or curve where the last one ended */
  static int oldx = 0;
  static int oldy = 0;
		

	int mag;

	
	y *= -1;  //align y with mouse
	y += 500; //ignore 
	mag = (oldx - x)*(oldx - x) + (oldy - y)*(oldy - y);
	if (mag > 20) {
		printf(" x,y is (%d,%d)\n", x,y);

    ++numClicks;

    // MODE 0 is for lines, MODE 1 is for curves
    // Initialize colors of each point randomly

    if(MODE == 0){
      lineCords.push_back(Point(x, y, (double)(rand()%101)/100, 
                                      (double)(rand()%101)/100, 
                                      (double)(rand()%101)/100 ));
      if(numClicks == 2){
        drawLine(lineCords);
        numClicks = 0;
        lineCords.clear();
      } 
    }
    else if(MODE == 1){
      curveCords.push_back(Point(x, y, (double)(rand()%101)/100, 
                                       (double)(rand()%101)/100, 
                                       (double)(rand()%101)/100 ));
      if(numClicks == 4){
        drawCurve(curveCords);        
        numClicks = 0;
        curveCords.clear();
      } 
    }


	}
	oldx = x;
	oldy = y;
	x_last = x;
	y_last = y;

}
 
/***************************************************************************/
void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{

	switch ( key ) {
		case 27:              // When Escape Is Pressed...
			exit ( 0 );   // Exit The Program
			break;        
    case 108:            // 'l' key pressed, reset clicks and change mode
      printf("Line mode\n");
      MODE = 0;
      numClicks = 0;
      lineCords.clear();
			break;
    case 99:             // 'c' key pressed, reset clicks and change mode
      printf("Curve mode\n");
      MODE = 1;
      numClicks = 0;
      curveCords.clear();
			break;
    case 101:             // 'e' key pressed, clear all points in frameBuffer
      printf("Clear screen\n");
      frameBuffer.clear();
			break;
		default:       
			break;
	}
}
/***************************************************************************/

int main (int argc, char *argv[])
{
/* This main function sets up the main loop of the program and continues the
   loop until the end of the data is reached.  Then the window can be closed
   using the escape key.						  */
	
	glutInit            ( &argc, argv ); 
  glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH ); 
	glutInitWindowSize  ( 500,500 ); 
	glutCreateWindow    ( "Computer Graphics" ); 
	glutDisplayFunc     ( display );  
	glutIdleFunc	    ( display );
	glutMouseFunc       ( mouse );
	glutKeyboardFunc    ( keyboard );
        					      
  init_window();				             //create_window
						       		
	glutMainLoop        ( );                 // Initialize The Main Loop
}



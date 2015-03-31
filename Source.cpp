#include <time.h>
#include <stdlib.h>
#include "D:\\Движки\freeglut-2.8.1\include\GL\freeglut.h"
#include "LogSystem.h"

int N=30,M=20;
int Scale=25;

int w = Scale*N;
int h = Scale*M;

int dir,num=4;
int Score(0);
int life(0);
bool GameOver(false);

struct 
{ int x;
  int y;}  s[100];

  struct
  {
	  int x;
	  int y;
  } lifes[2];

class Fructs
{ 
public:
	int x,y;

    void New()
    {  x=rand() % N;
        y=rand() % M;   }
	
    void DrawApple()
   {   glColor3f(0.0,1.0,0.0);
       glRectf(x*Scale,y*Scale,(x+1)*Scale,(y+1)*Scale); }

} m[10];

 void DrawSnake()
 {  
  glColor3f(0.0,0.0,1.0);
  for (int i=0;i<num;i++)
    {glRectf(s[i].x*Scale, s[i].y*Scale, (s[i].x+0.9)*Scale, (s[i].y+0.9)*Scale); }
 }

 void Tick()
 {
    for (int i=num;i>0;--i)
	 {s[i].x=s[i-1].x;
	 s[i].y=s[i-1].y;}

    if (dir==0) s[0].y+=1;      
    if (dir==1) s[0].x-=1;        
    if (dir==2) s[0].x+=1;         
    if (dir==3) s[0].y-=1;         

  for (int i=0;i<10;i++)
    if ((s[0].x==m[i].x) && (s[0].y==m[i].y)) 
      {num++; m[i].New();}
 
	//if (s[0].x>N) {   }  if (s[0].x<0) {  }

  //if (s[0].y>M) dir=3;  if (s[0].y<0) dir=0;
 
 for (int i=1;i<num;i++)
  if (s[0].x==s[i].x && s[0].y==s[i].y)  num=i;
 }
void DrawField()
  {
   glColor3f(0.0,0.7,0.0);
   glBegin(GL_LINES);

    for (int i=0; i<w; i+=Scale) 
      {
		  glVertex2f(i,0); glVertex2f(i,h);
	  }
    for (int j=0; j<h; j+=Scale)  
      {
		  glVertex2f(0,j); glVertex2f(w,j);
	  }

    glEnd();
}
void DrawScore()
{

}
void ResetGame()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
}

bool IsOutBorder()
{
	const int leftWall = 0;
	const int rightWall = 0;
	const int topWall = 500;
	const int bottomWall = 750;

	if ( s[0].x < leftWall) { return true; }


	return false;
}

void DrawLife()
{
	float StartX(350),StartY(230);
	float ScaleLife(2.0f);
	float frame(15.0f);

	lifes[0].x = StartX; lifes[0].y = StartY;
	lifes[1].x = 334; lifes[1].y = 230;
	lifes[2].x = 318; lifes[2].y = 230;


		glColor3f(1.0f,0.0f,0.0f);

		switch(life)
		{
		case 0 : GameOver = true; break;

			case 1 :
				{
					glRectf(lifes[0].x * ScaleLife, lifes[0].y * ScaleLife, ( lifes[0].x + frame) * ScaleLife, (lifes[0].y + frame) * ScaleLife ); 
					break;
				}

			case 2 : 
				{ 
					
					// clear 3 life

					ResetGame();
DrawField();
					glColor3f(1.0f,0.0f,0.0f);
					glRectf(lifes[0].x * ScaleLife, lifes[0].y * ScaleLife, ( lifes[0].x + frame) * ScaleLife, (lifes[0].y + frame) * ScaleLife ); 
                    glRectf(lifes[1].x * ScaleLife, lifes[1].y * ScaleLife, ( lifes[1].x + frame) * ScaleLife, (lifes[1].y + frame) * ScaleLife ); 

					

					break;

				}

			case 3 : 
				{ 
					glRectf(lifes[0].x * ScaleLife, lifes[0].y * ScaleLife, ( lifes[0].x + frame) * ScaleLife, (lifes[0].y + frame) * ScaleLife ); 
                    glRectf(lifes[1].x * ScaleLife, lifes[1].y * ScaleLife, ( lifes[1].x + frame) * ScaleLife, (lifes[1].y + frame) * ScaleLife ); 
                    glRectf(lifes[2].x * ScaleLife, lifes[2].y * ScaleLife, ( lifes[2].x + frame) * ScaleLife, (lifes[2].y + frame) * ScaleLife );
					
					break;
				}
		};


glRectf(lifes[0].x * ScaleLife, lifes[0].y * ScaleLife, ( lifes[0].x + frame) * ScaleLife, (lifes[0].y + frame) * ScaleLife ); 
glRectf(lifes[1].x * ScaleLife, lifes[1].y * ScaleLife, ( lifes[1].x + frame) * ScaleLife, (lifes[1].y + frame) * ScaleLife ); 
glRectf(lifes[2].x * ScaleLife, lifes[2].y * ScaleLife, ( lifes[2].x + frame) * ScaleLife, (lifes[2].y + frame) * ScaleLife ); 
			//StartX * Scale, StartY * Scale , (StartX + frame)* Scale, (StartY + frame) * Scale);
//lifes[i].x += frame;		
		
	
}

void DrawFruct()
{
for (int i=0;i<10;i++)
     m[i].DrawApple();
}

void display() 
{

	if (GameOver) { ResetGame();  }
	else
	{
	

    DrawField();
    DrawLife();
	if (IsOutBorder() ) { if (life == 0) { GameOver = true; } else life -= 1;}
    DrawSnake(); 

	DrawScore();

	
	DrawFruct();
   

  // glFlush();
  
	
	}

 glutSwapBuffers();
}

void KeyboardEvent(int key, int a, int b)
{   
    switch(key)
    {
        case 101 : 	dir=0; break;
         case 102:   dir=2; break;
        case 100 :  dir=1; break;
        case 103 :  dir=3; break;
     }
}
void getkeys_down(unsigned char key,int x,int y)
{
	switch ( key )
	{

		// нужно использовать русскую раскладку проще действительно переключить раскладку
	case 'w' : dir = 0; break; //ClearScreen(); //Data::id = 1; glutTimerFunc(Data::IntervalTimer,glutTimer,Data::id); break; 
	case 'a' : dir = 1; break; //ClearScreen(); //Data::id = 1; glutTimerFunc(Data::IntervalTimer,glutTimer,Data::id); break; 
	case 'd' : dir = 2; break; //ClearScreen(); //Data::id = 1; glutTimerFunc(Data::IntervalTimer,glutTimer,Data::id); break; 
	case 's' : dir = 3; break; 
	

	case 27  : exit(0); break;
}
}
void Mouse(int state,int button,int x,int y)
{
	using namespace LogSpace;
	CLog logFile;

	logFile<< LogSpace::color("gray") << LogSpace::color("green") << "X " << x << LogSpace::endl;
	logFile<< LogSpace::color("gray") << LogSpace::color("green") << "Y " << y << LogSpace::endl;
}

void timer(int = 0)
{
  display();

  Tick();
       
 glutTimerFunc(250,timer,0);
}

HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;
HINSTANCE hPrevInstance;

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,PSTR pCmdLine,int nShowCmd)
{
	int argc=0; char** argv=0;

	srand(time(0));
	
	for (int i=0;i<10;i++)
		m[i].New();
	
	int i(0);

	 s[i].x=10;
	 s[i].y=10;

	 life = 2;
	// GameOver = true;

glutInit(&argc, argv);
glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB );
glutInitWindowSize (w, h);
glutCreateWindow ("Test"); 

glClearColor(1.0,1.0,0.6,1.0);  //С†РІРµС‚ С„РѕРЅР°
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0,w,0,h);

glutDisplayFunc (display);
glutSpecialFunc(KeyboardEvent);
glutKeyboardFunc(getkeys_down);
glutMouseFunc(Mouse);

glutTimerFunc(250,timer,0);

glutMainLoop();
}

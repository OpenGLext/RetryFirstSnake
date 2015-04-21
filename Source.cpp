#include <time.h>
#include <stdlib.h>
#include "D:\\ƒвижки\freeglut-2.8.1\include\GL\freeglut.h"
#include "LogSystem.h"
#include "Font.h"
#include <sstream>

int N=30,M=20;
int Scale=25;

int w = Scale*N;
int h = Scale*M;

int dir(1),num = 4;
int Score(0);
HDC  hDC;
int TimeDraw(0);
int lifes(0);
int level(1);
int FructOnLevel[2]={5,7};

/* 
   ----------------- States Game --------------- 



 ------------------  States Game ----------------
 */

const int LOGO = 1;
const int GAME = 2;
const int LEVELCOMPLETE = 3;
const int GAMEOVER = 4;
const int STARTMENU = 5;
const int ENDGAME   = 6;

bool StartGame(false);
bool GameOver(false);
int  State(LOGO);

struct 
{ int x;
  int y;}  s[100];

//struct
//  {
//	  int x;
//	  int y;
//  } lifes[2];

class Fructs
{ 


public:
	int x,y;

    void New()
    {   x=rand() % N;
        y=rand() % M;  

		if ( x == 550 && y == 485) { this->New(); }
		if ( x == 550 && y == 460) { this->New(); }
		if ( x == 550 && y == 435) { this->New(); }
		if ( x == 550 && y == 410) { this->New(); }
		
		/* добавить чуть больше к х и у что бы до кра€ правого экрана не рисовались фрукты и перед строками где то на один два кубика */

		/* координаты с которыми надо сверить если совпадают то заново дергать метод нью
		     550, 485
550, 460
550, 435
550, 410, 
		*/
	}
	
    void DrawApple()
   {   glColor3f(0.0,1.0,0.0);
       glRectf(x*Scale,y*Scale,(x+1)*Scale,(y+1)*Scale); }

} m[10];

inline void CorectFrustPosition()
{
	for(int i=0; i<10; i++)
		if ( m[i].x == (m[i+1].x + Scale) || m[i].y == ( m[i+1].y + Scale) ) { m[i+1].New(); }
}

void Tick()
 {
    for (int i = num; i>0; --i)
	 {
		 s[i].x = s[i-1].x;
	     s[i].y = s[i-1].y;
	}

	//CorectFrustPosition();

    if (dir==0) s[0].y+=1;      
    if (dir==1) s[0].x-=1;        
    if (dir==2) s[0].x+=1;         
    if (dir==3) s[0].y-=1;         

  for (int i=0;i<10;i++)
    if ((s[0].x == m[i].x) && ( s[0].y == m[i].y)) 
      {
		  num++;
		  Score += 100;
		  m[i].New();
	  }
 
	//if (s[0].x>N) {   }  if (s[0].x<0) {  }

  //if (s[0].y>M) dir=3;  if (s[0].y<0) dir=0;
 
	/* если столкнулись голова и хвост */
 for (int i=1;i<num;i++)
  if (s[0].x==s[i].x && s[0].y==s[i].y)  num=4;
 }
void DrawSnake()
 {  
	 Tick();

	 glColor4f(1.0f,1.0f,0.0f,0.9f);
     glColor4f(1.0f,0.0f,0.0f,0.4f);

  for (int i=0;i<num;i++)
    {
		glRectf(s[i].x * Scale, s[i].y * Scale, (s[i].x + 0.9) * Scale, ( s[i].y + 0.9) * Scale);
    }
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
	glClearColor(0.0f,0.0f,0.5f,0.2f);
}
bool IsOutBorder()
{
	const int leftWall   = 0;
	const int rightWall  = 30;
	const int topWall    = 20;
	const int bottomWall = 0;

	if ( s[0].x < leftWall   ) 
	{ 
		dir = 2;
		return true;
	}
	if ( s[0].x > rightWall  )  
	{ 
		dir = 1;
		return true;
	}
	if ( s[0].y > topWall    ) 
	{ 
		dir = 3;
		return true; 
	}
	if ( s[0].y < bottomWall ) 
	{
		dir = 0;
		return true;
	}

	return false;
}
std::string GetStr(const char* mess,const float value,const int valueInt=0)
{
	std::string ScoreFloat="";
	std::stringstream StrStream;

	StrStream<<value;
	StrStream>>ScoreFloat;
	ScoreFloat = mess + ScoreFloat ;
	 
	return ScoreFloat;
}
void DrawLife(const int life)
{
	float StartX(350),StartY(230);
	float ScaleLife(2.0f);
	float frame(15.0f);

		glColor3f(1.0f,0.0f,0.0f);

		/*-------------------
	       длина тела черв€
	       ------------------*/
	Font *ourtext = new Font(hDC,"times",10,15,30);
	
     glColor4f(1.0f,1.0f,0.3f,0.9f);

	 std::string len = GetStr("Body Snake: ",num);
	
	 ourtext->put(550, 485, 1.0f, len.c_str());

	 /*-------------------
	              уровень
	       ------------------*/
	  glColor4f(1.0f,1.0f,0.3f,0.9f);

	 std::string lev = GetStr("Stage: ",level);
	
	 ourtext->put(550, 460, 1.0f, lev.c_str());

	 
		/*-------------------
	               очки
	       ------------------*/
	  glColor4f(1.0f,1.0f,0.3f,0.9f);

	 std::string score = GetStr("Score: ",Score);
	
	 ourtext->put(550, 435, 1.0f, score.c_str());

	      /*-------------------
	               жизни
	       ------------------*/
	  glColor4f(1.0f,1.0f,0.3f,0.9f);

	 std::string life_ = GetStr("Life: ",life);
	
	 ourtext->put(550, 410, 1.0f, life_.c_str());

	 
     delete ourtext;

		//switch(life)
		//{

		//case 0 : GameOver = true; break;

		//	case 1 :
		//		{
		//			glRectf(lifes[0].x * ScaleLife, lifes[0].y * ScaleLife, ( lifes[0].x + frame) * ScaleLife, (lifes[0].y + frame) * ScaleLife ); 
		//			break;
		//		}

		//	case 2 : 
		//		{ 
		//			
		//			// clear 3 life

		//			//ResetGame();
  //                  //DrawField();
		//			glColor3f(1.0f,0.0f,0.0f);
		//			glRectf(lifes[0].x * ScaleLife, lifes[0].y * ScaleLife, ( lifes[0].x + frame) * ScaleLife, (lifes[0].y + frame) * ScaleLife ); 
  //                  glRectf(lifes[1].x * ScaleLife, lifes[1].y * ScaleLife, ( lifes[1].x + frame) * ScaleLife, (lifes[1].y + frame) * ScaleLife ); 

		//			break;

		//		}

		//	case 3 : 
		//		{ 
		//			glRectf(lifes[0].x * ScaleLife, lifes[0].y * ScaleLife, ( lifes[0].x + frame) * ScaleLife, (lifes[0].y + frame) * ScaleLife ); 
  //                  glRectf(lifes[1].x * ScaleLife, lifes[1].y * ScaleLife, ( lifes[1].x + frame) * ScaleLife, (lifes[1].y + frame) * ScaleLife ); 
  //                  glRectf(lifes[2].x * ScaleLife, lifes[2].y * ScaleLife, ( lifes[2].x + frame) * ScaleLife, (lifes[2].y + frame) * ScaleLife );
		//			
		//			break;
		//		}
		//};	
}
void DrawFruct()
{
for (int i=0;i<10;i++)
     m[i].DrawApple();
}
void ShowLogo()
{
}
void ShowGameOver()
{
	Font *ourtext = new Font(hDC,"times",15,25,30);
	
     glColor4f(1.0f,0.0f,0.0f,1.0f);
	
     ourtext->put(290, 370, 1.0f, "Game Over...");

	 

	 //glutSwapBuffers();
	 
     delete ourtext;
}
inline GLvoid box(float x1, float y1, float x2, float y2)
{
	glBegin(GL_QUADS);	
        	glTexCoord2f(0.0f, 0.0f); glVertex2f(x1,y1);
			glTexCoord2f(1.0f, 0.0f); glVertex2f(x2,y1);
			glTexCoord2f(1.0f, 1.0f); glVertex2f(x2,y2);
			glTexCoord2f(0.0f, 1.0f); glVertex2f(x1,y2);
			
	glEnd();
}
void ShowMenu()
{
	glEnable(GL_BLEND);
	float FonMenuX(200.0f),FonMenuY(90.0f),FonMenuX2(550.0f),FonMenuY2(450.0f);
	float WidthMenu(350.0f);
	float HeightMenu(360.0f);
	float StartButtonX(220.0f); float StartButtonY(350.0f); float StartButtonX2(530.0f); float StartButtonY2(400.0f);
	float WidthButtonStart(310.0f); float HeightButtonStart(50.0f);

    	/*-------------------
	       фон рамка меню
	       ------------------*/
	glColor4f(0.5f,0.5f,0.5f,0.5f);
	glRectf(FonMenuX, FonMenuY, FonMenuX + WidthMenu, FonMenuY + HeightMenu);

	/*-------------------
	       кнопка старт
	       ------------------*/

	glColor4f(0.0f,1.0f,0.0f,0.3f);
	glRectf(StartButtonX, StartButtonY, StartButtonX + WidthButtonStart, StartButtonY + HeightButtonStart); 

	/*-------------------
	       кнопка старт
	       ------------------*/


	/*-------------------
	       текст дл€ кнопки старт
	       ------------------*/
	Font *ourtext = new Font(hDC,"times",15,25,30);
	
     glColor4f(0.0f,0.0f,0.3f,0.9f);
	
     ourtext->put(290, 370, 1.0f, "Start Game");
	 
     delete ourtext;
}
bool TargetInButton(int x, int y)
{
	float xmin(220.0f); float xmax(530.0f); float ymin(350.0f); float ymax(400.0f);

	if ( x >= xmin && x <= xmax) 
		{
			if ( ((y+260.0f)  >= ymin) && ((y +260.0f) <= ymax))
			{
               return true;
			}
	}

	return false;
}
void ShowHappyAllLevels()
{
	Font *ourtext = new Font(hDC,"times",15,25,30);
	
     glColor4f(1.0f,0.0f,0.0f,1.0f);
	
     ourtext->put(290, 370, 1.0f, "ѕоздравл€ем вы прошли все уровни!!! ,ну ты чувак даешь рекордсмен ))) ...");

	 

	 //glutSwapBuffers();
	 
     delete ourtext;
}
bool IsLevelComplete()
{
	if ( (num - 4) == FructOnLevel[0]  )
	{
      // State = LEVELCOMPLETE;
	   level += 1;
	   FructOnLevel[0] = 7;
	   TimeDraw = 10;
       return true;
	   
	}

	return false;
}
void display() 
{
	using namespace LogSpace;
	CLog logFile;
	

	ResetGame();

	/*if (State == GameOver) { ResetGame();  State = GAMEOVER;  }
	else
	{*/

	IsLevelComplete();

	if (IsOutBorder())
	{ 
		if (lifes == 0)
		{ 
			State = GAMEOVER; ResetGame(); ShowGameOver(); 
		} 
		else 
         lifes -= 1;	
	} 
//DrawField();
			DrawLife(lifes);
            DrawSnake(); 
	        DrawFruct();
 
 glutSwapBuffers();
}
void ProcessStates()
{
	switch (State)
	{
	case LOGO :      ShowLogo();     break;
	//case GAME :      display();      break;
	//case GAMEOVER :  ShowGameOver(); break;
	case STARTMENU : ShowMenu();     break;
	
	}

	glutSwapBuffers();
}
//void KeyboardEvent(int key, int a, int b)
//{   
//    switch(key)
//    {
//        case 101 : 	dir=0; break;
//        case 102:   dir=2; break;
//        case 100 :  dir=1; break;
//        case 103 :  dir=3; break;
//     }
//}
void getkeys_down(unsigned char key,int x,int y)
{
	switch ( key )
	{

		// нужно использовать русскую раскладку проще действительно переключить раскладку
	case 'w' : dir = 0; break; //ClearScreen(); //Data::id = 1; glutTimerFunc(Data::IntervalTimer,glutTimer,Data::id); break; 
	case 'a' : dir = 1; break; //ClearScreen(); //Data::id = 1; glutTimerFunc(Data::IntervalTimer,glutTimer,Data::id); break; 
	case 'd' : dir = 2; break; //ClearScreen(); //Data::id = 1; glutTimerFunc(Data::IntervalTimer,glutTimer,Data::id); break; 
	case 's' : dir = 3; break; 
	case 'g' : State = GAME; break;
	case '1' : glBlendFunc(GL_SRC_ALPHA, GL_ONE); break;
	case '2' : glBlendFunc(GL_ONE, GL_ONE); break;
	case '3' : glBlendFunc(GL_DST_COLOR, GL_ZERO); break;
	case '4' : glBlendFunc(GL_SRC_COLOR, GL_ONE); break;
	case '5' : glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE); break;
    case 'b' : glEnable(GL_BLEND); glBlendFunc(GL_ZERO,  GL_SRC_ALPHA_SATURATE); break;

	case 27  : State = STARTMENU; ResetGame(); lifes = 3; break;  //exit(0); break;
}
}
void Mouse(int state,int button,int x,int y)
{
	using namespace LogSpace;
	CLog logFile;

	if ( button == GLUT_LEFT_BUTTON  && state == GLUT_DOWN)
	{
      if (TargetInButton(x, y))
	{
                    // logFile<< LogSpace::color("gray") << LogSpace::color("green") << "Is target in button!!! " <<"x "<< x<<"y "<<y << LogSpace::endl;
			  
		State = GAME;
	}

	}

	
}
void Drawtimer(int = 0)
{

	if (State == GAME )
	{
       display();
	}

	if ( State == GAMEOVER)
	{
		ShowGameOver();
	}

	if ( State == LEVELCOMPLETE)
	{
	
		State = GAME;
	}

  
 glutTimerFunc(TimeDraw,Drawtimer,0);
}
void StateTimer(int = 0 )
{
	ProcessStates();
	glutTimerFunc(0,StateTimer,0);
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

	 State = STARTMENU;
	 lifes = 3;
	 TimeDraw = 150;

	
	// GameOver = true;

glutInit(&argc, argv);
glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_RGB );
glutInitWindowSize (w, h);
glutCreateWindow ("Test"); 
hWnd = FindWindow(L"GLUT",L"OpenGL Application");
hDC = GetDC(hWnd);

glClearColor(1.0,1.0,0.6,1.0);  
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0,w,0,h);

//glutDisplayFunc (display);
//glutSpecialFunc(KeyboardEvent);
glutKeyboardFunc(getkeys_down);
glutMouseFunc(Mouse);

glutTimerFunc(TimeDraw,Drawtimer,0);
glutTimerFunc(0,StateTimer,0);
//glutIdleFunc(ProcessStates);

glutMainLoop();
}

/**********************************************************************
 * LM Simulator
 **********************************************************************/

#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"
using namespace std;

/*************************************************************************
 * Game
 *************************************************************************/
class Game
{
public:
   Game(const Point& ptUpperRight) :
          angle(0.0),
          ptLM(ptUpperRight.getX() / 2.0, ptUpperRight.getY() / 2.0),
          ground(ptUpperRight)
   { 

      phase = random(0, 255);
   }

   // this is just for test purposes.  Don't make member variables public!
   Point ptLM;           // location of the LM on the screen
   Point ptUpperRight;   // size of the screen
   double angle;         // angle the LM is pointing
   unsigned char phase;  // phase of the star's blinking
   Ground ground;
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface *pUI, void * p)
{
   ogstream gout;

   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Game * pGame = (Game *)p;  

   // move the ship around
   if (pUI->isRight())
      pGame->ptLM.addX(-1.0);
   if (pUI->isLeft())
      pGame->ptLM.addX(1.0);
   if (pUI->isUp())
      pGame->ptLM.addY(-1.0);
   if (pUI->isDown())
      pGame->ptLM.addY(1.0);

   // draw the ground
   pGame->ground.draw(gout);

   // draw the lander and its flames
   gout.drawLander(pGame->ptLM /*position*/, pGame->angle /*angle*/);
   gout.drawLanderFlames(pGame->ptLM, pGame->angle, /*angle*/
                    pUI->isDown(), pUI->isLeft(), pUI->isRight());

   // put some text on the screen
   gout.setPosition(Point(30.0, 30.0));
   gout << "Game (" << (int)pGame->ptLM.getX() << ", " << (int)pGame->ptLM.getY() << ")" << "\n";

   // draw our little star
   gout.drawStar(pGame->ptStar, pGame->phase++);
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my Game type and call the display engine.
 * That is all!
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance, 
   _In_opt_ HINSTANCE hPrevInstance, 
   _In_ PWSTR pCmdLine, 
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char ** argv)
#endif // !_WIN32
{
   // Initialize OpenGL
   Point ptUpperRight(400.0, 400.0);
   Interface ui(0, NULL, 
                "Open GL Game", 
                 ptUpperRight);

   // Initialize the game class
   Game game(ptUpperRight);

   // set everything into action
   ui.run(callBack, &game);             

   return 0;
}

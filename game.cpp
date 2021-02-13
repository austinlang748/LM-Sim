/**********************************************************************
 * LM Simulator
 **********************************************************************/

#include <vector>

#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"
#include "LM.h"
#include "star.h"

const double SCREEN_WIDTH  = 400.0;
const double SCREEN_HEIGHT = 400.0;
const int    STARS_AMOUNT  = 100;

using namespace std;

/*************************************************************************
 * Game
 *************************************************************************/
class Game
{
public:
   Game(const Point& ptUpperRight) :
         lm(ptUpperRight),
         ground(ptUpperRight),
         restart(false),
         pause(false),
         pauseButtonTimer(0)
   {
      // create stars to be put on the screen
      for (int i = 0; i < STARS_AMOUNT; i++)
         stars.push_back(Star());
      
      // initialize points
      textBottomLeft = Point(10, 20);
      
      textBottomRight = Point(ptUpperRight.getX() - 80, 20);
      
      textTopLeft = Point(10, ptUpperRight.getY() - 20);
      
      textTopRight = Point(
         ptUpperRight.getX() - 80,
         ptUpperRight.getY() - 20
      );
      
      textCenter = Point(
         ptUpperRight.getX()/2 - 40,
         ptUpperRight.getY()/2
      );
      
      textBottomCenter = Point(textCenter.getX(), 20);

      textTopCenter = Point(
         textCenter.getX(),
         ptUpperRight.getY() - 20
      );
   }
    
   void update()
   {
      cout << pause << endl;
      if (!pause) {
         // update lunar module
         lm.update();
      }

      // update stars phases
      for (int i = 0; i < STARS_AMOUNT; i++)
         stars[i].update();
   
      // check for collisions
      checkCollisions();
   }

   void handleInput(const Interface *pUI)
   {
      // handle lunar module input
      if (!pause) lm.handleInput(pUI);
      
      // pause/resume game
      if (pUI->getHeldKey(SPACE) && pauseButtonTimer <= 0)
      {
         pause = !pause;         // toggle pause/resume
         pauseButtonTimer = 40;  // delay 2/3s of a second
      }
      
      // update pause button timer
      if (pauseButtonTimer > 0) pauseButtonTimer--;

      // restart
      if (pUI->getHeldKey(R)) restart = true;

      // quit
      if (pUI->getHeldKey(Q)) exit(0);
   }

   void draw(ogstream & gout, const Interface* pUI) const
   {
      // draw stars
      for (int i = 0; i < STARS_AMOUNT; i++)
         stars[i].draw(gout);

      ground.draw(gout);   // draw the ground
      lm.draw(gout, pUI);  // draw the lander and its flames
      drawText(gout);      // put some text on the screen
   }
   
   // helper methods for restart functionality
   Point getPtUpperRight() { return ptUpperRight; }
   bool getRestart()       { return restart; }

private:
   void checkCollisions()
   {
      // stop game and display 'crashed' if lm hit the ground
      if (ground.hitGround(lm.getPosition(), lm.getWidth()))
      {
         lm.crash();
         pause = true;
      }

      // stop game and display 'landed' if lm hit the ground
      if (ground.onPlatform(lm.getPosition(), lm.getWidth()))
      {
         lm.land();
         pause = true;
      }
   }
   
   void drawText(ogstream & gout) const
   {
      /* TOP - display menu options */
   
      // "quit == q"
      gout.setPosition(textTopRight);
      gout << "Q - Quit";
      
      // "pause == spc"
      gout.setPosition(textTopLeft);
      if (pause)  gout << "SPACE - Resume";
      else        gout << "SPACE - Pause";
      
      /* CENTER - display state */

      gout.setPosition(textCenter);

      // landed/crashed
      if (lm.isLanded())
      {
         if (lm.isAlive()) gout << "Landed";
         else              gout << "Crashed";
      }
      
      // paused
      else if (pause)
      {
         gout << "Paused";
      }

      /* BOTTOM - lander info */

      // lander position
      gout.setPosition(
         Point(textBottomLeft.getX(),
               textBottomLeft.getY() + 40)
         );
      gout << "LM Position " << lm.getPosition();
      
      // lm velocity (dx, dy)
      gout.setPosition(
         Point(textBottomLeft.getX(),
               textBottomLeft.getY() + 20)
         );
      gout << "LM Velocity " << lm.getVelocity();
      
      // lm velocity (angle, magnitude)
      gout.setPosition(textBottomLeft);
      gout << "LM Angle " << lm.getAngle();
      gout.setPosition(textBottomCenter);
      gout << "LM Speed " << lm.getVelocity().getSpeed();
   }

   /* simulator objects */
   LM lm;                  // lunar module object
   Ground ground;          // object to keep track of ground attributes
   vector<Star> stars;     // dynamic list to keep track of stars
   Point ptUpperRight;     // size of the screen
   
   /* other simulator attributes */
   bool restart;           // flag for callback to use in order to restart game
   bool pause;             // flag for updating screen/objects
   int pauseButtonTimer;

   Point textBottomLeft;
   Point textBottomRight;
   Point textTopLeft;
   Point textTopRight;
   Point textCenter;
   Point textBottomCenter;
   Point textTopCenter;
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

   /**********************************************************************
    * the first step is to cast the void pointer into a game object. This
    * is the first step of every single callback function in OpenGL.
    **********************************************************************/
   Game * pGame = (Game *)p;  

   /*******************************************
    * Note from Elijah:
    * Let game handle specific tasks by calling
    * game::update(),
    * game::draw() and
    * game::handleInput()
    *******************************************/
   pGame->update();
   pGame->draw(gout, pUI);
   pGame->handleInput(pUI);
   
   /**********************************************
    * Note from Elijah:
    * The idea behind this is to restart the game.
    * Specifically, create a new Game object and
    * set pGame equal to the new game object
    * pointer.
    * Currently, this is not functioning.
    * In the debug module, game.ptUpperRight.x and
    * .y both have values of 0.0 (double) at the
    * end of execution.
    **********************************************/
   if (pGame->getRestart())
   {
      Game game(Point(SCREEN_WIDTH, SCREEN_HEIGHT));
      pGame = &game;
   }
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
   Point ptUpperRight(SCREEN_WIDTH, SCREEN_HEIGHT);
   Interface ui(0, NULL, "Open GL Game", ptUpperRight);

   // Initialize the game class
   Game game(ptUpperRight);

   // set everything into action
   ui.run(callBack, &game);             

   return 0;
}

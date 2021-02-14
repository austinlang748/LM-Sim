/**************************************************************************
 * LM SIMULATOR
 * 
 * MAIN SOURCE FILE
 *
 * Authors: Austin Hilderbrand, Elijah Harrison
 *
 * CSE 230 - Encapsulation Design
 * Lab 06:  Apollo 11 Final Submission
 * Instructor: Brother Helfrich
 **************************************************************************/

#include <vector>

#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"
#include "LM.h"
#include "star.h"

// Constants
const double SCREEN_WIDTH  = 400.0;
const double SCREEN_HEIGHT = 400.0;
const int    STARS_AMOUNT  = 100;

using namespace std;

/**************************************************************************
 * Game
 *
 * Authors: Austin Hilderbrand, Elijah Harrison
 *
 * Contains all information and methods relevant for handling gameplay. 
 * This includes displaying information to the screen, processing user
 * input, and handling core gameplay logic.
 **************************************************************************/
class Game
{
public:
   /**************************************************************************
    * Initializer
    *
    * Initializes the gameplay state (restart, pause) and objects in the game
    * (LM, stars, ground, text). 
    **************************************************************************/
   Game(const Point& ptUpperRight) :
         lm(ptUpperRight),
         ground(ptUpperRight),
         restart(false),
         pause(false),
         pauseButtonTimer(0)

   {
      // Create stars to be put on the screen. 
      for (int i = 0; i < STARS_AMOUNT; i++)
         stars.push_back(Star());
      
      // Specify all the points which determine the text location. 
      textBottomLeft = Point(10, 20);
      textBottomRight = Point(ptUpperRight.getX() - 80, 20);
      textTopLeft = Point(10, ptUpperRight.getY() - 20);
      textTopRight = Point
      (
         ptUpperRight.getX() - 80,
         ptUpperRight.getY() - 20
      );
      textCenter = Point
      (
         ptUpperRight.getX()/2 - 40,
         ptUpperRight.getY()/2
      );
      textBottomCenter = Point(textCenter.getX(), 20);
      textTopCenter = Point
      (
         textCenter.getX(),
         ptUpperRight.getY() - 20
      );
   }
    
   /**************************************************************************
    * update
    *
    * Updates the game state. 
    * This code should be executed once every 0.1 seconds. 
    **************************************************************************/
   void update()
   {
      // If the game isn't paused, update the LM.
      cout << pause << endl;
      if (!pause) lm.update();

      // Update star phases. 
      for (int i = 0; i < STARS_AMOUNT; i++)
         stars[i].update();
   
      // Check for collisions. 
      checkCollisions();
   }

   /**************************************************************************
    * handleInput
    *
    * Allows the user to interact with the game. 
    **************************************************************************/
   void handleInput(const Interface *pUI)
   {
      // If not paused, handle LM input.
      if (!pause) lm.handleInput(pUI);
      
      // Pause/resume the game.
      if (pUI->getHeldKey(SPACE) && pauseButtonTimer <= 0)
      {
         pause = !pause;         // Toggle pause/resume.
         pauseButtonTimer = 40;  // Delay 2/3 of a second.
      }
      
      // Update pause button timer.
      if (pauseButtonTimer > 0) pauseButtonTimer--;

      // Restart.
      if (pUI->getHeldKey(R)) restart = true;

      // Quit.
      if (pUI->getHeldKey(Q)) exit(0);
   }
   
   /**************************************************************************
    * draw
    *
    * Display everything to the user. 
    **************************************************************************/
   void draw(ogstream & gout, const Interface* pUI) const
   {
      // Draw the stars. 
      for (int i = 0; i < STARS_AMOUNT; i++)
         stars[i].draw(gout);

      ground.draw(gout);   // Draw the ground.
      lm.draw(gout, pUI);  // Draw the lander and its flames.
      drawText(gout);      // Put the text on the screen. 
   }
   
   // Helper methods for restart functionality.
   Point getPtUpperRight() { return ptUpperRight; }
   bool getRestart()       { return restart; }

private:
   /**************************************************************************
    * checkCollisions
    *
    * Determine if the LM has come in contact with the ground or the platform. 
    **************************************************************************/
   void checkCollisions()
   {
      // Stop game and display 'crashed' if LM hit the ground.
      if (ground.hitGround(lm.getPosition(), lm.getWidth()))
      {
         lm.crash();
         pause = true;
      }

      // Stop game and display 'landed' if LM hit the platform.
      if (ground.onPlatform(lm.getPosition(), lm.getWidth()))
      {
         lm.land();
         pause = true;
      }
   }
   
   /**************************************************************************
    * drawText
    *
    * Determines which text information to display to the user. 
    **************************************************************************/
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

      // Landed/crashed
      if (lm.isLanded())
      {
         if (lm.isAlive()) gout << "Landed";
         else              gout << "Crashed";
      }
      
      // Paused
      else if (pause)
      {
         gout << "Paused";
      }

      /* BOTTOM - LM info */

      // Lander position
      gout.setPosition(
         Point(textBottomLeft.getX(),
               textBottomLeft.getY() + 40)
         );
      gout << "LM Position " << lm.getPosition();
      
      // LM velocity (dx, dy)
      gout.setPosition(
         Point(textBottomLeft.getX(),
               textBottomLeft.getY() + 20)
         );
      gout << "LM Velocity " << lm.getVelocity();
      
      // LM velocity (angle, magnitude)
      gout.setPosition(textBottomLeft);
      gout << "LM Angle " << lm.getAngle();
      gout.setPosition(textBottomCenter);
      gout << "LM Speed " << lm.getVelocity().getSpeed();
   }

   /* Simulator objects */
   LM lm;                  // lunar module object
   Ground ground;          // object to keep track of ground attributes
   vector<Star> stars;     // dynamic list to keep track of stars
   Point ptUpperRight;     // size of the screen
   
   /* Other simulator attributes */
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


/**************************************************************************
* callBack
*
* All the interesting work happens here, when I get called back from OpenGL
* to draw a frame. When I am finished drawing, then the graphics engine 
* will wait until the proper amount of time has passed and put the drawing 
* on the screen.
**************************************************************************/
void callBack(const Interface *pUI, void * p)
{
   ogstream gout;

   /**********************************************************************
    * The first step is to cast the void pointer into a game object. This
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

/********
 * MAIN *
 ********/

#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance, 
   _In_opt_ HINSTANCE hPrevInstance, 
   _In_ PWSTR pCmdLine, 
   _In_ int nCmdShow)
#else // !_WIN32

 /**************************************************************************
 * main
 *
 * Initializes the Game type and calls the display engine.
 **************************************************************************/
int main(int argc, char ** argv)
#endif // !_WIN32
{
   // Initialize OpenGL.
   Point ptUpperRight(SCREEN_WIDTH, SCREEN_HEIGHT);
   Interface ui(0, NULL, "Open GL Game", ptUpperRight);

   // Initialize the game class.
   Game game(ptUpperRight);

   // Set everything into action.
   ui.run(callBack, &game);             

   return 0;
}
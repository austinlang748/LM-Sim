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

const int STARS_AMOUNT = 100;

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
         pause(false)
   {
      // create stars to be put on the screen
      for (int i = 0; i < STARS_AMOUNT; i++)
         stars.push_back(Star());

      // set other attributes
      angle = 0.0;
   }
    
   void update()
   {
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
      if (!pause) {
         // handle lunar module input
         lm.handleInput(pUI);
      }
   }

   void draw(ogstream & gout, const Interface* pUI) const
   {
      // draw stars
      for (int i = 0; i < STARS_AMOUNT; i++)
         stars[i].draw(gout);

      // draw the ground
      ground.draw(gout);

      // draw the lander and its flames
      lm.draw(gout, pUI);

      // put some text on the screen
      gout.setPosition(Point(30.0, 280.0));
      gout << "LM Position (" << lm.getPosition().toString() << ")" << "\n";
      
      // display 'crashed'/'landed'
      if (pause)
      {
         gout.setPosition(Point(280, 30.0));
         if (lm.isAlive()) gout << "Landed\n";
         else gout << "Crashed\n";
      }
   }

private:
   void checkCollisions()
   {
      // stop game and display 'crashed' if lm hit the ground
      if (ground.hitGround(lm.getPosition(), lm.getWidth()))
         lm.setAlive(false);
      pause = !lm.isAlive();
      
      // stop game and display 'landed' if lm hit the ground
      if (ground.onPlatform(lm.getPosition(), lm.getWidth()))
      {
         pause = true;
      }
   }

   LM lm;                  // lunar module object
   Ground ground;          // object to keep track of ground attributes
   vector<Star> stars;     // dynamic list to keep track of stars
   Point ptUpperRight;     // size of the screen
   bool pause;             // update screen/objects?
   double angle;           // angle the LM is pointing
   unsigned char phase;    // phase of the star's blinking
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
   
   // Elijah:
   // Let game handle specific tasks by calling 
   // game::update() and game::draw()
   pGame->update();
   pGame->draw(gout, pUI);
   pGame->handleInput(pUI);
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

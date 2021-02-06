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
          lm(ptUpperRight.getX() / 2.0, ptUpperRight.getY() / 2.0),
          ground(ptUpperRight)
   { 
      // create stars to be put on the screen
      for (int i = 0; i < STARS_AMOUNT; i++)
         stars.push_back(Star());

      // set other attributes
      angle = 0.0;
   }
    
   void update()
   {
        
   }

   void handleInput(const Interface *pUI)
   {
      // move the ship around
      if (pUI->isRight())
         lm.addX(-1.0);
      if (pUI->isLeft())
         lm.addX(1.0);
      if (pUI->isUp())
         lm.addY(-1.0);
      if (pUI->isDown())
         lm.addY(1.0);
   }

   void draw(ogstream & gout, const Interface* pUI) const
   {
       // draw stars
       for (int i = 0; i < STARS_AMOUNT; i++)
          stars[i].draw(gout);

      // draw the ground
      ground.draw(gout);

      // draw the lander and its flames
      gout.drawLander(lm /*position*/, angle /*angle*/);
      gout.drawLanderFlames(lm, angle, /*angle*/
                     pUI->isDown(), pUI->isLeft(), pUI->isRight());

      // put some text on the screen
      gout.setPosition(Point(30.0, 30.0));
      gout << "Game (" << (int)lm.getX() << ", " << (int)lm.getY() << ")" << "\n";
   }

private:
   // this is just for test purposes.  Don't make member variables public!
   Point lm;               // lunar module object
   Ground ground;          // object to keep track of ground attributes
   vector<Star> stars;     // dynamic list to keep track of stars
   Point ptUpperRight;     // size of the screen
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

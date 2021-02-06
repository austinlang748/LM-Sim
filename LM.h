/*************************************************************
 * LM
 * Represents both the position and velocity of the LM.
 *****************************************************************/

#include "math.h"
#include "point.h"
#include "velocity.h"
#include "point.h"
#include "thrust.h"

#ifndef M_PI              // Define M_PI (within class)
#define M_PI 3.14159265358979323846
#endif


class LM
{
public:
   LM(const Point& ptUpperRight) : 
      weight(15103),
      thrustAmountX(45000), thrustAmountY(450),
      gravity(-1.625),
      angle(0.00), fuel(25000)
   {
      point.set(
          ptUpperRight.getX() / 2.0,
          ptUpperRight.getX() / 2.0
      );
   }
   
   void update()
   {
      
   }
   
   void draw(ogstream & gout, const Interface* pUI) const
   {
      // draw lander
      gout.drawLander(point, angle);

      // draw flames (direction based on key input)
      gout.drawLanderFlames(
         point, angle,
         pUI->isDown(), pUI->isLeft(), pUI->isRight()
      );
   }
   
   void handleInput(const Interface * pUI)
   {
      // accerate forward when up arrow is pressed
   }

   void reset()
   {

   }

   bool isDead()
   {

   }

   bool isLanded()
   {

   }

   bool isFlying()
   {

   }

   Point getPosition()
   {

   }

   int getFuel()
   {

   }

private:
   /*************************************************************
    * DEGREES FROM RADIANS and RADIANS FROM DEGREES
    * Convert degrees to radians and vice-versa.
    *****************************************************************/
   double degreesFromRadians(double radians) const
   {
      return 360.0 * (radians / (2.0 * M_PI));
   }
   
   double radiansFromDegrees(double degrees) const
   {
      return (2.0 * M_PI) * (degrees / 360.0);
   }

   // Attribute declarations
   Point point;
   Point screenTopRight;
   Velocity v;
   double angle;
   double fuel;
   const double thrustAmountX;
   const double thrustAmountY;
   const double weight;
   const double gravity;
   bool alive;
   bool landed;
};

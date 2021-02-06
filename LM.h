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
      weight(15103), vThrust(45000),
      hThrust(450), gravity(-1.625)
   {
      pt.setX(ptUpperRight.getX() / 2.0);
      pt.setY(ptUpperRight.getY() / 2.0);
      v.setDX(0.00);
      v.setDY(0.00); 
      angle = 0.00;
      fuel = 25000;
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

   void draw(const Thrust& thrust)

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
   Point pt;
   Point ptUpperRight;
   Velocity v;
   double angle;
   double fuel;
   const double weight;
   const double vThrust;
   const double hThrust;
   const double gravity;
};

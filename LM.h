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
      thrustAmountX(45000),
      thrustAmountY(450),
      gravity(-1.625),
      angle(90.00),
      fuel(25000)
   {
      point.set(
          ptUpperRight.getX() / 2.0,
          ptUpperRight.getX() / 2.0
      );
      center.set(point);
   }
   
   void update()
   {
      point.add(v);
      v.addMagnitude(degreesToRadians(angle), gravity);
   }
   
   void draw(ogstream & gout, const Interface* pUI) const
   {
      // draw lander
      gout.drawLander(point, degreesToRadians(angle - 90));

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
      v.set(0,0);
      point.set(center);
   }

   bool isAlive() { return alive; }
   bool isLanded() { return landed; }
   bool isFlying() { return !landed; }

   Point getPosition() const { return point; }

   double getFuel() { return fuel; }

   Velocity getVelocity() { return v; }
   
private:
   /*************************************************************
    * DEGREES FROM RADIANS and RADIANS FROM DEGREES
    * Convert degrees to radians and vice-versa.
    *****************************************************************/
   double radiansToDegrees(double degrees) const
   {
      return 180 * degrees / M_PI;
   }

   double degreesToRadians(double radians) const
   {
      return M_PI * radians / 180;
   }

   // Attribute declarations
   Point point;
   Point center;
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

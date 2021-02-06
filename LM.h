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
      mass(15103),
      width(10),
      thrustRotateAmount(450),
      thrustAmountY(45000),
      gravity(-1.625),
      angle(90.00),
      fuel(25000),
      alive(true)
   {
      point.set(
          ptUpperRight.getX() / 2.0,
          ptUpperRight.getX() / 1.25
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
         point, degreesToRadians(angle - 90),
         pUI->isDown(), pUI->isLeft(), pUI->isRight()
      );
   }
   
   void handleInput(const Interface * pUI)
   {
      // accerate forward when up arrow is pressed
      if (pUI->isDown())
         v.addMagnitude(degreesToRadians(angle), thrustAmountY);
   }

   void reset()
   {
      v.set(0,0);
      point.set(center);
   }

   bool  isAlive()      const { return alive; }
   bool  isLanded()     const { return landed; }
   bool  isFlying()     const { return !landed; }
   Point getPosition()  const { return point; }
   double getFuel()     const { return fuel; }
   double getWidth()    const { return width; }
   
   void setAlive(bool value) { alive = value; }
   
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
   const double thrustAmountY;
   const double thrustRotateAmount;
   const double mass;
   const double width;
   const double gravity;
   bool alive;
   bool landed;
};

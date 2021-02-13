/*************************************************************
 * LM
 * Represents both the position and velocity of the LM.
 *****************************************************************/

#include "point.h"      // import Point class
#include "velocity.h"   // import Velocity class
#include "uiInteract.h" // import keys (enum) from file (global scope)

#include <math.h>       // import M_PI


class LM
{
public:
   LM(const Point& ptUpperRight) : 
      mass(15103),
      width(10),
      thrustRotateAmount(45000),
      thrustAmountY(450),
      gravity(-1.625),
      angle(90.00),
      fuel(25000),
      alive(true),
      landed(false)
   {
      point.set(
          ptUpperRight.getX() / 2.0,
          ptUpperRight.getX() / 1.25
      );
      center.set(point);
   }
   
   void update()
   {
      if (landed) return;
      point.add(v);
      v.addMagnitude(degreesToRadians(90), gravity);
   }
   
   void draw(ogstream & gout, const Interface* pUI) const
   {
      // draw lander
      gout.drawLander(point, degreesToRadians(angle - 90));

      // don't draw flames when landed
      if (landed) return;

      // draw flames (direction based on key input)
      gout.drawLanderFlames(
          point, degreesToRadians(angle - 90),
          pUI->getHeldKey(DOWN),
          pUI->getHeldKey(LEFT),
          pUI->getHeldKey(RIGHT)
      );
   }
   
   void handleInput(const Interface * pUI)
   {
      // don't update input values when landed
      if (landed) return;

      // accerate forward when up arrow is pressed
      if (pUI->getHeldKey(DOWN))
         v.addMagnitude(degreesToRadians(angle), thrustAmountY/100);
      
      if (pUI->getHeldKey(LEFT)) {
         angle -= thrustRotateAmount/10000;
      }
      
      if (pUI->getHeldKey(RIGHT))
         angle += thrustRotateAmount/10000;
   }
   
   void hit()
   {
      setAlive(false);
      setLanded(true);
   }
   
   void crash()
   {
      hit();
   }
   
   void land()
   {
      setAlive(true);
      setLanded(true);
   }

   void reset()
   {
      v.set(0,0);
      point.set(center);
   }

   bool     isAlive()      const { return alive;   }
   bool     isLanded()     const { return landed;  }
   bool     isFlying()     const { return !landed; }
   double   getAngle()     const { return angle;   }
   double   getFuel()      const { return fuel;    }
   double   getWidth()     const { return width;   }
   Point    getPosition()  const { return point;   }
   Velocity getVelocity()  const { return v;       }
   
   void setAlive(bool value)     { alive = value;  }
   void setLanded(bool value)    { landed = value; }
   
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

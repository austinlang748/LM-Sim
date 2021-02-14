/**************************************************************************
 * LM
 *
 * Authors: Austin Hilderbrand, Elijah Harrison
 *
 * Represents both the position and velocity of the LM.
 **************************************************************************/

#include "point.h"      // import Point class
#include "velocity.h"   // import Velocity class
#include "uiInteract.h" // import keys (enum) from file (global scope)

#define PI 3.14159265358979323846 // Pi constant

class LM
{
public:
   /***********************************************************************
    * Initializer
    *
    * Initialize the LM with constant attributes and starting values. 
    ***********************************************************************/
   LM(const Point& ptUpperRight) : 
      // Constant attributes
      mass(15103),
      width(10),
      thrustRotateAmount(45000),
      thrustAmountY(450),
      gravity(-1.625),

      // Starting values
      angle(90.00),
      fuel(25000),
      alive(true),
      landed(false)

   {
      // Set the starting location.
      point.set
      (
          ptUpperRight.getX() / 2.0,
          ptUpperRight.getX() / 1.25
      );
      center.set(point);
   }
   
   /***********************************************************************
    * update
    *
    * Has the LM landed? If not, update the location of the lander. 
    * This should be called once every 0.1 seconds. 
    ***********************************************************************/
   void update()
   {
      if (landed) return; // Landed?

      // If not, update the location of the lander. 
      point.add(v);
      v.addMagnitude(degreesToRadians(90), gravity);
   }
   
   /***********************************************************************
    * draw
    *
    * Draw the lander and its flames (if not landed) to the screen. 
    ***********************************************************************/
   void draw(ogstream & gout, const Interface* pUI) const
   {
      // Draw lander.
      gout.drawLander(point, degreesToRadians(angle - 90));

      // Don't draw flames when landed.
      if (landed) return;

      // Draw flames (direction based on key input).
      gout.drawLanderFlames
      (
          point, degreesToRadians(angle - 90),
          pUI->getHeldKey(DOWN),
          pUI->getHeldKey(LEFT),
          pUI->getHeldKey(RIGHT)
      );
   }
   
   /***********************************************************************
    * handleInput
    *
    * If the LM hasn't landed, accept user input to apply thrust. 
    * The user may use the down arrow for the main thrusters, or the 
    * left/right arrows for rotational thrust. 
    ***********************************************************************/
   void handleInput(const Interface * pUI)
   {
      // Don't update input values when landed
      if (landed) return;

      // Accerate using main thrusters when down arrow is pressed.
      if (pUI->getHeldKey(DOWN))
         v.addMagnitude(degreesToRadians(angle), thrustAmountY/100);
      
      // Rotate clockwise when left arrow is pressed. 
      if (pUI->getHeldKey(LEFT))
         angle -= thrustRotateAmount/10000;
      
      // Rotate counterclockwise when right arrow is pressed. 
      if (pUI->getHeldKey(RIGHT))
         angle += thrustRotateAmount/10000;
   }
   
   /***********************************************************************
    * crash
    *
    * The lander has crashed!
    ***********************************************************************/
   void crash()
   {
      setAlive(false);
      setLanded(true);
   }
   
   /***********************************************************************
    * land
    *
    * The LM has landed successfully!
    ***********************************************************************/
   void land()
   {
      setAlive(true);
      setLanded(true);
   }

   /***********************************************************************
    * reset
    *
    * Reset the LM to its starting position and velocity. 
    ***********************************************************************/
   void reset()
   {
      v.set(0,0);
      point.set(center);
   }

   /**************************************************************************
    * Getters
    **************************************************************************/
   bool     isAlive()      const { return alive;   }
   bool     isLanded()     const { return landed;  }
   bool     isFlying()     const { return !landed; }
   double   getAngle()     const { return angle;   }
   double   getFuel()      const { return fuel;    }
   double   getWidth()     const { return width;   }
   Point    getPosition()  const { return point;   }
   Velocity getVelocity()  const { return v;       }
   
   /**************************************************************************
    * Setters
    **************************************************************************/
   void setAlive(bool value)     { alive = value;  }
   void setLanded(bool value)    { landed = value; }
   
private:
   /*************************************************************
    * DEGREES FROM RADIANS and RADIANS FROM DEGREES
    * 
    * Convert degrees to radians and vice-versa.
    *****************************************************************/
   double radiansToDegrees(double degrees) const
   {
      return 180 * degrees / PI;
   }

   double degreesToRadians(double radians) const
   {
      return PI * radians / 180;
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

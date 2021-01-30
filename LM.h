/*************************************************************
 * LM
 * Represents both the position and velocity of the LM.
 *****************************************************************/

#include "point.h"
#include "velocity.h"

#ifndef M_PI              // Define M_PI (within class)
#define M_PI 3.14159265358979323846
#endif


class LM
{
public:
   LM(double altitude, double position,
      double verticalVelocity,
      double horizontalVelocity,
      double degrees) :
      weight(15103.00), gravity(-1.625), thrust(45000.00)
   {
      x = position;
      y = altitude;
      dx = horizontalVelocity;
      dy = verticalVelocity;
      updateAngle(degrees);
   }

   /*************************************************************
    * UPDATE ANGLE
    * Converts the angle to radians from degrees.
    *****************************************************************/
   void updateAngle(int degrees)
   {
      angle = radiansFromDegrees(degrees);
   }

   /*************************************************************
    * APPLY INERTIA
    * Changes the position of the LM by applying dx and dy.
    *****************************************************************/
   void applyInertia()
   {
      x += dx;
      y += dy;
   }

   /*************************************************************
    * APPLY THRUST
    * Applies the vertical and/or horizontal acceleration due to the force
    * of the thrusters.
    *****************************************************************/
   void applyThrust()
   {
      dy += cos(angle) * thrust / weight;
      dx += sin(angle) * thrust / weight;
   }
   /*************************************************************
    * APPLY GRAVITY
    * Applies the downward acceleration due to gravity to dy.
    *****************************************************************/
   void applyGravity()
   {
      dy += gravity;
   }

   /*************************************************************
    * TOTAL VELOCITY
    * Returns the total velocity of the LM.
    *****************************************************************/
   double totalVelocity() const
   {
      return sqrt(dx * dx + dy * dy);
   }

   // The overloaded insertion operator must be declared as a friend
   // of the LM class to get access to its data later on. 
   friend ostream& operator << (ostream& out, const LM& rhs);

private:
   /*************************************************************
    * DEGREES FROM RADIANS and RADIANS FROM DEGREES
    * Convert degrees to radians and vice-verse.
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
   const double thrust;
   const double gravity;
};

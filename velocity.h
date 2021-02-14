/**************************************************************************
 * Velocity
 *
 * Authors: Austin Hilderbrand, Elijah Harrison
 *
 * Contains all velocity-related information and the methods to act on it.
 **************************************************************************/

#pragma once

#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

class Velocity
{
public:
   /**************************************************************************
    * Initializer
    *
    * Sets the starting velocity, equal to 0.00 because we want the LM to be
    * motionless at the start of the simulation. 
    **************************************************************************/
   Velocity(double dx_init = 0.0, double dy_init = 0.00)
   {
      dx = dx_init;
      dy = dy_init;
   }
   
   /**************************************************************************
    * OVERLOADED == and != OPERATORS
    *
    * This will assist with velocity comparisons. 
    **************************************************************************/
   bool operator == (const Velocity & rhs) const
   {
      return dx == rhs.dx && dy == rhs.dy;
   }
   
   bool operator != (const Velocity & rhs) const
   {
      return dx != rhs.dx || dy != rhs.dy;
   }

   /**************************************************************************
    * Getters
    **************************************************************************/
   double getDx() const { return dx; }
   double getDy() const { return dy; }
   double getSpeed() const
   {
      return sqrt(dx * dx + dy * dy);
   }
   
   /**************************************************************************
    * Setters
    **************************************************************************/
   void setDx(double newDx) { dx = newDx; }
   void setDy(double newDy) { dy = newDy; }
   void set(Velocity v) { set(v.dx, v.dy); }
   
   void set(double dx, double dy)
   {
      setDx(dx);
      setDy(dy);
   }
   
   /**************************************************************************
    * Adders
    *
    * Methods which apply acceleration. 
    **************************************************************************/
   void addDx(double dxAdd) { dx += dxAdd; }
   void addDy(double dyAdd) { dy += dyAdd; }

   // Shell method for addDx and addDy. 
   void add(double ddx, double ddy)
   {
      addDx(ddx);
      addDy(ddy);
   }
   
   // A way to use add() by passing an angle and magnitude. 
   void addMagnitude(double angleRad, double magnitude)
   {
      add(magnitude * cos(angleRad), magnitude * sin(angleRad));
   }
   
   // A way to use add() by passing a single velocity object. 
   void add(Velocity acceleration)
   {
      add(acceleration.dx, acceleration.dy);
   }

private:
   // Attribute declarations. 
   double dx;
   double dy;
};

// Stream I/O used by gout and useful for debugging.
ostream & operator << (ostream & out, const Velocity & v);
istream & operator >> (istream & in,        Velocity & v);

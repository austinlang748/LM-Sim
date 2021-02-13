/************************************************
* Velocity Class
* Written by Austin Hilderbrand
*************************************************/

#pragma once

#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;

class Velocity
{
public:
   Velocity(double dx_init = 0.0, double dy_init = 0.00)
   {
      dx = dx_init;
      dy = dy_init;
   }

   // getters
   double getDx() const { return dx; }
   double getDy() const { return dy; }
   
   double getSpeed() const
   {
      return sqrt(dx * dx + dy * dy);
   }
   
   bool operator == (const Velocity & rhs) const
   {
      return dx == rhs.dx && dy == rhs.dy;
   }
   
   bool operator != (const Velocity & rhs) const
   {
      return dx != rhs.dx || dy != rhs.dy;
   }
   
   // setters
   void setDx(double newDx) { dx = newDx; }
   void setDy(double newDy) { dy = newDy; }
   void set(Velocity v) { set(v.dx, v.dy); }
   
   void set(double dx, double dy)
   {
      setDx(dx);
      setDy(dy);
   }
   
   // adders
   void addDx(double dxAdd) { dx += dxAdd; }
   void addDy(double dyAdd) { dy += dyAdd; }
   
   void add(double ddx, double ddy)
   {
      addDx(ddx);
      addDy(ddy);
   }
   
   void addMagnitude(double angleRad, double magnitude)
   {
      add(magnitude * cos(angleRad), magnitude * sin(angleRad));
   }
    
   void add(Velocity acceleration)
   {
      add(acceleration.dx, acceleration.dy);
   }

private:
   double dx;
   double dy;
};

// stream I/O used by gout and useful for debugging
ostream & operator << (ostream & out, const Velocity & v);
istream & operator >> (istream & in,        Velocity & v);

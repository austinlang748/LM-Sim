/************************************************
* Velocity Class
* Written by Austin Hilderbrand
*************************************************/

#pragma once

#include <cmath>
#include <iostream>
using namespace std;

class Velocity
{
public:
   Velocity(double dx_init = 0.0, double dy_init = 0.00)
   {
      dx = dx_init;
      dy = dy_init;
   }

   double getDx() { return dx; }
   double getDy() { return dy; }
   
   double getSpeed() const
   {
      return sqrt(dx * dx + dy * dy);
   }

   void setDx(double newDX) { dx = newDX; }
   void setDy(double newDY) { dy = newDY; }
   void set(Velocity v) { set(v.dx, v.dy); }
   
   void set(double dx, double dy)
   {
      setDx(dx);
      setDy(dy);
   }
   
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
istream & operator >> (istream & in, Velocity & v);

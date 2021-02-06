/************************************************
* Velocity Class
* Written by Austin Hilderbrand
*************************************************/

#pragma once

#include <cmath>

class Velocity
{
public:
   Velocity(double dx_init = 0.0, double dy_init = 0.00)
   {
      dx = dx_init;
      dy = dy_init;
   }

   double getDX() { return dx; }
   double getDY() { return dy; }
   
   double getSpeed() const
   {
      return sqrt(dx * dx + dy * dy);
   }

   void setDX(double newDX) { dx = newDX; }
   void setDY(double newDY) { dy = newDY; }
   
   void addDX(double dxAdd) { dx += dxAdd; }
   void addDY(double dyAdd) { dy += dyAdd; }
    
   void accelerate(Velocity acceleration)
   {
      addDX(acceleration.dx);
      addDY(acceleration.dy);
   }

private:
   double dx;
   double dy;
};

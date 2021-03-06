/***********************************************************************
 * Header File:
 *    Point : The representation of a position on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/


#pragma once

#include "velocity.h"

#include <iostream>
#include <cassert>
using namespace std;

/*********************************************
 * POINT
 * A single position.  
 *********************************************/
class Point
{
public:
   // constructors
   Point()            : x(0.0), y(0.0)  {}
   Point(double x, double y) { set(x, y); }
   Point(const Point & pt) : x(pt.x), y(pt.y) {}

   // getters
   double getX() const { return x; }
   double getY() const { return y; }
   
   bool operator == (const Point & rhs) const
   {
      return x == rhs.x && y == rhs.y;
   }
   
   bool operator != (const Point & rhs) const
   {
      return x != rhs.x || y != rhs.y;
   }

   // setters
   void setX(double x)         { this->x = x; }
   void setY(double y)         { this->y = y; }

   void set(Point newPoint)    { set(newPoint.x, newPoint.y); }

   void set(double x, double y) {
      this->x = x;
      this->y = y;
   }

   void translate(Velocity v) {
      add(v.getDx(), v.getDy());
   }

   void addX(double dx) { setX(getX() + dx); }
   void addY(double dy) { setY(getY() + dy); }
   
   void add(Velocity v) { add(v.getDx(), v.getDy()); }
    
   void add(double dx, double dy) {
      x += dx/30;
      y += dy/30;
   }

   Point & operator = (const Point & rhs)
   {
      x = rhs.x;
      y = rhs.y;
      return *this;
   }

private:
    double x;  // horizontal position
    double y;  // vertical position
};

// stream I/O used by gout and useful for debugging
ostream & operator << (ostream & out, const Point & pt);
istream & operator >> (istream & in,        Point & pt);

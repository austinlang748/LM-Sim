/**************************************************************************
 * velocity.cpp
 *
 * Author: Elijah Harrison
 * Date: 02/13/2021
 *
 * Contains code for velocity insertion and extraction. 
 **************************************************************************/

#include "velocity.h"

using namespace std;

/**************************************************************************
 * VELOCITY INSERTION
 *  
 * Display coordinates on the screen. 
 **************************************************************************/
ostream & operator << (ostream & out, const Velocity & v)
{
   out << "(" << v.getDx() << ", " << v.getDy() << ")";
   return out;
}

/**************************************************************************
 * VELOCITY EXTRACTION
 *
 * Prompt for coordinates. 
 **************************************************************************/
istream & operator >> (istream & in, Velocity & v)
{
   double x;
   double y;
   in >> x >> y;

   v.setDx(x);
   v.setDy(y);

   return in;
}

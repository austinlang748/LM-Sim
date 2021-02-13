//
//  velocity.cpp
//  Lab03
//
//  Created by Elijah Harrison on 2/13/21.
//

#include "velocity.h"

/******************************************
 * VELOCITY insertion
 *       Display coordinates on the screen
 *****************************************/
std::ostream & operator << (std::ostream & out, const Velocity & v)
{
   out << "(" << v.getDx() << ", " << v.getDy() << ")";
   return out;
}

/*******************************************
 * VELOCITY extraction
 *       Prompt for coordinates
 ******************************************/
std::istream & operator >> (std::istream & in, Velocity & v)
{
   double x;
   double y;
   in >> x >> y;

   v.setDx(x);
   v.setDy(y);

   return in;
}
   

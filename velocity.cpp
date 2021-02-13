//
//  velocity.cpp
//  Lab03
//
//  Created by Elijah Harrison on 2/13/21.
//

#include "velocity.h"

using namespace std;

/******************************************
 * VELOCITY insertion
 *       Display coordinates on the screen
 *****************************************/
ostream & operator << (ostream & out, const Velocity & v)
{
   out << "(" << v.getDx() << ", " << v.getDy() << ")";
   return out;
}

/*******************************************
 * VELOCITY extraction
 *       Prompt for coordinates
 ******************************************/
istream & operator >> (istream & in, Velocity & v)
{
   double x;
   double y;
   in >> x >> y;

   v.setDx(x);
   v.setDy(y);

   return in;
}

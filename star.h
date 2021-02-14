/**************************************************************************
 * Star
 *
 * Author: Elijah Harrison
 *
 * Contains the necessary methods for displaying a star on the scrren. 
 **************************************************************************/

#include "point.h"
#include "uiDraw.h"

class Star {
public:
   /**************************************************************************
    * Initializer
    *
    * Set the location of the star and initialize the phase.
    **************************************************************************/
    Star() 
    {
        // Initialize point.
       point.setX(random(0.0, 400.0));
       point.setY(random(0.0, 400.0));

        // Initailize phase.
        phase = random(0, 255);
    }

    /**************************************************************************
    * update
    *
    * Cycles through the star phases.
    * Should be called once every 0.1 seconds. 
    **************************************************************************/
    void update() 
    {
        if (phase >= 255) phase = 0; // Reset phase once it reaches max value. 
        phase++;
    }

    /**************************************************************************
    * draw
    *
    * Draw the star on the screen. 
    **************************************************************************/
    void draw(ogstream & gout) const 
    {
        gout.drawStar(point, phase);
    }

private:
   // Attribute declarations
   Point point;
   unsigned char phase;
};

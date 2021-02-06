/**
 * Star class
 * 
 * Author: Elijah Harrison
 * 
 * Contains star components and methods necessary to display a single star on the screen.
 **/

#include "point.h"
#include "uiDraw.h"

class Star {
public:
    Star() {
        // initialize point
       point.setX(random(0.0, 400.0));
       point.setY(random(0.0, 400.0));

        // initailize phase
        phase = random(0, 255);
    }

    void update() {
        if (phase >= 255) phase = 0;
        phase++;
    }

    void draw(ogstream & gout) const {
        gout.drawStar(point, phase);
    }

private:
    Point point;
    unsigned char phase;
};

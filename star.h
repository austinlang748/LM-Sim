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
        point.set(random(0, 400), random(0, 400));

        // initailize phase
        phase = random(0, 255);
    }

    void update() {
        // TODO: update star phase here
    }

    void draw(ogstream & gout) const {
        gout.drawStar(point, phase);
    }

private:
    Point point;
    unsigned char phase;
};

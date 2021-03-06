/*
 * state.cpp
 *
 *  Created on: 18. 7. 2014
 *      Author: Petr Vana
 */

#include "opendubins/state.h"

using namespace std;

namespace opendubins {

    State::State() {
        this->point = Point(0, 0);
        this->ang = NAN;
    }

    State::State(Point point, myFloat angle) {
        this->point = point;
        this->ang = angle;
    }

    State::State(myFloat x, myFloat y, myFloat angle) {
        this->point = Point(x, y);
        this->ang = angle;
    }

    void State::random(myFloat interval) {
        this->point = Point(myRandom() * interval, myRandom() * interval);
        this->ang = myRandom() * 2 * M_PI;
    }

    Vector State::getNormalizedDirection() const {
        return Vector(cos(ang), sin(ang));
    }

    ostream &operator<<(ostream &os, const State &pos) {
        Point p = pos.getPoint();
        os << "(" << p.x << ", " << p.y << ", " << pos.getAngle() << ")";
        return os;
    }

}


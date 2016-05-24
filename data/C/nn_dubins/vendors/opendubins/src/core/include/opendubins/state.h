/*
 * state.h
 *
 *  Created on: 18. 7. 2014
 *      Author: Petr Vana
 */

#pragma once

#include "dmath.h"
#include "point.h"

namespace opendubins {

    class State final {
    public:
        Point point;
        myFloat ang;

        State();

        State(Point, myFloat);

        State(myFloat, myFloat, myFloat);

        inline void set(myFloat x, myFloat y, myFloat ang) {
            point.x = x;
            point.y = y;
            this->ang = ang;
        }

        void random(myFloat);

        Vector getNormalizedDirection() const;

        inline bool invalid() {
            return std::isnan(ang);
        }

        inline Point getPoint() const { return point; }

        inline myFloat getAngle() const { return ang; }

        inline myFloat squared_distance(const State &p) const {
            return point.distanceSquared(p.point);
        }

        //TODO - add method witch will check tolerance
        //bool isInTolerance
    };

    std::ostream &operator<<(std::ostream &os, const State &d);

}

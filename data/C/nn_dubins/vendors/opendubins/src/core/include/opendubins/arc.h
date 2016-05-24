/*
 * arc.h
 *
 *  Created on: 23. 7. 2014
 *      Author: Petr
 */

#pragma once

#include "path.h"
#include "line.h"
#include "intersection.h"

namespace opendubins {

    class Arc : public Path {
    public:

        State state;
        myFloat angle;
        myFloat radius;

        Arc() :
                angle(NAN), radius(NAN) {
        }

        Arc(State &state, myFloat angle, myFloat radius) :
                state(state), angle(angle), radius(radius) {
        }

        virtual State getState(myFloat len) const;

        virtual Intersection getClosestIntersection(const Point &p) const;

        Intersection intersectionPoint(const Line &line) const;

        Point getCenter() const;

        State getStateByAngle(myFloat angle) const;

        State getEnd() const;

        inline myFloat getLength() const {
            return fabs(getAngle()) * getRadius();
        }

        inline myFloat getAngle() const { return angle; }

        inline myFloat getRadius() const { return radius; }

        inline State getStart() const { return state; }
    };

    inline std::ostream &operator<<(std::ostream &os, const Arc &a) {
        os << "Arc: from={" << a.state << "} angle=" << a.angle << " radius=" << a.radius;
        return os;
    }

}

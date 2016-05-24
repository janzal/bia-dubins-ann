/*
 * line.h
 *
 *  Created on: 23. 7. 2014
 *      Author: Petr Vana
 */

#pragma once

#include "path.h"
#include "intersection.h"

namespace opendubins {

    class Line : public Path {
    public:

        Point p1;
        Point p2;

        inline Line() { };

        Line(const Point &, const Point &);

        Line(State, myFloat);

        virtual State getState(myFloat len) const;

        virtual Intersection getClosestIntersection(const Point &p) const;

        inline myFloat getLength() const {
            return (p2 - p1).length();
        }

        inline Vector getDirection() const {
            return p2 - p1;
        }

        bool intersect(Line line) const;

        Intersection intersectionPoint(Line line) const;


    };

    inline std::ostream &operator<<(std::ostream &os, const Line &d) {
        os << "Line from " << d.p1 << " to " << d.p2;
        return os;
    }

}


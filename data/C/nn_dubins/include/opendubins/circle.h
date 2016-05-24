/*
 * circle.h
 *
 *  Created on: 24. 2. 2015
 *      Author: Petr Vana
 */

#pragma once

#include <tuple>

#include "state.h"

namespace opendubins {

    struct Circle {

        Point center;
        myFloat radius;

        inline Circle() : center(Point(NAN, NAN)), radius(NAN) { };

        Circle(const Point &center, const myFloat &radius);

        virtual ~Circle();

        bool pointInCircle(Point);

        Point getCenter();

        myFloat perimeterLength();

        std::tuple<int, Point, Point> halfLineIntersections(const State &pos) const;

        Point halfLineIntersection(const State &pos) const;

        inline myFloat getRadius() { return radius; }
    };

}

/*
 * shapecircle.cpp
 *
 *  Created on: 24. 2. 2015
 *      Author: Petr Vana
 */

#include "opendubins/shape/shapecircle.h"

namespace opendubins {

    ShapeCircle::ShapeCircle(const Point &center, const myFloat &radius) {
        circle = Circle(center, radius);
    }

    ShapeCircle::~ShapeCircle() { }

    bool ShapeCircle::pointInPolygon(Point p) {
        return circle.pointInCircle(p);
    }

    Point ShapeCircle::getCenter() {
        return circle.center;
    }

    Point ShapeCircle::getEdgePoint(myFloat alpha) {
        return circle.center + circle.radius * Vector(alpha * 2 * M_PI);
    }

    myFloat ShapeCircle::perimeterLength() {
        return circle.perimeterLength();
    }

    int ShapeCircle::getType() {
        return 3;
    }

}

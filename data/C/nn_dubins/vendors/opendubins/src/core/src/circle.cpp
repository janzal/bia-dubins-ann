/*
 * circle.cpp
 *
 *  Created on: 24. 2. 2015
 *      Author: Petr Vana
 */

#include "opendubins/circle.h"

namespace opendubins {

    Circle::Circle(const Point &center, const myFloat &radius) {
        this->center = center;
        this->radius = radius;
    }

    Circle::~Circle() { }

    bool Circle::pointInCircle(Point p) {
        return center.distanceSquared(p) <= radius * radius;
    }

    Point Circle::getCenter() {
        return center;
    }

    myFloat Circle::perimeterLength() {
        return 2 * M_PI * radius;
    }


    std::tuple<int, Point, Point> Circle::halfLineIntersections(const State &pos) const {
        int count = 0;
        Point ps[2];

        // calculate two points of intersection
        Vector dir = pos.getNormalizedDirection(); // (already normalized)
        Vector normal = dir.left();
        myFloat distance = normal.dotProduct(center - pos.point);

        // vector to closest point on line from center of arc
        Vector vDistance = -distance * normal;

        if (distance < radius) {
            myFloat tangentAngle = vDistance.getAngle();
            myFloat diffAngle = acos(fabs(distance) / radius);

            myFloat ang1 = tangentAngle + diffAngle;
            myFloat ang2 = tangentAngle - diffAngle;

            auto p1 = center + Vector(ang1) * radius;
            auto p2 = center + Vector(ang2) * radius;

            if (dir.dotProduct(p1 - pos.point) > 0) {
                ps[count++] = p1;
            }

            if (dir.dotProduct(p2 - pos.point) > 0) {
                ps[count++] = p2;
            }
        }

        return std::tuple<int, Point, Point>(count, ps[0], ps[1]);
    }

    Point Circle::halfLineIntersection(const State &pos) const {
        auto ints = halfLineIntersections(pos);
        int count = std::get<0>(ints);

        if (count > 1) {
            auto len1 = pos.point.distance(std::get<1>(ints));
            if (count == 1) {
                return std::get<1>(ints);
            } else {
                auto len2 = pos.point.distance(std::get<2>(ints));
                if (len1 < len2) {
                    return std::get<1>(ints);
                } else {
                    return std::get<2>(ints);
                }
            }
        }
        return Point(NAN, NAN);
    }

}

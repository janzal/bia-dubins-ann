/*
 * arc.cpp
 *
 *  Created on: 23. 7. 2014
 *      Author: Petr Vana
 */

#include "opendubins/arc.h"

namespace opendubins {

    State Arc::getState(myFloat len) const {
        return getStateByAngle(len * sgn(angle) / radius);
    }

    Intersection Arc::getClosestIntersection(const Point &p) const {
        Intersection ret;

        // start state
        ret.state = state;
        ret.distance = 0;

        // end state
        auto end = getEnd();
        if (end.point.distance(p) < ret.state.point.distance(p)) {
            ret.state = end;
            ret.distance = getLength();
        }

        // center state
        if (angle > 0) { // left turn
            auto dir = (p - getCenter()).left().getAngle();
            auto turn = angleToLeft(state.ang, dir);
            auto turnLen = turn * radius;
            if (turnLen < getLength()) {
                auto actPos = getState(turnLen);
                if (actPos.point.distance(p) < ret.state.point.distance(p)) {
                    ret.state = actPos;
                    ret.distance = turnLen;
                }
            }
        } else { // right turn
            auto dir = (p - getCenter()).right().getAngle();
            auto turn = angleToRight(state.ang, dir);
            auto turnLen = -turn * radius;
            if (turnLen < getLength()) {
                auto actPos = getState(turnLen);
                if (actPos.point.distance(p) < ret.state.point.distance(p)) {
                    ret.state = actPos;
                    ret.distance = turnLen;
                }
            }
        }

        return ret;
    }

    Intersection Arc::intersectionPoint(const Line &line) const {
        myFloat rad = getLength() + line.getLength();
        if ((state.point - line.p1).lengthSquared() > rad * rad) {
            return Intersection(State(), 0);
        }

        // calculate two points of intersection
        Vector dir = line.getDirection().normalize();
        Vector normal = dir.left();
        myFloat distance = normal.dotProduct(getCenter() - line.p1);

        // vector to closest point on line from center of arc
        Vector vDistance = -distance * normal;

        if (distance > radius) {
            return Intersection(State(), 0);
        }

        myFloat tangentAngle = vDistance.getAngle() + (angle > 0 ? M_PI / 2 : -M_PI / 2);
        myFloat diffAngle = acos(fabs(distance) / radius);

        myFloat ang1 = tangentAngle + diffAngle;
        myFloat ang2 = tangentAngle - diffAngle;

        if (angle > 0) { // left
            myFloat turn1 = angleToLeft(state.ang, ang1);
            myFloat turn2 = angleToLeft(state.ang, ang2);

            myFloat less = std::min(turn1, turn2);
            myFloat more = std::max(turn1, turn2);

            if (less <= angle) {
                State p = getStateByAngle(less);
                myFloat dist = dir.dotProduct(p.point - line.p1);

                if (dist >= 0 && dist < line.getDirection().length()) {
                    return Intersection(p, less * radius);
                }

                if (more <= angle) {
                    p = getStateByAngle(more);
                    dist = dir.dotProduct(p.point - line.p1);

                    if (dist >= 0 && dist < line.getDirection().length()) {
                        return Intersection(p, more * radius);
                    }
                }
            }
        } else {
            myFloat turn1 = angleToRight(state.ang, ang1);
            myFloat turn2 = angleToRight(state.ang, ang2);

            myFloat less = std::max(turn1, turn2);
            myFloat more = std::min(turn1, turn2);

            if (less >= angle) {
                State p = getStateByAngle(less);
                myFloat dist = dir.dotProduct(p.point - line.p1);

                if (dist >= 0 && dist < line.getDirection().length()) {
                    return Intersection(p, less * -radius);
                }

                if (more >= angle) {
                    p = getStateByAngle(more);
                    dist = dir.dotProduct(p.point - line.p1);

                    if (dist >= 0 && dist < line.getDirection().length()) {
                        return Intersection(p, more * -radius);
                    }
                }
            }
        }

        // todo - try to refactor

        return Intersection(State(), 0);
    }

    Point Arc::getCenter() const {
        Point center = state.point;

        Vector toCenter = state.getNormalizedDirection().left();
        toCenter *= radius;
        if (angle < 0) {
            toCenter *= -1;
        }

        center += toCenter;

        return center;
    }

    State Arc::getStateByAngle(myFloat arcAngle) const {
        Point center = getCenter();

        Vector dir = state.getNormalizedDirection() * radius;
        Vector norm = state.point - center;

        myFloat aa = fabs(arcAngle);

        center += dir * sin(aa);
        center += norm * cos(aa);

        return State(center, state.ang + arcAngle);
    }

    State Arc::getEnd() const {
        return getStateByAngle(angle);
    }


}

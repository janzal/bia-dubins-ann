/*
 * angleinterval.h
 *
 *  Created on: Dec 4, 2015
 *      Author: Petr Vana
 */

#pragma once

#include "state.h"

namespace opendubins {

    struct AngleInterval {

        AngleInterval() :
                point(Point()), rightDir(NAN), diff(NAN) {
            resolution = -1;
        };

        AngleInterval(Point point, myFloat rightDir, myFloat diff) :
                point(point), rightDir(rightDir) {
            this->diff = angleToLeft(0, diff);

            resolution = -1;
        };

        AngleInterval(Point point) :
                point(point), rightDir(0), diff(2 * M_PI) {
            resolution = 1;
        };

        // right angle from the interval
        // startAngle \in <0,2*PI)
        myFloat rightDir;

        // diff between left and right angle <0,2*PI>
        // diff = 0    >> single direction
        // diff = 2*PI >> every possible dirrection
        myFloat diff;

        Point point;

        int resolution;

        inline myFloat getRight() {
            return rightDir;
        }

        inline myFloat getLeft() {
            return rightDir + diff;
        }

        inline State getLeftState() {
            return State(point, getLeft());
        }

        inline State getRightState() {
            return State(point, getRight());
        }

        inline Vector getLeftDir() {
            return Vector(getLeft());
        }

        inline Vector getRightDir() {
            return Vector(getRight());
        }

        inline myFloat inInterval(myFloat direction) {
            return angleToLeft(rightDir, direction) <= diff;
        }

        inline myFloat inIntervalWithTollerance(myFloat direction, myFloat tollerance) {
            if (angleToLeft(rightDir, direction) <= diff + tollerance) {
                return true;
            } else {
                if (angleToLeft(rightDir, direction) + tollerance > 2 * M_PI) {
                    return true;
                } else {
                    return false;
                }
            }
        }

        inline AngleInterval splitInterval() {
            diff /= 2;
            resolution *= 2;
            AngleInterval ret(point, getLeft(), diff);
            ret.resolution = resolution;
            return ret;
        }

        inline bool operator<(const AngleInterval &o) const {
            return rightDir < o.rightDir;
        }

        inline bool operator==(const AngleInterval &o) const {
            return point == o.point && rightDir == o.rightDir && diff == o.diff;
        }

        inline bool operator!=(const AngleInterval &o) const {
            return !(*this == o);
        }

        inline size_t hash() const {
            auto h1 = point.hash();
            auto h2 = std::hash<opendubins::myFloat>()(diff);
            auto h3 = std::hash<opendubins::myFloat>()(rightDir);
            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }

    };

    inline std::ostream &operator<<(std::ostream &os, const AngleInterval &d) {
        os << "AngleInterval: (" << d.rightDir << "; " << (d.rightDir + d.diff) << ")";
        return os;
    }

}

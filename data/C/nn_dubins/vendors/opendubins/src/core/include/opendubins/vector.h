/*
 * vector.h
 *
 *  Created on: 20. 7. 2014
 *      Author: Petr Vana
 */

#pragma once

#include "dmath.h"

namespace opendubins {

    class Vector {
    public:

        myFloat dx, dy;

        Vector(myFloat x, myFloat y) :
                dx(x), dy(y) {
        }

        Vector(myFloat angle) :
                dx(cos(angle)), dy(sin(angle)) {
        }

        inline myFloat getAngle() const {
            return atan2(dy, dx);
        }

        inline Vector right() const {
            return Vector(dy, -dx);
        }

        inline Vector left() const {
            return Vector(-dy, dx);
        }

        inline Vector negate() const {
            return Vector(-dx, -dy);
        }

        inline myFloat length() const {
            return sqrt(dx * dx + dy * dy);
        }

        inline myFloat lengthSquared() const {
            return dx * dx + dy * dy;
        }

        inline Vector normalize() const {
            myFloat len = this->length();
            return Vector(dx / len, dy / len);
        }

        inline myFloat dotProduct(const Vector &vec) const {
            return dx * vec.dx + dy * vec.dy;
        }

        inline Vector &operator*=(const myFloat &mult) {
            dx *= mult;
            dy *= mult;
            return *this;
        }

        inline Vector &operator+=(const Vector &rght) {
            dx += rght.dx;
            dy += rght.dy;
            return *this;
        }

        inline Vector rotate(const myFloat &angle) const {
            const myFloat c = cos(angle);
            const myFloat s = sin(angle);
            return Vector(c * dx - s * dy, c * dy + s * dx);
        }

    };

    inline Vector operator+(const Vector &left, const Vector &right) {
        return Vector(left.dx + right.dx, left.dy + right.dy);
    }

    inline Vector operator*(const Vector &left, const myFloat &right) {
        return Vector(left.dx * right, left.dy * right);
    }

    inline Vector operator*(const myFloat &left, const Vector &right) {
        return Vector(right.dx * left, right.dy * left);
    }

}

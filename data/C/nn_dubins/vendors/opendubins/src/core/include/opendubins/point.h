/*
 * point.h
 *
 *  Created on: 18. 7. 2014
 *      Author: Petr Vana
 */

#pragma once

#include "vector.h"

namespace opendubins {

    class Point {
    public:
        myFloat x;
        myFloat y;

        Point() {
            x = 0;
            y = 0;
        }

        Point(myFloat x, myFloat y) {
            this->x = x;
            this->y = y;
        }

        inline myFloat getX() {
            return x;
        }

        inline myFloat getY() {
            return y;
        }

        inline Vector operator-(const Point &r) {
            return Vector(x - r.x, y - r.y);
        }

        inline Vector operator-(const Point &r) const {
            return Vector(x - r.x, y - r.y);
        }

        inline Point operator+(const Vector &right) const {
            return Point(x + right.dx, y + right.dy);
        }

        inline Point operator-(const Vector &right) const {
            return Point(x - right.dx, y - right.dy);
        }

        inline Point &operator+=(const Vector &rhs) {
            this->x += rhs.dx;
            this->y += rhs.dy;
            return *this;
        }

        inline Point &operator+=(const Point &rhs) {
            this->x += rhs.x;
            this->y += rhs.y;
            return *this;
        }

        inline Point &operator-=(const Vector &rhs) {
            this->x -= rhs.dx;
            this->y -= rhs.dy;
            return *this;
        }

        inline Point &operator-=(const Point &rhs) {
            this->x -= rhs.x;
            this->y -= rhs.y;
            return *this;
        }

        inline Point operator+(const Point &right) const {
            return Point(x + right.x, y + right.y);
        }

        inline Point operator/(const myFloat div) {
            if (div != 0)
                return Point(x / div, y / div);
            else
                return Point();
        }

        inline myFloat distance(const Point &to) const {
            return (*this - to).length();
        }

        inline myFloat distanceSquared(const Point &to) const {
            return (*this - to).lengthSquared();
        }

        inline Point interpolate(const Point &p, myFloat &alpha) {
            myFloat beta = 1 - alpha;
            return Point(beta * x + alpha * p.x, beta * y + alpha * p.y);
        }

        inline bool operator==(const Point &b) const {
            return x == b.x && y == b.y;
        }

        inline bool operator!=(const Point &b) const {
            return !(*this == b);
        }

        inline size_t hash() const {
            auto h1 = std::hash<opendubins::myFloat>()(x);
            auto h2 = std::hash<opendubins::myFloat>()(y);
            return h1 ^ (h2 << 1);
        }
    };

    inline std::ostream &operator<<(std::ostream &os, const Point &d) {
        os << "Point: (" << d.x << ", " << d.y << ")";
        return os;
    }

}

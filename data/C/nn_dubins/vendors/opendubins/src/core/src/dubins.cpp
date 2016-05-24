/*
 * dubins.cpp
 *
 *  Created on: 20. 7. 2014
 *      Author: Petr Vana
 */

#include "opendubins/dubins.h"

#include <iomanip>

using namespace std;

namespace opendubins {

    Dubins::Dubins() :
            len1(NAN), len2(NAN), len3(NAN), radius(NAN), isCCC(false), length(NAN), type(
            DType::Unknown) {
    }

    Dubins::Dubins(State pos, bool isCCC, myFloat le1, myFloat le2, myFloat le3, myFloat rad) {
        start = pos;
        radius = rad;
        this->radius = rad;
        this->isCCC = isCCC;
        len1 = le1;
        len2 = le2;
        len3 = le3;
        calculateLength();
        end = getSecondArc().getEnd();
    }

    Dubins::~Dubins() { }

    bool Dubins::check() {
        return end.point.distance(getSecondArc().getEnd().point) < ((5 + 2 * length) * TOLERANCE);
    }

    State Dubins::getState(myFloat len) const {
        Arc path1 = getFirstArc();
        myFloat l1 = path1.getLength();
        if (len < l1) {
            return path1.getState(len);
        }

        myFloat l2;
        if (isCCC) {
            Arc ca = getCenterArc();
            l2 = ca.getLength();
            if (len < l1 + l2) {
                return ca.getState(len - l1);
            }
        } else {
            Line cl = getCenter();
            l2 = cl.getLength();
            if (len < l1 + l2) {
                return cl.getState(len - l1);
            }
        }

        Arc path3 = getSecondArc();
        return path3.getState(len - l1 - l2);
    }

    Intersection Dubins::getClosestIntersection(const Point &p) const {
        Intersection closest;

        closest.state = start;
        closest.distance = 0;

        auto a1c = getFirstArc().getClosestIntersection(p);
        if (a1c.state.point.distance(p) < closest.state.point.distance(p)) {
            closest = a1c;
        }

        auto a2c = getSecondArc().getClosestIntersection(p);
        if (a2c.state.point.distance(p) < closest.state.point.distance(p)) {
            closest = a2c;
        }

        Intersection a3c;
        if (isCCC) {
            Arc ca = getCenterArc();
            a3c = ca.getClosestIntersection(p);
        } else {
            Line cl = getCenter();
            a3c = cl.getClosestIntersection(p);
        }

        if (a3c.state.point.distance(p) < closest.state.point.distance(p)) {
            closest = a3c;
        }

        return closest;
    }

    Arc Dubins::getFirstArc() const {
        auto st = start;
        return Arc(st, len1, radius);
    }

    Line Dubins::getCenter() const {
        return Line(getFirstArc().getEnd(), len2);
    }

    Arc Dubins::getCenterArc() const {
        State p = getFirstArc().getEnd();
        return Arc(p, len2, radius);
    }

    Arc Dubins::getSecondArc() const {
        State st;
        if (isCCC) {
            st = getCenterArc().getEnd();
        } else {
            Point ps = getCenter().p2;
            st = State(ps, start.ang + len1);
        }
        return Arc(st, len3, radius);
    }

    Intersection Dubins::intersectLine(const Line &line) const {

        Intersection p = getFirstArc().intersectionPoint(line);
        if (!p.state.invalid()) {
            return p;
        }

        if (isCCC) {
            p = getCenterArc().intersectionPoint(line);
            if (!p.state.invalid()) {
                return p;
            }
        } else {
            p = getCenter().intersectionPoint(line);
            if (!p.state.invalid()) {
                return p;
            }
        }

        p = getSecondArc().intersectionPoint(line);
        if (!p.state.invalid()) {
            return p;
        }

        return Intersection(State(), 0);
    }

    bool Dubins::intersectLineBool(const Line &line) const {
        if (!getFirstArc().intersectionPoint(line).state.invalid()) {
            return true;
        }

        if (isCCC) {
            if (!getCenterArc().intersectionPoint(line).state.invalid()) {
                return true;
            }
        } else {
            if (!getCenter().intersectionPoint(line).state.invalid()) {
                return true;
            }
        }

        if (!getSecondArc().intersectionPoint(line).state.invalid()) {
            return true;
        }

        return false;
    }

    ostream &operator<<(ostream &os, const Dubins &d) {
        os << "Dubins maneuver " << d.start << " --> " << d.end << endl
        << (d.isCCC ? "CCC" : "CSC") << " type "
        << setprecision(5)
        << "\tlen = " << d.getLength()
        << "\t("
        << "n1 = " << d.getLen1()
        << ", n2 = " << d.getLen2()
        << ", n3 = " << d.getLen3()
        << ")";

        return os;
    }
}

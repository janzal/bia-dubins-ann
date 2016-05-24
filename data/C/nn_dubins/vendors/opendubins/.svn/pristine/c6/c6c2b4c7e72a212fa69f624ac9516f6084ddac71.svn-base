/*
 * dubins.h
 *
 *  Created on: 20. 7. 2014
 *      Author: Petr Vana
 */

#pragma once

#include "dtype.h"
#include "line.h"
#include "arc.h"
#include "angleinterval.h"

namespace opendubins {

    class Dubins : public Path {

    private:
        // in radians (positive - left, negative - right) or in meters (straight)
        myFloat len1, len2, len3;

        DType type;

    public:

        State start;
        State end;

        myFloat radius;

        bool isCCC;

        myFloat length;

        // default constructor
        Dubins();

        // classical Dubins maneuver
        Dubins(State from, State to, myFloat radius);

        // Dubins Interval Problem (DIP)
        Dubins(AngleInterval from, AngleInterval to, myFloat radius);

        // Generalited Dubins Interval Problem (GDIP)
        // diff1 - neighborhood around the start state
        // diff2 - neighborhood around the end state
        Dubins(AngleInterval from, AngleInterval to, myFloat radius, myFloat diff1, myFloat diff2);

        Dubins(State pos, bool isCCC, myFloat le1, myFloat le2, myFloat le3, myFloat radius);

        virtual ~Dubins();

        bool check();

        virtual State getState(myFloat len) const;

        virtual Intersection getClosestIntersection(const Point &p) const;

        Arc getFirstArc() const;

        Line getCenter() const;

        Arc getCenterArc() const;

        Arc getSecondArc() const;

        Intersection intersectLine(const Line &line) const;

        bool intersectLineBool(const Line &line) const;

        inline myFloat getLength() const {
            return length;
        }

        inline bool getIsCCC() const {
            return isCCC;
        }

        inline myFloat getLen1() const {
            return len1;
        }

        inline myFloat getLen2() const {
            return len2;
        }

        inline myFloat getLen3() const {
            return len3;
        }

        inline myFloat getRadius() const {
            return radius;
        }

        inline void calculateLength() {
            if (isCCC) {
                length = radius * (fabs(len1) + fabs(len2) + fabs(len3));
            } else {
                length = len2 + radius * (fabs(len1) + fabs(len3));
            }
        }

        inline myFloat getTotalTurning() {
            return fabs(len1) + fabs(len3);
        }

        inline DType getType() {
            return type;
        }

    private:

        void init(State from, State to);

        void initIntervalProblem(AngleInterval from, AngleInterval to);

        void initGDIP(AngleInterval from, AngleInterval to, myFloat diff1, myFloat diff2);

        void GDIP_S(AngleInterval &from, Point &to, myFloat &diff1, myFloat &diff2);

        void GDIP_RS(State from, AngleInterval &to, myFloat &diff1, myFloat &diff2);

    };

    std::ostream &operator<<(std::ostream &os, const Dubins &d);

}

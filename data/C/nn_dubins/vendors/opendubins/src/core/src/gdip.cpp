/*
 * gdip.cpp - Generalized Dubins Interval Problem - shortest path connecting tow states with heading intervals
 *
 *  Created on: Mar 8, 2016
 *      Author: Petr Vana
 */

#include <iomanip>
#include "opendubins/dubins.h"
#include "opendubins/circle.h"

using namespace std;

#define USE_XpXp 0

namespace opendubins {

    Dubins::Dubins(AngleInterval from, AngleInterval to, myFloat newRadius, myFloat diff1, myFloat diff2) {
        radius = newRadius;
        length = std::numeric_limits<myFloat>::max();
        type = DType::Unknown;
        initGDIP(from, to, diff1, diff2);
    }

    void Dubins::GDIP_S(AngleInterval &from, Point &to, myFloat &diff1, myFloat &diff2) {

        const auto totalDiff = diff1 + diff2;

        Vector diff = to - from.point;
        myFloat diffAng = diff.getAngle();

        if (diff.length() < totalDiff) { // no move needed
            isCCC = false;
            length = len1 = len2 = len3 = 0;
            myFloat ang = from.rightDir + from.diff / 2;
            start = State(from.point, ang);
            end = State(from.point, ang);
        } else {
            if (from.inInterval(diffAng)) { // the shortest S maneuver is in interval
                auto intersection = to + diff.normalize() * -totalDiff;
                auto nLen = intersection.distance(from.point);
                if (nLen < length) {
                    isCCC = false;
                    len1 = len3 = 0;
                    length = len2 = nLen;
                    start = State(from.point, diffAng);
                    end = State(intersection, diffAng);
                }
            } else { // solution is at the edge of the interval
                Circle ng = Circle(to, totalDiff);

                State halfLine1 = State(from.point, from.getRight());
                auto intersec1 = ng.halfLineIntersection(halfLine1);
                if (intersec1.x != NAN) {
                    auto nLen = from.point.distance(intersec1);
                    if (nLen < length) {
                        isCCC = false;
                        len1 = len3 = 0;
                        length = len2 = nLen;
                        start = State(from.point, halfLine1.ang);
                        end = State(intersec1, halfLine1.ang);
                    }
                }

                State halfLine2 = State(from.point, from.getLeft());
                auto intersec2 = ng.halfLineIntersection(halfLine2);
                if (intersec2.x != NAN) {
                    auto nLen = from.point.distance(intersec2);
                    if (nLen < length) {
                        isCCC = false;
                        len1 = len3 = 0;
                        length = len2 = nLen;
                        start = State(from.point, halfLine2.ang);
                        end = State(intersec2, halfLine2.ang);
                    }
                }

            } // else there is no intersection with the neighborhood circle
        }
    }

    void Dubins::GDIP_RS(State from, AngleInterval &to, myFloat &diff1, myFloat &diff2) {

        //cout << "GDIP_RS xxxxxxxxxx " << endl;

        const auto totalDiff = diff1 + diff2;

        Vector dir1radius = from.getNormalizedDirection() * radius;
        // center of the turning circle
        Point c1right = from.point + dir1radius.right();

        // vector from the center of the right turn to the goal point
        Vector diff = to.point - c1right;

        myFloat len = diff.length();
        if (radius <= len) { // RS maneuver
            myFloat alpha = asin(radius / len);
            myFloat directionS = diff.getAngle() - alpha;
            myFloat turn = angleToRight(from.ang, directionS);

            State st = from;
            Arc arc(st, turn, radius);
            myFloat lenS = arc.getEnd().point.distance(to.point);

            if (to.inInterval(directionS)) {
                auto lenS2 = max(0.0, lenS - totalDiff);
                myFloat nLen = lenS2 - radius * turn;

                //cout << "Length " << nLen << " ------------ RS" << endl;

                if (nLen < length) {

                    length = nLen;
                    isCCC = false;
                    len1 = turn;
                    len2 = lenS2;
                    len3 = 0;

                    // TODO - change positions
                    start = st;
                    end = State(to.point - Vector(directionS) * (lenS - lenS2), directionS);

                    type = DType::GDIP_RS;
                }
            } else {
                Circle goal(to.point, totalDiff);

                // termination angle is on right edge of the termination interval
                auto turn1 = angleToRight(from.ang, to.getRight());
                auto rEnd1 = Arc(from, turn1, radius).getEnd();
                if (to.inInterval(rEnd1.ang)) {
                    auto intersect1 = goal.halfLineIntersection(rEnd1);

                    if (intersect1.x != NAN) {
                        if (Vector(rEnd1.ang).dotProduct(intersect1 - rEnd1.point) > 0) {
                            auto lenS = intersect1.distance(rEnd1.point);
                            auto nLen = lenS - radius * turn1;
                            if (nLen < length) {

                                //cout << "Length " << nLen << " +++++++++++ RS" << endl;

                                length = nLen;
                                isCCC = false;
                                len1 = turn1;
                                len2 = lenS;
                                len3 = 0;

                                // TODO - change positions
                                start = st;
                                end = State(intersect1, rEnd1.ang);

                                type = DType::GDIP_RS;
                            }
                        }

                    }
                }

                // TODO

                // termination angle is on right edge of the termination interval
                auto turn2 = angleToRight(from.ang, to.getLeft());
                auto rEnd2 = Arc(from, turn2, radius).getEnd();

                if (to.inInterval(rEnd2.ang)) {
                    auto intersect2 = goal.halfLineIntersection(rEnd2);

                    if (intersect2.x != NAN) {
                        if (Vector(rEnd2.ang).dotProduct(intersect2 - rEnd2.point) > 0) {
                            auto lenS = intersect2.distance(rEnd2.point);
                            auto nLen = lenS - radius * turn2;
                            if (nLen < length) {

                                //cout << "Length " << nLen << " ============== RS" << endl;

                                length = nLen;
                                isCCC = false;
                                len1 = turn2;
                                len2 = lenS;
                                len3 = 0;

                                // TODO - change positions
                                start = st;
                                end = State(intersect2, rEnd2.ang);

                                type = DType::GDIP_RS;
                            }
                        }

                    }

                }
            }

            //cout << "not R maneuver " << endl;

        } else { // possible R maneuver

            // todo - implement R maneuver

            //cout << "R maneuver " << endl;
        }
    }

    void Dubins::initGDIP(AngleInterval from, AngleInterval to, myFloat diff1, myFloat diff2) {

        initIntervalProblem(from, to);

        // ends of intervals:
        // from(A,B)
        const auto A = from.getRight();
        const auto B = from.getLeft();
        //  to(C,D)
        const auto C = to.getRight();
        const auto D = to.getLeft();

        // size of the global neighborhood circle
        const auto totalDiff = diff1 + diff2;

        /////////////////////////////////////////////////////////////////////////
        // CASE 1 - S

        // intersection of intervals from(A,B) to (C,D)
        // detection is based on  1) is A in (C,D)?    2) is B in (C,D)?
        bool AinCD = to.inInterval(A);
        bool BinCD = to.inInterval(B);

        int numberOfIntersection = 0;
        AngleInterval firstInterval;
        AngleInterval secondInterval;

        // start is consicered as a point and end as a circle with radius = diff1 + diff2
        firstInterval.point = secondInterval.point = from.point;

        if (AinCD && BinCD) {
            // there are two options: (A,B) or {(C,B),(A,D)}
            if (angleToLeft(C, B) > angleToLeft(C, A)) {
                // intersection is (A,B)
                numberOfIntersection = 1;
                firstInterval = from;
            } else {
                // TODO
                // intersection is {(C,B),(A,D)}
                numberOfIntersection = 2;

                firstInterval.rightDir = C;
                firstInterval.diff = angleToLeft(C, B);

                secondInterval.rightDir = A;
                secondInterval.diff = angleToLeft(A, D);
            }
        } else if (AinCD) { // not BinCD
            // intersection is (A,D)
            numberOfIntersection = 1;
            firstInterval.rightDir = A;
            firstInterval.diff = angleToLeft(A, D);
        } else if (BinCD) { // not AinCD
            // intersection is (C,B)
            numberOfIntersection = 1;
            firstInterval.rightDir = C;
            firstInterval.diff = angleToLeft(C, B);
        } else {
            if (from.inInterval(C) || from.inInterval(D)) {
                // intersection is (C,D)
                numberOfIntersection = 1;
                firstInterval.rightDir = C;
                firstInterval.diff = angleToLeft(C, D);
            }
        }

        if (numberOfIntersection > 0) { // first interval
            GDIP_S(firstInterval, to.point, diff1, diff2);
        }

        if (numberOfIntersection > 1) { // second interval
            GDIP_S(secondInterval, to.point, diff1, diff2);
        }

        // R and RS maneuver
        GDIP_RS(from.getRightState(), to, diff1, diff2);

        // TODO - implement other types

    }

}

/*
 * dip.cpp - Dubins Interval Problem - shortest path connecting tow states with heading intervals
 *
 *  Created on: Mar 8, 2016
 *      Author: Petr Vana
 */

#include <iomanip>
#include "opendubins/dubins.h"

namespace opendubins {

    Dubins::Dubins(AngleInterval from, AngleInterval to, myFloat newRadius) {
        radius = newRadius;
        length = std::numeric_limits<myFloat>::max();
        type = DType::Unknown;
        initIntervalProblem(from, to);
    }

// implementation of dubins Interval Problem
// based on article http://arxiv.org/pdf/1507.06980v2.pdf
    void Dubins::initIntervalProblem(AngleInterval from, AngleInterval to) {
        const Vector dir = to.point - from.point;
        const myFloat dir_length = dir.length();
        const myFloat dir_ang = dir.getAngle();

        ///////////////////////////////
        // CASE 1

        // Straight line S
        myFloat theta = dir.getAngle();
        if (from.inInterval(theta) && to.inInterval(theta)) {
            isCCC = false;
            len1 = len3 = 0;
            length = len2 = dir.length();
            start = State(from.point, theta);
            end = State(to.point, theta);
            type = DType::DIP_S;
        }

        ///////
        // + is greater then 1*PI
        // L+, R+, L+R+, R+L+

        // L+, R+
        if (dir_length < 2 * radius) {
            myFloat alpha = asin(dir_length / 2 / radius);

            // L+
            {
                myFloat dir1 = dir_ang + M_PI + alpha;
                myFloat dir2 = dir_ang + M_PI - alpha;

                myFloat turn = angleToLeft(dir1, dir2);

                myFloat nLen = radius * turn;
                if (nLen < length) {
                    if (from.inInterval(dir1) && to.inInterval(dir2)) {
                        length = nLen;
                        isCCC = false;
                        len1 = turn;
                        len2 = 0;
                        len3 = 0;

                        start = State(from.point, dir1);
                        end = State(to.point, dir2);

                        type = DType::DIP_Lp;
                    }
                }
            }

            // R+
            {
                myFloat dir1 = dir_ang + M_PI - alpha;
                myFloat dir2 = dir_ang + M_PI + alpha;

                myFloat turn = angleToRight(dir1, dir2);

                myFloat nLen = -radius * turn;
                if (nLen < length) {
                    if (from.inInterval(dir1) && to.inInterval(dir2)) {
                        length = nLen;
                        isCCC = false;
                        len1 = turn;
                        len2 = 0;
                        len3 = 0;

                        start = State(from.point, dir1);
                        end = State(to.point, dir2);

                        type = DType::DIP_Rp;
                    }
                }
            }
        }

#if USE_XpXp
        // R+L+, L+R+
        if (dir_length < 4 * radius) {

            myFloat alpha = asin(dir_length / 4 / radius);

            // TODO - implement unit test first
            // R+L+
            {
                myFloat dir1 = dir_ang + M_PI - alpha;
                myFloat dir2 = dir_ang + M_PI + alpha;

                myFloat turn = angleToRight(dir1, dir2);

                myFloat nLen = - 2 * radius * turn;
                if (nLen < length) {
                    if (from.inInterval(dir1) && to.inInterval(dir2)) {
                        length = nLen;
                        isCCC = false;
                        len1 = turn;
                        len2 = 0;
                        len3 = -turn;

                        start = State(from.point, dir1);
                        end = State(to.point, dir2);

                        type = DType::DIP_RpLp;
                    }
                }
            }
            // TODO - implement

            // L+R+
            {
                myFloat dir1 = dir_ang + M_PI + alpha;
                myFloat dir2 = dir_ang + M_PI - alpha;

                myFloat turn = angleToLeft(dir1, dir2);

                myFloat nLen = 2 * radius * turn;
                if (nLen < length) {
                    if (from.inInterval(dir1) && to.inInterval(dir2)) {
                        length = nLen;
                        isCCC = false;
                        len1 = turn;
                        len2 = 0;
                        len3 = -turn;

                        start = State(from.point, dir1);
                        end = State(to.point, dir2);

                        type = DType::DIP_LpRp;
                    }
                }
            }
            // TODO - implement
        }
#endif

        ///////////////////////////////
        // CASE 2
        // on boundaries of angle interval
        // LSR, LSL, LR+L, RSL, RSR, RL+R
        init(from.getRightState(), to.getRightState());
        init(from.getRightState(), to.getLeftState());
        init(from.getLeftState(), to.getRightState());
        init(from.getLeftState(), to.getLeftState());

        ///////////////////////////////
        // CASE 3 - limited by first interval
        // LS, LR+, RS, RL+

        // LS
        {
            Vector dir1radius = from.getLeftDir() * radius;
            // center of the turning circle
            Point c1left = from.point + dir1radius.left();

            // vector from the center of the left turn to the goal point
            Vector diff = to.point - c1left;

            myFloat len = diff.length();
            if (radius <= len) {
                myFloat alpha = asin(radius / len);
                myFloat directionS = diff.getAngle() + alpha;
                myFloat turn = angleToLeft(from.getLeft(), directionS);

                State st = from.getLeftState();
                Arc arc(st, turn, radius);
                myFloat lenS = arc.getEnd().point.distance(to.point);

                myFloat nLen = lenS + radius * turn;
                if (nLen < length) {
                    if (to.inInterval(directionS)) {
                        length = nLen;
                        isCCC = false;
                        len1 = turn;
                        len2 = lenS;
                        len3 = 0;

                        start = st;
                        end = State(to.point, directionS);

                        type = DType::DIP_LS;
                    }
                }
            }


        }

        // LR+
        {
            // center of the turning circle
            Point c1left = from.point + from.getLeftDir().left() * radius;

            // vector from first center to target point
            Vector diff = to.point - c1left;

            myFloat len = diff.length();
            if (radius < len && len < 3 * radius) {

                // angle in triangle 2R, R, len
                myFloat alpha = acos((3 * radius * radius + len * len) / (4 * radius * len));

                { // first option + alpha
                    // direction between segments
                    myFloat centerDir = diff.left().getAngle() + alpha;

                    // length of the first turning maneuver (L)
                    myFloat turn1 = angleToLeft(from.getLeftDir().getAngle(), centerDir);
                    //std::cout << "turn 1 " << turn1 << " alpha " << alpha << std::endl;

                    State fp = from.getLeftState();
                    Arc left(fp, turn1, radius);
                    Point centerPoint = left.getEnd().point;

                    // L+
                    myFloat dir2 = centerPoint.distance(to.point);
                    myFloat dirAng2 = (to.point - centerPoint).getAngle();
                    if (dir2 < 2 * radius) {
                        myFloat alpha2 = asin(dir2 / 2 / radius);

                        myFloat turn2 = -2 * M_PI + 2 * alpha2;
                        myFloat dir2 = from.getLeft() + turn1 + turn2;

                        myFloat nLen = radius * (turn1 - turn2);
                        //std::cout << "turn 1 " << turn1 << " turn2 " << turn2 << " alpha " << alpha << " len " << nLen << std::endl;
                        if (nLen < length) {
                            if (to.inInterval(dir2)) {
                                length = nLen;
                                isCCC = false;
                                len1 = turn1;
                                len2 = 0;
                                len3 = turn2;

                                start = from.getLeftState();
                                end = State(to.point, dir2);

                                type = DType::DIP_LRp;
                            }
                        }
                    }
                }
            }
        }

        // RS
        {
            Vector dir1radius = from.getRightDir() * radius;
            // center of the turning circle
            Point c1right = from.point + dir1radius.right();

            // vector from the center of the right turn to the goal point
            Vector diff = to.point - c1right;

            myFloat len = diff.length();
            if (radius <= len) {
                myFloat alpha = asin(radius / len);
                myFloat directionS = diff.getAngle() - alpha;
                myFloat turn = angleToRight(from.getRight(), directionS);

                State st = from.getRightState();
                Arc arc(st, turn, radius);
                myFloat lenS = arc.getEnd().point.distance(to.point);

                myFloat nLen = lenS - radius * turn;
                if (nLen < length) {
                    if (to.inInterval(directionS)) {
                        length = nLen;
                        isCCC = false;
                        len1 = turn;
                        len2 = lenS;
                        len3 = 0;

                        start = st;
                        end = State(to.point, directionS);

                        type = DType::DIP_RS;
                    }
                }
            }

        }

        // RL+
        {
            // center of the turning circle
            Point c1right = from.point + from.getRightDir().right() * radius;

            // vector from first center to target point
            Vector diff = to.point - c1right;

            myFloat len = diff.length();
            if (radius < len && len < 3 * radius) {

                // angle in triangle 2R, R, len
                myFloat alpha = acos((3 * radius * radius + len * len) / (4 * radius * len));

                { // first option + alpha
                    // direction between segments
                    myFloat centerDir = diff.right().getAngle() - alpha;

                    // length of the first turning maneuver (L)
                    myFloat turn1 = angleToRight(from.getRightDir().getAngle(), centerDir);
                    //std::cout << "turn 1 " << turn1 << " alpha " << alpha << std::endl;

                    State fp = from.getRightState();
                    Arc right(fp, turn1, radius);
                    Point centerPoint = right.getEnd().point;

                    // R+
                    myFloat dir2 = centerPoint.distance(to.point);
                    myFloat dirAng2 = (to.point - centerPoint).getAngle();
                    if (dir2 < 2 * radius) {
                        myFloat alpha2 = asin(dir2 / 2 / radius);

                        myFloat turn2 = 2 * M_PI - 2 * alpha2;
                        myFloat dir2 = from.getRight() + turn1 + turn2;

                        myFloat nLen = radius * (-turn1 + turn2);
                        //std::cout << "turn 1 " << turn1 << " turn2 " << turn2 << " alpha " << alpha << " len " << nLen << std::endl;
                        if (nLen < length) {
                            if (to.inInterval(dir2)) {
                                length = nLen;
                                isCCC = false;
                                len1 = turn1;
                                len2 = 0;
                                len3 = turn2;

                                start = from.getRightState();
                                end = State(to.point, dir2);

                                type = DType::DIP_RLp;
                            }
                        }
                    }
                }
            }
        }

        ///////////////////////////////
        // CASE 3 - limited by second interval
        // SR, SL, L+R, R+L

        // SR
        {
            Vector dir1radius = to.getLeftDir() * radius;
            // center of the turning circle
            Point c1right = to.point + dir1radius.right();

            // vector from the center of the right turn to the goal point
            Vector diff = c1right - from.point;

            myFloat len = diff.length();
            if (radius <= len) {
                myFloat alpha = asin(radius / len);
                myFloat directionS = diff.getAngle() + alpha;
                myFloat turn = angleToRight(directionS, to.getLeft());

                State st = to.getLeftState();
                st.ang += M_PI;
                Arc arc(st, -turn, radius);
                myFloat lenS = arc.getEnd().point.distance(from.point);

                myFloat nLen = lenS - radius * turn;

                if (nLen < length) {
                    if (from.inInterval(directionS)) {

                        length = nLen;
                        isCCC = false;
                        len1 = 0;
                        len2 = lenS;
                        len3 = turn;

                        start = State(from.point, directionS);
                        end = to.getLeftState();

                        type = DType::DIP_SR;
                    }
                }
            }
        }

        // SL
        {
            Vector dir1radius = to.getRightDir() * radius;
            // center of the turning circle
            Point c1left = to.point + dir1radius.left();

            // vector from the center of the left turn to the goal point
            Vector diff = c1left - from.point;

            myFloat len = diff.length();
            if (radius <= len) {
                myFloat alpha = asin(radius / len);
                myFloat directionS = diff.getAngle() - alpha;
                myFloat turn = angleToLeft(directionS, to.getRight());

                State st = to.getRightState();
                st.ang += M_PI;
                Arc arc(st, -turn, radius);
                myFloat lenS = arc.getEnd().point.distance(from.point);

                myFloat nLen = lenS + radius * turn;

                if (nLen < length) {
                    if (from.inInterval(directionS)) {
                        length = nLen;
                        isCCC = false;
                        len1 = 0;
                        len2 = lenS;
                        len3 = turn;

                        start = State(from.point, directionS);
                        end = to.getRightState();

                        type = DType::DIP_SL;
                    }
                }
            }
        }

        // L+R
        {
            // center of the turning circle
            Point c1right = to.point + to.getLeftDir().right() * radius;

            // vector from first center to target point
            Vector diff = from.point - c1right;

            myFloat len = diff.length();
            if (radius < len && len < 3 * radius) {

                // angle in triangle 2R, R, len
                myFloat alpha = acos((3 * radius * radius + len * len) / (4 * radius * len));

                { // first option + alpha
                    // direction between segments
                    myFloat centerDir = diff.right().getAngle() + alpha;

                    // length of the second turning maneuver (R)
                    myFloat turn2 = angleToRight(centerDir, to.getLeft());
                    //std::cout << "turn 1 " << turn1 << " alpha " << alpha << std::endl;

                    State fp = State(to.point, to.getLeft() + M_PI);
                    Arc back(fp, -turn2, radius);
                    Point centerPoint = back.getEnd().point;

                    // L+
                    myFloat dir2 = centerPoint.distance(from.point);
                    if (dir2 < 2 * radius) {
                        myFloat alpha2 = asin(dir2 / 2 / radius);

                        myFloat turn1 = 2 * M_PI - 2 * alpha2;
                        myFloat dir1 = to.getLeft() - turn1 - turn2;

                        myFloat nLen = radius * (turn1 - turn2);
                        //std::cout << "turn 1 " << turn1 << " turn2 " << turn2 << " alpha " << alpha << " len " << nLen << std::endl;
                        if (nLen < length) {
                            if (from.inInterval(dir1)) {
                                length = nLen;
                                isCCC = false;
                                len1 = turn1;
                                len2 = 0;
                                len3 = turn2;

                                start = State(from.point, dir1);
                                end = to.getLeftState();

                                type = DType::DIP_LpR;
                            }
                        }
                    }
                }
            }
        }

        // R+L
        {
            // center of the turning circle
            Point c1left = to.point + to.getRightDir().left() * radius;

            // vector from first center to target point
            Vector diff = from.point - c1left;

            myFloat len = diff.length();
            if (radius < len && len < 3 * radius) {

                // angle in triangle 2R, R, len
                myFloat alpha = acos((3 * radius * radius + len * len) / (4 * radius * len));

                { // first option + alpha
                    // direction between segments
                    myFloat centerDir = diff.left().getAngle() - alpha;

                    // length of the second turning maneuver (L)
                    myFloat turn2 = angleToLeft(centerDir, to.getRight());
                    //std::cout << "turn 1 " << turn1 << " alpha " << alpha << std::endl;

                    State fp = State(to.point, to.getRight() + M_PI);
                    Arc back(fp, -turn2, radius);
                    Point centerPoint = back.getEnd().point;

                    // L+
                    myFloat dir2 = centerPoint.distance(from.point);
                    if (dir2 < 2 * radius) {
                        myFloat alpha2 = asin(dir2 / 2 / radius);

                        myFloat turn1 = -2 * M_PI + 2 * alpha2;
                        myFloat dir1 = to.getRight() - turn1 - turn2;

                        myFloat nLen = radius * (-turn1 + turn2);
                        //std::cout << "turn 1 " << turn1 << " turn2 " << turn2 << " alpha " << alpha << " len " << nLen << std::endl;
                        if (nLen < length) {
                            if (from.inInterval(dir1)) {
                                length = nLen;
                                isCCC = false;
                                len1 = turn1;
                                len2 = 0;
                                len3 = turn2;

                                start = State(from.point, dir1);
                                end = to.getRightState();

                                type = DType::DIP_RpL;
                            }
                        }
                    }
                }
            }
        }
    }

}

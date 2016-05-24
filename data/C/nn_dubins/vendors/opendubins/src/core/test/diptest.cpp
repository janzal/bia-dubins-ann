/*
 * diptest.cpp
 *
 *  Created on: Dec 7, 2015
 *      Author: Petr Vana
 */

#include "gtest/gtest.h"
#include "opendubins/dubins.h"

using namespace std;
using namespace opendubins;

namespace diptest {

    const int COUNT = 1000;

    int typeCount[200] = {};

    void check(AngleInterval &interval1, AngleInterval &interval2, Dubins &d1, Dubins &d2) {

        //if (d2.getType() != Unknown) {
        EXPECT_TRUE(d1.check()) << "incorrect original maneuver";
        EXPECT_TRUE(d2.check()) << "incorrect newly created maneuver form intervals";
        EXPECT_TRUE(interval1.inIntervalWithTollerance(d2.start.ang, TOLERANCE))
                            << "out of first interval";
        EXPECT_TRUE(interval2.inIntervalWithTollerance(d2.end.ang, TOLERANCE))
                            << "out of second interval";
        EXPECT_GE(d1.length + TOLERANCE, d2.length) << "DubinsInterval is longer than original maneuver";

        myFloat len2 = d2.getFirstArc().getLength() + d2.getSecondArc().getLength();
        if (d2.isCCC) {
            len2 += d2.getCenterArc().getLength();
        } else {
            len2 += d2.getCenter().getLength();
        }

        EXPECT_LE(fabs(d2.length - len2), TOLERANCE)
                            << "Incorrect length calculation";

        typeCount[(int) d2.getType()]++;
    }

    Dubins checkUsingIntervals(Dubins &d1, myFloat a1, myFloat b1, myFloat a2, myFloat b2) {
        myFloat a = myRandom() * a1;
        myFloat b = myRandom() * b1;

        AngleInterval interval1 = AngleInterval(d1.start.point, d1.start.getAngle() - a, b + a);

        a = myRandom() * a2;
        b = myRandom() * b2;

        AngleInterval interval2 = AngleInterval(d1.end.point, d1.end.getAngle() - a, b + a);

        Dubins d2(interval1, interval2, d1.radius);
        check(interval1, interval2, d1, d2);

        return d2;
    }

    myFloat getRadius() {
        return 0.1 + 3 * myRandom();
    }

    TEST (DIP, ZeroInterval) {
        State p1 = State(Point(0, 0), 0);
        State p2 = State(Point(0, 0), 0);

        for (int i = 0; i < COUNT; ++i) {
            p1.random(100);
            p2.random(100);
            Dubins d1(p1, p2, getRadius());

            AngleInterval interval1 = AngleInterval(p1.point, p1.ang, 0);
            AngleInterval interval2 = AngleInterval(p2.point, p2.ang, 0);
            Dubins d2(interval1, interval2, d1.radius);

            check(interval1, interval2, d1, d2);
        }
    }

    TEST (DIP, S) {
        State p1 = State(Point(0, 0), 0);
        for (int i = 0; i < COUNT; ++i) {
            p1.random(100);
            Dubins d1(p1, false, 0, myRandom() * 10, 0, getRadius());
            Dubins d2 = checkUsingIntervals(d1, 1, 1, 1, 1);

            EXPECT_TRUE(fabs(d1.length - d2.length) < TOLERANCE) << "Different length of a straight line.";
        }
    }

    TEST (DIP, RS) {
        State p1 = State(Point(0, 0), 0);
        for (int i = 0; i < COUNT; ++i) {
            p1.random(100);
            Dubins d1(p1, false, -myRandom() * 7, myRandom() * 10, 0, getRadius());
            checkUsingIntervals(d1, 0, 1, 1, 1);
        }
    }

    TEST (DIP, LS) {
        State p1 = State(Point(0, 0), 0);
        for (int i = 0; i < COUNT; ++i) {
            p1.random(100);
            Dubins d1(p1, false, myRandom() * 7, myRandom() * 10, 0, getRadius());
            checkUsingIntervals(d1, 1, 0, 1, 1);
        }
    }

    TEST (DIP, SR) {
        State p1 = State(Point(0, 0), 0);
        for (int i = 0; i < COUNT; ++i) {
            p1.random(100);
            Dubins d1(p1, false, 0, myRandom() * 10, -myRandom() * 7, getRadius());
            checkUsingIntervals(d1, 1, 1, 1, 0);
        }
    }

    TEST (DIP, SL) {
        State p1 = State(Point(0, 0), 0);
        for (int i = 0; i < COUNT; ++i) {
            p1.random(100);
            Dubins d1(p1, false, 0, myRandom() * 10, myRandom() * 7, getRadius());
            checkUsingIntervals(d1, 1, 1, 0, 1);
        }
    }

    TEST (DIP, Lp) {
        State p1 = State(Point(0, 0), 0);
        for (int i = 0; i < COUNT; ++i) {
            p1.random(100);
            Dubins d1(p1, false, M_PI + myRandom() * M_PI, 0, 0, getRadius());
            checkUsingIntervals(d1, 0.1, 0.1, 0.1, 0.1);
        }
    }

    TEST (DIP, Rp) {
        State p1 = State(Point(0, 0), 0);
        for (int i = 0; i < COUNT; ++i) {
            p1.random(100);
            Dubins d1(p1, false, -M_PI - myRandom() * M_PI, 0, 0, getRadius());
            checkUsingIntervals(d1, 0.1, 0.1, 0.1, 0.1);
        }
    }

    TEST (DIP, LRp) {
        State p1 = State(Point(0, 0), 0);
        for (int i = 0; i < COUNT; ++i) {
            p1.random(100);

            const myFloat TOL_ANG = 0.05;
            myFloat turn1 = myRandom() * M_PI * (1 - TOL_ANG);
            myFloat turn2 = -M_PI * (1 + TOL_ANG) - myRandom() * M_PI * (1 - 2 * TOL_ANG);

            Dubins d1(p1, false, turn1, 0, turn2, getRadius());
            checkUsingIntervals(d1, 0.1, 0, 0.1, 0.1);
        }
    }

    TEST (DIP, RLp) {
        State p1 = State(Point(0, 0), 0);
        for (int i = 0; i < COUNT; ++i) {
            p1.random(100);

            const myFloat TOL_ANG = 0.05;
            myFloat turn1 = -myRandom() * M_PI * (1 - TOL_ANG);
            myFloat turn2 = +M_PI * (1 + TOL_ANG) + myRandom() * M_PI * (1 - 2 * TOL_ANG);

            Dubins d1(p1, false, turn1, 0, turn2, getRadius());
            checkUsingIntervals(d1, 0, 0.1, 0.1, 0.1);
        }
    }

    TEST (DIP, LpR) {
        State p1 = State(Point(0, 0), 0);
        for (int i = 0; i < COUNT; ++i) {
            p1.random(100);

            const myFloat TOL_ANG = 0.05;
            myFloat turn1 = M_PI * (1 + TOL_ANG) + myRandom() * M_PI * (1 - 2 * TOL_ANG);
            myFloat turn2 = -myRandom() * M_PI * (1 - TOL_ANG);

            Dubins d1(p1, false, turn1, 0, turn2, getRadius());
            checkUsingIntervals(d1, 0.1, 0.1, 0.1, 0);
        }
    }

    TEST (DIP, RpL) {
        State p1 = State(Point(0, 0), 0);
        for (int i = 0; i < COUNT; ++i) {
            p1.random(100);

            const myFloat TOL_ANG = 0.05;
            myFloat turn1 = -M_PI * (1 + TOL_ANG) - myRandom() * M_PI * (1 - 2 * TOL_ANG);
            myFloat turn2 = myRandom() * M_PI * (1 - TOL_ANG);

            Dubins d1(p1, false, turn1, 0, turn2, getRadius());
            checkUsingIntervals(d1, 0.1, 0.1, 0, 0.1);
        }
    }

    TEST (DIP, Small) {
        State p1 = State(Point(0, 0), 0);
        State p2 = State(Point(0, 0), 0);
        for (int i = 0; i < COUNT; ++i) {
            p1.random(5);
            p2.random(5);
            Dubins d1(p1, p2, getRadius());
            checkUsingIntervals(d1, 0.1, 0.1, 0.1, 0.1);
        }
    }

    TEST (DIP, Big) {
        State p1 = State(Point(0, 0), 0);
        State p2 = State(Point(0, 0), 0);
        for (int i = 0; i < COUNT; ++i) {
            p1.random(5);
            p2.random(5);
            Dubins d1(p1, p2, getRadius());
            checkUsingIntervals(d1, 1, 1, 1, 1);
        }
    }

    TEST (DIP, Random) {
        State p1 = State(Point(0, 0), 0);
        for (int i = 0; i < COUNT; ++i) {
            p1.random(5);
            Dubins d1;

            myFloat radius = getRadius();

            myFloat turn1 = 0;
            myFloat turn2 = 0;

            if (myRandom() < 0.5) {
                myFloat center = myRandom() * radius;
                d1 = Dubins(p1, false, turn1, center, turn2, radius);
            } else {
                myFloat centerTurn = (1 + myRandom()) * M_PI;
                d1 = Dubins(p1, true, turn1, centerTurn, turn2, radius);
            }
            checkUsingIntervals(d1, 0.1, 0.1, 0.1, 0.1);
        }
    }

    TEST (DIP, RpLp) {

        int localType[200] = {};

        State p1 = State(Point(0, 0), 0);
        for (int i = 0; i < COUNT; ++i) {
            p1.random(100);
            myFloat turn = M_PI + myRandom() * M_PI;
            Dubins d1(p1, false, -turn, TOLERANCE, turn, getRadius());
            auto epsilon = 0.00001 * myRandom();
            auto d2 = checkUsingIntervals(d1, epsilon, epsilon, epsilon, epsilon);
        }
    }

    TEST (DIP, LpRp) {
        State p1 = State(Point(0, 0), 0);
        for (int i = 0; i < COUNT; ++i) {
            p1.random(100);
            myFloat turn = M_PI + myRandom() * M_PI;
            Dubins d1(p1, false, turn, 0, -turn, getRadius());
            myFloat intervalSize = 3;
            checkUsingIntervals(d1, 0.1, 0.1, 0.1, 0.1);
        }
    }

// this test proves that there is no locally optimal XpXp maneuver
    TEST (DIP, RpLp_epsilon) {

        State p1 = State(Point(0, 0), 0);
        for (int i = 0; i < COUNT; ++i) {
            p1.random(100);
            myFloat turn = M_PI + (0.01 * myRandom()) * M_PI;
            Dubins d1(p1, false, -turn, 0, turn, getRadius());
            auto epsilon = 0.0001 * myRandom();

            auto p1a = d1.start;
            p1a.ang += epsilon;
            auto p1b = d1.start;
            p1b.ang -= epsilon;

            auto p2a = d1.end;
            p2a.ang += epsilon;
            auto p2b = d1.end;
            p2b.ang -= epsilon;

            auto da = Dubins(p1a, p2a, d1.radius);
            auto db = Dubins(p1b, p2a, d1.radius);
            auto dc = Dubins(p1a, p2b, d1.radius);
            auto dd = Dubins(p1b, p2b, d1.radius);

            auto nLen = min(min(da.length, db.length), min(dc.length, dd.length));

            EXPECT_GT(d1.length + TOLERANCE, nLen) << " Locally optimal ";
        }
    }

    TEST (DIP, AllUsed) {

        const int MIN = (int) DType::DIP_S;
#if USE_XpXp
        const int MAX = DType::DIP_RpLp;
#else
        const int MAX = (int) DType::DIP_LpR;
#endif

        for (int t = MIN; t <= MAX; t++) {
            const int value = typeCount[t];
            //std::cout << t << "\t-\t" << value  << endl;
            EXPECT_GT(value, 0) << "There is no maneuver with type " << t;
        }
    }

}

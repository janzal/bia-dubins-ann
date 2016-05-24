/*
 * gdiptest.cpp
 *
 *  Created on: Feb 10, 2016
 *      Author: Petr Vana
 */

#include "gtest/gtest.h"
#include "opendubins/dubins.h"
#include <iostream>

using namespace opendubins;
using namespace std;

const int COUNT = 100;

namespace gdiptest {

    void check2(AngleInterval &interval1, AngleInterval &interval2, Dubins &d1, Dubins &d2) {
        EXPECT_TRUE(d1.check()) << "incorrect original maneuver";
        EXPECT_TRUE(d2.check()) << "incorrect newly created maneuver form intervals";

        bool in1 = interval1.inIntervalWithTollerance(d2.start.ang, TOLERANCE);
        bool in2 = interval2.inIntervalWithTollerance(d2.end.ang, TOLERANCE);
        EXPECT_TRUE(in1) << "out of first interval";
        EXPECT_TRUE(in2) << "out of second interval";
        EXPECT_GE(d1.length + 10 * TOLERANCE, d2.length) << "DubinsInterval is longer than original maneuver";

        if (!in1) {
            cout << "IN1 " << d2.start.ang << " is not in <" << interval1.getRight() << ", " << interval1.getLeft() <<
            endl;
        }
        if (!in2) {
            cout << "IN2 " << d2.end.ang << " is not in <" << interval2.getRight() << ", " << interval2.getLeft() <<
            endl;
        }

        if (d1.length + TOLERANCE < d2.length) {
            std::cout << "First dubins 111111111111 " << std::endl << d1 << std::endl;
            std::cout << "Second dubins 222222222222 " << std::endl << d2 << std::endl;
        }
    }

    Dubins checkUsingIntervals2(Dubins &d1, myFloat a1, myFloat b1, myFloat a2, myFloat b2) {
        myFloat a = myRandom() * a1;
        myFloat b = myRandom() * b1;

        AngleInterval interval1 = AngleInterval(d1.start.point, d1.start.getAngle() - a, b + a);

        a = myRandom() * a2;
        b = myRandom() * b2;

        AngleInterval interval2 = AngleInterval(d1.end.point, d1.end.getAngle() - a, b + a);

        Dubins d2(interval1, interval2, d1.radius, 0, 0);
        check2(interval1, interval2, d1, d2);

        return d2;
    }

    myFloat getRadius2() {
        return 0.1 + 3 * myRandom();
    }

// OLD TESTS FROM DIP ///////////////////////////////////////////////////////////////////

    TEST (GDIP, ZeroInterval) {
        State p1 = State(Point(0, 0), 0);
        State p2 = State(Point(0, 0), 0);

        for (
                int i = 0;
                i < COUNT;
                ++i) {
            p1.random(100);
            p2.random(100);
            Dubins d1(p1, p2, getRadius2());

            AngleInterval interval1 = AngleInterval(p1.point, p1.ang, 0);
            AngleInterval interval2 = AngleInterval(p2.point, p2.ang, 0);
            Dubins d2(interval1, interval2, d1.radius, 0, 0);

            check2(interval1, interval2, d1, d2
            );
        }
    }

    TEST (GDIP, S) {
        State p1 = State(Point(0, 0), 0);
        for (
                int i = 0;
                i < COUNT;
                ++i) {
            p1.random(100);
            Dubins d1(p1, false, 0, myRandom() * 10, 0, getRadius2());
            Dubins d2 = checkUsingIntervals2(d1, 1, 1, 1, 1);

            EXPECT_TRUE(fabs(d1.length - d2.length)
                        < TOLERANCE) << "Different length of a straight line.";
        }
    }

    TEST (GDIP, RS) {
        State p1 = State(Point(0, 0), 0);
        for (
                int i = 0;
                i < COUNT;
                ++i) {
            p1.random(100);
            Dubins d1(p1, false, -myRandom() * 7, myRandom() * 10, 0, getRadius2());
            checkUsingIntervals2(d1,
                                 0, 1, 1, 1);
        }
    }

    TEST (GDIP, LS) {
        State p1 = State(Point(0, 0), 0);
        for (
                int i = 0;
                i < COUNT;
                ++i) {
            p1.random(100);
            Dubins d1(p1, false, myRandom() * 7, myRandom() * 10, 0, getRadius2());
            checkUsingIntervals2(d1,
                                 1, 0, 1, 1);
        }
    }

    TEST (GDIP, SR) {
        State p1 = State(Point(0, 0), 0);
        for (
                int i = 0;
                i < COUNT;
                ++i) {
            p1.random(100);
            Dubins d1(p1, false, 0, myRandom() * 10, -myRandom() * 7, getRadius2());
            checkUsingIntervals2(d1,
                                 1, 1, 1, 0);
        }
    }

    TEST (GDIP, SL) {
        State p1 = State(Point(0, 0), 0);
        for (
                int i = 0;
                i < COUNT;
                ++i) {
            p1.random(100);
            Dubins d1(p1, false, 0, myRandom() * 10, myRandom() * 7, getRadius2());
            checkUsingIntervals2(d1,
                                 1, 1, 0, 1);
        }
    }

    TEST (GDIP, Lp) {
        State p1 = State(Point(0, 0), 0);
        for (
                int i = 0;
                i < COUNT;
                ++i) {
            p1.random(100);
            Dubins d1(p1, false, M_PI + myRandom() * M_PI, 0, 0, getRadius2());
            checkUsingIntervals2(d1,
                                 0.1, 0.1, 0.1, 0.1);
        }
    }

    TEST (GDIP, Rp) {
        State p1 = State(Point(0, 0), 0);
        for (
                int i = 0;
                i < COUNT;
                ++i) {
            p1.random(100);
            Dubins d1(p1, false, -M_PI - myRandom() * M_PI, 0, 0, getRadius2());
            checkUsingIntervals2(d1,
                                 0.1, 0.1, 0.1, 0.1);
        }
    }

    TEST (GDIP, LRp) {
        State p1 = State(Point(0, 0), 0);
        for (
                int i = 0;
                i < COUNT;
                ++i) {
            p1.random(100);

            const myFloat TOL_ANG = 0.05;
            myFloat turn1 = myRandom() * M_PI * (1 - TOL_ANG);
            myFloat turn2 = -M_PI * (1 + TOL_ANG) - myRandom() * M_PI * (1 - 2 * TOL_ANG);

            Dubins d1(p1, false, turn1, 0, turn2, getRadius2());
            checkUsingIntervals2(d1,
                                 0.1, 0, 0.1, 0.1);
        }
    }

    TEST (GDIP, RLp) {
        State p1 = State(Point(0, 0), 0);
        for (
                int i = 0;
                i < COUNT;
                ++i) {
            p1.random(100);

            const myFloat TOL_ANG = 0.05;
            myFloat turn1 = -myRandom() * M_PI * (1 - TOL_ANG);
            myFloat turn2 = +M_PI * (1 + TOL_ANG) + myRandom() * M_PI * (1 - 2 * TOL_ANG);

            Dubins d1(p1, false, turn1, 0, turn2, getRadius2());
            checkUsingIntervals2(d1,
                                 0, 0.1, 0.1, 0.1);
        }
    }

    TEST (GDIP, LpR) {
        State p1 = State(Point(0, 0), 0);
        for (
                int i = 0;
                i < COUNT;
                ++i) {
            p1.random(100);

            const myFloat TOL_ANG = 0.05;
            myFloat turn1 = M_PI * (1 + TOL_ANG) + myRandom() * M_PI * (1 - 2 * TOL_ANG);
            myFloat turn2 = -myRandom() * M_PI * (1 - TOL_ANG);

            Dubins d1(p1, false, turn1, 0, turn2, getRadius2());
            checkUsingIntervals2(d1,
                                 0.1, 0.1, 0.1, 0);
        }
    }

    TEST (GDIP, RpL) {
        State p1 = State(Point(0, 0), 0);
        for (
                int i = 0;
                i < COUNT;
                ++i) {
            p1.random(100);

            const myFloat TOL_ANG = 0.05;
            myFloat turn1 = -M_PI * (1 + TOL_ANG) - myRandom() * M_PI * (1 - 2 * TOL_ANG);
            myFloat turn2 = myRandom() * M_PI * (1 - TOL_ANG);

            Dubins d1(p1, false, turn1, 0, turn2, getRadius2());
            checkUsingIntervals2(d1,
                                 0.1, 0.1, 0, 0.1);
        }
    }

// TODO - change test to be useful
    TEST (GDIP, RpLp) {
        State p1 = State(Point(0, 0), 0);
        for (
                int i = 0;
                i < COUNT;
                ++i) {
            p1.random(100);
            myFloat turn = M_PI + myRandom() * M_PI;
            Dubins d1(p1, false, -turn, 0, turn, getRadius2());
            checkUsingIntervals2(d1,
                                 0.1, 0.1, 0.1, 0.1);
        }
    }

// TODO - change test to be useful
    TEST (GDIP, LpRp) {
        State p1 = State(Point(0, 0), 0);
        for (
                int i = 0;
                i < COUNT;
                ++i) {
            p1.random(100);
            myFloat turn = M_PI + myRandom() * M_PI;
            Dubins d1(p1, false, turn, 0, -turn, getRadius2());
            myFloat intervalSize = 3;
            checkUsingIntervals2(d1,
                                 0.1, 0.1, 0.1, 0.1);
        }
    }

    TEST (GDIP, Small) {
        State p1 = State(Point(0, 0), 0);
        State p2 = State(Point(0, 0), 0);
        for (
                int i = 0;
                i < COUNT;
                ++i) {
            p1.random(5);
            p2.random(5);
            Dubins d1(p1, p2, getRadius2());
            checkUsingIntervals2(d1,
                                 0.1, 0.1, 0.1, 0.1);
        }
    }

    TEST (GDIP, Big) {
        State p1 = State(Point(0, 0), 0);
        State p2 = State(Point(0, 0), 0);
        for (
                int i = 0;
                i < COUNT;
                ++i) {
            p1.random(5);
            p2.random(5);
            Dubins d1(p1, p2, getRadius2());
            checkUsingIntervals2(d1,
                                 1, 1, 1, 1);
        }
    }

    TEST (GDIP, Random) {
        State p1 = State(Point(0, 0), 0);
        for (
                int i = 0;
                i < COUNT;
                ++i) {
            p1.random(5);
            Dubins d1;

            myFloat radius = getRadius2();

            myFloat turn1 = 0;
            myFloat turn2 = 0;

            if (

                    myRandom()

                    < 0.5) {
                myFloat center = myRandom() * radius;
                d1 = Dubins(p1, false, turn1, center, turn2, radius);
            } else {
                myFloat centerTurn = (1 + myRandom()) * M_PI;
                d1 = Dubins(p1, true, turn1, centerTurn, turn2, radius);
            }
            checkUsingIntervals2(d1,
                                 0.1, 0.1, 0.1, 0.1);
        }
    }

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
// NEW TESTS SPECIALLY FOR GDIP /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


    Dubins checkUsingIntervals_GDIP(Dubins &d1, myFloat a1, myFloat b1, myFloat a2, myFloat b2) {
        myFloat diff1 = 10 * myRandom();
        myFloat diff2 = 10 * myRandom();

        auto dir1 = Vector(myRandom() * 2 * M_PI) * diff1;
        auto dir2 = Vector(myRandom() * 2 * M_PI) * diff2;

        myFloat a = myRandom() * a1;
        myFloat b = myRandom() * b1;

        AngleInterval interval1 = AngleInterval(d1.start.point + dir1, d1.start.getAngle() - a, b + a);

        a = myRandom() * a2;
        b = myRandom() * b2;

        AngleInterval interval2 = AngleInterval(d1.end.point + dir2, d1.end.getAngle() - a, b + a);

        Dubins d2(interval1, interval2, d1.radius, diff1, diff2);
        check2(interval1, interval2, d1, d2);

        return d2;
    }

    TEST (GDIP, S_GDIP) {
        State p1 = State(Point(0, 0), 0);
        for (
                int i = 0;
                i < COUNT;
                ++i) {
            p1.random(100);
            Dubins d1(p1, false, 0, myRandom() * 10, 0, getRadius2());
            Dubins d2 = checkUsingIntervals_GDIP(d1, 1, 1, 1, 1);
        }
    }

/*TEST (GDIP, R_GDIP) { // RS and R
	Position p1 = Position(Point(0, 0), 0);
	for (int i = 0; i < COUNT; ++i) {
		p1.random(100);
		Dubins d1 (p1, false, myRandom()*10, 0, 0, getRadius2());
		Dubins d2 = checkUsingIntervals_GDIP(d1, 1, 1, 1, 1);
	}
}*/

/*TEST (GDIP, RS_GDIP) { // RS and R
	Position p1 = Position(Point(0, 0), 0);
	for (int i = 0; i < COUNT; ++i) {
		p1.random(100);
		Dubins d1 (p1, false, myRandom()*10, myRandom()*10, 0, getRadius2());
		Dubins d2 = checkUsingIntervals_GDIP(d1, 1, 1, 1, 1);
	}
}*/

/*TEST (GDIP, ZeroInterval_GDIP) {
	Position p1 = Position(Point(0, 0), 0);
	Position p2 = Position(Point(0, 0), 0);

	myFloat diff1 = 0.1;
	myFloat diff2 = 0.2;

	for (int i = 0; i < COUNT; ++i) {
		p1.random(100);
		p2.random(100);
		Dubins d1(p1, p2, getRadius2());

		auto dir1 = Vector(myRandom()*2*M_PI) * diff1;
		auto dir2 = Vector(myRandom()*2*M_PI) * diff2;

		AngleInterval interval1 = AngleInterval(p1.point + dir1, p1.ang , 0);
		AngleInterval interval2 = AngleInterval(p2.point + dir2, p2.ang , 0);
        Dubins d2(interval1, interval2, d1.radius, diff1, diff2);

		check2(interval1, interval2, d1, d2);
	}
}*/

}
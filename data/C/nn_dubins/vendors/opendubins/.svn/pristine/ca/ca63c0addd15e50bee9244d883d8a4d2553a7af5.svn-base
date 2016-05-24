/*
 * dubins3pointtest.cpp
 *
 *  Created on: Feb 18, 2016
 *      Author: Petr Vana
 */

#include "gtest/gtest.h"
#include "opendubins/touring/dubins3point.h"

using namespace std;
using namespace opendubins;

namespace dub3_test {

    int COUNT = 100;

    myFloat getRadius() {
        return 0.1 + 3 * myRandom();
    }

    TEST (Dub3Test, Random) {
        State p1 = State(Point(0, 0), 0);
        State p2 = State(Point(0, 0), 0);

        State target = State(Point(0, 0), 0);

        for (int i = 0; i < COUNT; ++i) {
            p1.random(1);
            p2.random(1);
            target.random(1);
            auto &tp = target.point;

            auto radius = getRadius();

            Dubins3Point d3p(p1, tp, p2, radius, 1000000);

            auto shortest = numeric_limits<myFloat>::max();
            for (myFloat h = 0; h < 2 * M_PI; h += 0.001) {
                Dubins d1(p1, State(tp, h), radius);
                Dubins d2(State(tp, h), p2, radius);

                shortest = min(shortest, d1.length + d2.length);
            }

            EXPECT_LE(fabs(shortest / d3p.lowerBoundPathLen() - 1), 100 * TOLERANCE) << "lower bound out of tolerance";
            EXPECT_LE(fabs(shortest / d3p.feasibleSolutionLen() - 1), 100 * TOLERANCE)
                                << "feasible solution out of tolerance";
            //cout << shortest << " = " << d3p.lowerBoundPathLen() << endl;
        }
    }

    TEST (Dub3Test, Random2) {
        State p1 = State(Point(0, 0), 0);
        State p2 = State(Point(0, 0), 0);

        State target = State(Point(0, 0), 0);

        for (int i = 0; i < COUNT; ++i) {
            p1.random(1);
            p2.random(1);
            target.random(1);
            auto &tp = target.point;

            auto radius = getRadius();

            Dubins3Point d3p(p1, tp, p2, radius, 10);
            d3p.split(200000);

            auto shortest = numeric_limits<myFloat>::max();
            for (myFloat h = 0; h < 2 * M_PI; h += 0.001) {
                Dubins d1(p1, State(tp, h), radius);
                Dubins d2(State(tp, h), p2, radius);

                shortest = min(shortest, d1.length + d2.length);
            }

            EXPECT_LE(fabs(shortest / d3p.lowerBoundPathLen() - 1), 10*TOLERANCE) << "lower bound out of tolerance";
            EXPECT_LE(fabs(shortest / d3p.feasibleSolutionLen() - 1), 10*TOLERANCE)
                                << "feasible solution out of tolerance";
            //cout << shortest << " = " << d3p.lowerBoundPathLen() << endl;
        }
    }

}

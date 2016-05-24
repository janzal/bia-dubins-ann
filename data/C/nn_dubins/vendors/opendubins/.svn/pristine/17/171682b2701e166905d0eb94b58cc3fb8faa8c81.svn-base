/*
 * dubinstest.cpp - Basic test of the Dubins maneuver
 *
 *  Created on: Dec 7, 2015
 *      Author: Petr Vana
 */

#include "gtest/gtest.h"
#include "opendubins/dubins.h"

using namespace opendubins;

namespace dubinstest {

    const int COUNT = 10000;
    const int B_COUNT = 1;

    TEST (DubinsTest, CorrectPosition) {
        State p1 = State(0, 0, 0);
        State p2 = State(0, 0, 0);

        Dubins d(p1, p2, 1);

        for (int i = 0; i < COUNT; ++i) {
            p1.random(10);
            p2.random(10);
            for (int j = 0; j < B_COUNT; ++j) {
                d = Dubins(p1, p2, 1);
            }

            EXPECT_TRUE(d.check());
        }
    }

    TEST (DubinsTest, ShortestCSC) {
        State p1 = State(0, 0, 0);
        State p2 = State(0, 0, 0);
        Dubins d1(p1, p2, 100);
        Dubins d2(p1, p2, 100);

        for (int i = 0; i < COUNT; ++i) {
            p1.random(100);
            d1 = Dubins(p1, false, myRandom() * 20 - 10, myRandom() * 10, myRandom() * 20 - 10, 1.0);
            for (int j = 0; j < B_COUNT; ++j) {
                d2 = Dubins(p1, d1.end, d1.radius);
            }

            EXPECT_TRUE(d1.check());
            EXPECT_TRUE(d2.check());
            EXPECT_GE(d1.length + 10 * TOLERANCE, d2.length);
        }
    }

// TODO - add test for CCC maneuver

}
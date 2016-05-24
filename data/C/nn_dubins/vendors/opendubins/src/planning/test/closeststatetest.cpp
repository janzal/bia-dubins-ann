/*
 * ClosestTest.cpp
 *
 *  Created on: Feb 18, 2016
 *      Author: Petr Vana
 */

#include "gtest/gtest.h"
#include "opendubins/dubins.h"

using namespace std;
using namespace opendubins;

namespace closest_test {

    int COUNT = 100;

    myFloat getRadius() {
        return 0.1 + 3 * myRandom();
    }

    TEST (ClosestTest, Line) {
        State p1 = State(Point(0, 0), 0);
        State p2 = State(Point(0, 0), 0);

        State target = State(Point(0, 0), 0);

        for (int i = 0; i < COUNT; ++i) {
            p1.random(1);
            p2.random(1);
            target.random(1);
            auto &tp = target.point;

            Line line(p1.point, p2.point);

            auto closest = line.getClosestState(tp);

            myFloat minLen = numeric_limits<myFloat>().max();

            const auto lineLen = line.getLength();
            for (myFloat i = 0; i < lineLen; i += lineLen / 10000.0) {
                auto actPos = line.getState(i);
                auto dist = actPos.point.distance(tp);
                minLen = min(minLen, dist);
                EXPECT_GE(dist, closest.point.distance(tp));
            }

            EXPECT_GE(closest.point.distance(tp), minLen - 0.01);

            //cout << minLen << " > " << (closest.point.distance(tp)) << endl;
        }
    }

    TEST (ClosestTest, ArcLeft) {
        State p1 = State(Point(0, 0), 0);

        State target = State(Point(0, 0), 0);

        for (int i = 0; i < COUNT; ++i) {
            p1.random(3);
            target.random(3);
            auto &tp = target.point;

            Arc arc(p1, 2 * M_PI * myRandom(), getRadius());

            auto closest = arc.getClosestState(tp);

            myFloat minLen = numeric_limits<myFloat>().max();

            const auto lineLen = arc.getLength();
            for (myFloat i = 0; i < lineLen; i += lineLen / 10000.0) {
                auto actPos = arc.getState(i);
                auto dist = actPos.point.distance(tp);
                minLen = min(minLen, dist);
                EXPECT_GE(dist + TOLERANCE, closest.point.distance(tp));
            }

            EXPECT_GE(closest.point.distance(tp), minLen - 0.1);

            //cout << minLen << " > " << (closest.point.distance(tp)) << endl;
        }
    }

    TEST (ClosestTest, ArcRight) {
        State p1 = State(Point(0, 0), 0);

        State target = State(Point(0, 0), 0);

        for (int i = 0; i < COUNT; ++i) {
            p1.random(3);
            target.random(3);
            auto &tp = target.point;

            Arc arc(p1, -2 * M_PI * myRandom(), getRadius());

            auto closest = arc.getClosestState(tp);

            myFloat minLen = numeric_limits<myFloat>().max();

            const auto lineLen = arc.getLength();
            for (myFloat i = 0; i < lineLen; i += lineLen / 10000.0) {
                auto actPos = arc.getState(i);
                auto dist = actPos.point.distance(tp);
                minLen = min(minLen, dist);
                EXPECT_GE(dist + TOLERANCE, closest.point.distance(tp));
            }

            EXPECT_GE(closest.point.distance(tp), minLen - 0.1);

            //cout << minLen << " > " << (closest.point.distance(tp)) << endl;
        }
    }

    TEST (ClosestTest, Basic) {
        State p1 = State(Point(0, 0), 0);
        State p2 = State(Point(0, 0), 0);

        State target = State(Point(0, 0), 0);

        for (int i = 0; i < COUNT; ++i) {
            p1.random(100);
            p2.random(100);
            target.random(100);
            auto &tp = target.point;
            Dubins d1(p1, p2, getRadius());

            auto closest = d1.getClosestState(tp);

            myFloat minLen = numeric_limits<myFloat>().max();

            auto len1 = d1.getFirstArc().getLength();
            auto len2 = (d1.getIsCCC() ? d1.getCenterArc().getLength() : d1.getCenter().getLength());
            auto len3 = d1.getSecondArc().getLength();

            {
                auto arc1 = d1.getFirstArc();
                auto closestArc1 = arc1.getClosestState(tp);
                const auto arc1Len = arc1.getLength();
                for (myFloat i = 0; i < arc1Len; i += arc1Len / 1000.0) {
                    auto actPos = arc1.getState(i);
                    auto dist = actPos.point.distance(tp);
                    minLen = min(minLen, dist);
                    EXPECT_GE(dist + TOLERANCE, closestArc1.point.distance(tp)) << "Error in first arc";
                }

                auto arc2 = d1.getFirstArc();
                auto closestArc2 = arc2.getClosestState(tp);
                const auto arc2Len = arc2.getLength();
                for (myFloat i = 0; i < arc2Len; i += arc2Len / 1000.0) {
                    auto actPos = arc2.getState(i);
                    auto dist = actPos.point.distance(tp);
                    minLen = min(minLen, dist);
                    EXPECT_GE(dist + TOLERANCE, closestArc2.point.distance(tp)) << "Error in first arc";
                }

                EXPECT_GE(closestArc1.point.distance(tp), closest.point.distance(tp)) << "Bad min1";
                EXPECT_GE(closestArc2.point.distance(tp), closest.point.distance(tp)) << "Bad min2";
            }

            if (d1.getIsCCC() == false) {
                auto line = d1.getCenter();
                auto closestLine = line.getClosestState(tp);
                const auto lineLen = line.getLength();
                for (myFloat i = 0; i < lineLen; i += lineLen / 1000.0) {
                    auto actPos = line.getState(i);
                    auto dist = actPos.point.distance(tp);
                    minLen = min(minLen, dist);
                    EXPECT_GE(dist, closestLine.point.distance(tp)) << "Error in line";
                }
                EXPECT_GE(closestLine.point.distance(tp), closest.point.distance(tp)) << "Bad min line";
            }

            const auto dubLen = d1.getLength();
            for (myFloat i = 0; i < dubLen; i += dubLen / 10.0) {
                auto actPos = d1.getState(i);
                auto dist = actPos.point.distance(tp);
                minLen = min(minLen, dist);
                EXPECT_GE(dist + 10, closest.point.distance(tp));
                if (dist + 10 < closest.point.distance(tp)) {
                    //cout << i << " lenghts: " << len1 << "," << len2 << "," << len3 << "," << endl;
                }
            }

            //cout << minLen << " > " << (closest.point.distance(tp)) << endl;

        }
    }

    TEST (ClosestTest, Line_Intersection) {
        State p1 = State(Point(0, 0), 0);
        State p2 = State(Point(0, 0), 0);

        State target = State(Point(0, 0), 0);

        for (int i = 0; i < COUNT; ++i) {
            p1.random(1);
            p2.random(1);
            target.random(1);
            auto &tp = target.point;

            Line line(p1.point, p2.point);

            auto closest = line.getClosestIntersection(tp);

            myFloat minLen = numeric_limits<myFloat>().max();

            const auto lineLen = line.getLength();
            for (myFloat i = 0; i < lineLen; i += lineLen / 10000.0) {
                auto actPos = line.getState(i);
                auto dist = actPos.point.distance(tp);
                minLen = min(minLen, dist);
                EXPECT_GE(dist, closest.state.point.distance(tp));
            }

            EXPECT_GE(closest.state.point.distance(tp), minLen - 0.01);

            EXPECT_LE(line.getState(closest.distance).point.distance(closest.state.point), TOLERANCE);

            //cout << minLen << " > " << (closest.point.distance(tp)) << endl;
        }
    }

    TEST (ClosestTest, ArcLeft_Intersection) {
        State p1 = State(Point(0, 0), 0);

        State target = State(Point(0, 0), 0);

        for (int i = 0; i < COUNT; ++i) {
            p1.random(3);
            target.random(3);
            auto &tp = target.point;

            Arc arc(p1, 2 * M_PI * myRandom(), getRadius());

            auto closest = arc.getClosestIntersection(tp);

            myFloat minLen = numeric_limits<myFloat>().max();

            const auto lineLen = arc.getLength();
            for (myFloat i = 0; i < lineLen; i += lineLen / 10000.0) {
                auto actPos = arc.getState(i);
                auto dist = actPos.point.distance(tp);
                minLen = min(minLen, dist);
                EXPECT_GE(dist + TOLERANCE, closest.state.point.distance(tp));
            }

            EXPECT_GE(closest.state.point.distance(tp), minLen - 0.1);

            EXPECT_LE(arc.getState(closest.distance).point.distance(closest.state.point), TOLERANCE);

            //cout << minLen << " > " << (closest.point.distance(tp)) << endl;
        }
    }

    TEST (ClosestTest, ArcRight_Intersection) {
        State p1 = State(Point(0, 0), 0);

        State target = State(Point(0, 0), 0);

        for (int i = 0; i < COUNT; ++i) {
            p1.random(3);
            target.random(3);
            auto &tp = target.point;

            Arc arc(p1, -2 * M_PI * myRandom(), getRadius());

            auto closest = arc.getClosestIntersection(tp);

            myFloat minLen = numeric_limits<myFloat>().max();

            const auto lineLen = arc.getLength();
            for (myFloat i = 0; i < lineLen; i += lineLen / 10000.0) {
                auto actPos = arc.getState(i);
                auto dist = actPos.point.distance(tp);
                minLen = min(minLen, dist);
                EXPECT_GE(dist + TOLERANCE, closest.state.point.distance(tp));
            }

            EXPECT_GE(closest.state.point.distance(tp), minLen - 0.1);

            EXPECT_LE(arc.getState(closest.distance).point.distance(closest.state.point), TOLERANCE);

            //cout << minLen << " > " << (closest.point.distance(tp)) << endl;
        }
    }

    TEST (ClosestTest, Basic_Intersection) {
        State p1 = State(Point(0, 0), 0);
        State p2 = State(Point(0, 0), 0);

        State target = State(Point(0, 0), 0);

        for (int i = 0; i < COUNT; ++i) {
            p1.random(100);
            p2.random(100);
            target.random(100);
            auto &tp = target.point;
            Dubins d1(p1, p2, getRadius());

            auto closest = d1.getClosestIntersection(tp);

            myFloat minLen = numeric_limits<myFloat>().max();

            auto len1 = d1.getFirstArc().getLength();
            auto len2 = (d1.getIsCCC() ? d1.getCenterArc().getLength() : d1.getCenter().getLength());
            auto len3 = d1.getSecondArc().getLength();

            {
                auto arc1 = d1.getFirstArc();
                auto closestArc1 = arc1.getClosestIntersection(tp);
                const auto arc1Len = arc1.getLength();
                for (myFloat i = 0; i < arc1Len; i += arc1Len / 1000.0) {
                    auto actPos = arc1.getState(i);
                    auto dist = actPos.point.distance(tp);
                    minLen = min(minLen, dist);
                    EXPECT_GE(dist + TOLERANCE, closestArc1.state.point.distance(tp)) << "Error in first arc";
                }

                auto arc2 = d1.getFirstArc();
                auto closestArc2 = arc2.getClosestIntersection(tp);
                const auto arc2Len = arc2.getLength();
                for (myFloat i = 0; i < arc2Len; i += arc2Len / 1000.0) {
                    auto actPos = arc2.getState(i);
                    auto dist = actPos.point.distance(tp);
                    minLen = min(minLen, dist);
                    EXPECT_GE(dist + TOLERANCE, closestArc2.state.point.distance(tp)) << "Error in first arc";
                }

                EXPECT_GE(closestArc1.state.point.distance(tp), closest.state.point.distance(tp)) << "Bad min1";
                EXPECT_GE(closestArc2.state.point.distance(tp), closest.state.point.distance(tp)) << "Bad min2";
            }

            if (d1.getIsCCC() == false) {
                auto line = d1.getCenter();
                auto closestLine = line.getClosestIntersection(tp);
                const auto lineLen = line.getLength();
                for (myFloat i = 0; i < lineLen; i += lineLen / 1000.0) {
                    auto actPos = line.getState(i);
                    auto dist = actPos.point.distance(tp);
                    minLen = min(minLen, dist);
                    EXPECT_GE(dist, closestLine.state.point.distance(tp)) << "Error in line";
                }
                EXPECT_GE(closestLine.state.point.distance(tp), closest.state.point.distance(tp)) << "Bad min line";
            }

            const auto dubLen = d1.getLength();
            for (myFloat i = 0; i < dubLen; i += dubLen / 10.0) {
                auto actPos = d1.getState(i);
                auto dist = actPos.point.distance(tp);
                minLen = min(minLen, dist);
                EXPECT_GE(dist + 10, closest.state.point.distance(tp));
                if (dist + 10 < closest.state.point.distance(tp)) {
                    //cout << i << " lenghts: " << len1 << "," << len2 << "," << len3 << "," << endl;
                }
            }

            //cout << minLen << " > " << (closest.point.distance(tp)) << endl;

        }
    }


}

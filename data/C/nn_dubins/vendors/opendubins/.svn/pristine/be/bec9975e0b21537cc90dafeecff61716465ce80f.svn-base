/*
 * Dubins3Point.cpp
 *
 *  Created on: Feb 18, 2016
 *      Author: Petr Vana
 */

#include "opendubins/touring/dubins3point.h"

using namespace std;

namespace opendubins {

    Dubins3Point::Dubins3Point(State &start, Point &thru, State &end, myFloat radius, int resolution) :
            start(start), thru(thru), end(end), radius(radius), lowerSolution(0), lowerBound(0.0),
            resolution(resolution) {

        init();
        split(resolution);
    }

    Dubins3Point::~Dubins3Point() { }

    bool Dubins3Point::split(myFloat resolution) {
        bool ret = false;

        bool working = true;
        while (working) {
            working = false;
            auto &actInt = intervals[lowerSolution];
            if (actInt.resolution < resolution) {
                intervals.push_back(actInt.splitInterval());
                ret = true;
                working = true;
            }

            updateDistances();
            findLowerBound();
        }

        return ret;
    }

    void Dubins3Point::init() {
        intervals.clear();

        auto inter = AngleInterval(thru);
        intervals.push_back(inter);
        updateDistancesIdx(0);

        findLowerBound();
    }

    void Dubins3Point::findLowerBound() {
        const int SIZE = intervals.size();

        lowerBound = numeric_limits<myFloat>::max();
        lowerSolution = 0;

        for (int i = 0; i < SIZE; ++i) {
            auto nLen = dip1s[i].length + dip2s[i].length;
            if (nLen < lowerBound) {
                lowerBound = nLen;
                lowerSolution = i;
            }
        }
    }

    int Dubins3Point::findShortestFeasible() {
        const int SIZE = intervals.size();

        auto shortestLen = numeric_limits<myFloat>::max();
        int shortestIdx = 0;

        for (int i = 0; i < SIZE; ++i) {
            auto nLen = dub1s[i].length + dub2s[i].length;
            if (nLen < shortestLen) {
                shortestLen = nLen;
                shortestIdx = i;
            }
        }

        return shortestIdx;
    }

    void Dubins3Point::updateDistances() {
        const int SIZE = intervals.size();

        updateDistancesIdx(lowerSolution);
        updateDistancesIdx(SIZE - 1);
    }

    void Dubins3Point::updateDistancesIdx(int idx) {
        const int S = intervals.size();

        auto inter = intervals[idx];

        dip1s.resize(S);
        dip2s.resize(S);

        dip1s[idx] = Dubins(AngleInterval(start.point, start.ang, 0), inter, radius);
        dip2s[idx] = Dubins(inter, AngleInterval(end.point, end.ang, 0), radius);

        dub1s.resize(S);
        dub2s.resize(S);

        dub1s[idx] = Dubins(start, inter.getLeftState(), radius);
        dub2s[idx] = Dubins(inter.getLeftState(), end, radius);
    }

    std::vector<Dubins> Dubins3Point::lowerBoundPath() {
        vector<opendubins::Dubins> ret;

        const int SIZE = intervals.size();

        ret.push_back(dip1s[lowerSolution]);
        ret.push_back(dip2s[lowerSolution]);

        return ret;
    }

    opendubins::myFloat Dubins3Point::lowerBoundPathLen() {
        opendubins::myFloat ret = 0;
        for (auto m : lowerBoundPath()) {
            ret += m.length;
        }
        return ret;
    }

    opendubins::myFloat Dubins3Point::feasibleSolutionLen() {
        opendubins::myFloat ret = 0;
        for (auto m : feasibleSolution()) {
            ret += m.length;
        }
        return ret;
    }

    std::vector<Dubins> Dubins3Point::feasibleSolution() {
        const int SIZE = intervals.size();
        vector<opendubins::Dubins> ret;

        int idx = findShortestFeasible();

        ret.push_back(dub1s[idx]);
        ret.push_back(dub2s[idx]);

        return ret;
    }

    myFloat Dubins3Point::centerHeading() {
        auto solution = feasibleSolution();
        return solution[1].start.ang;
    }

    int Dubins3Point::size() {
        return intervals.size();
    }

    opendubins::Dubins Dubins3Point::shortestPath(opendubins::AngleInterval &from, opendubins::AngleInterval &to,
                                                  opendubins::myFloat radius) {
        opendubins::Dubins ret = opendubins::Dubins();
        ret.length = numeric_limits<double>::max();
        opendubins::Dubins n = opendubins::Dubins(from, to, radius);
        if (n.length < ret.length) {
            ret = n;
        }
        return ret;
    }

}

/*
 * dubins3point.h
 *
 *  Created on: Feb 19, 2016
 *      Author: Petr Vana
 */

#pragma once

#include "dtp.h"

namespace opendubins {

    class Dubins3Point {

    public:

        Dubins3Point(State &start, Point &thru, State &end, myFloat radius, int resolution);

        virtual ~Dubins3Point();

        State start;
        Point thru;
        State end;

        opendubins::myFloat radius;

        int resolution;

        bool split(opendubins::myFloat minInterval);

        std::vector<opendubins::Dubins> lowerBoundPath();
        opendubins::myFloat lowerBoundPathLen();

        std::vector<opendubins::Dubins> feasibleSolution();
        opendubins::myFloat feasibleSolutionLen();

        myFloat centerHeading();

        int size();

    protected:

        std::vector<opendubins::AngleInterval> intervals;

        std::vector<opendubins::Dubins> dub1s;
        std::vector<opendubins::Dubins> dub2s;

        std::vector<opendubins::Dubins> dip1s;
        std::vector<opendubins::Dubins> dip2s;

        int lowerSolution;
        myFloat lowerBound;

        Dubins shortestPath(opendubins::AngleInterval &from, opendubins::AngleInterval &to,
                            opendubins::myFloat radius);

        void init();

        void findLowerBound();

        int findShortestFeasible();

        void updateDistances();

        void updateDistancesIdx(int idx);
    };
}

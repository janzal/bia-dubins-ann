/*
 * dtp.h
 *
 *  Created on: Feb 18, 2016
 *      Author: Petr Vana
 */

#pragma once

#include "opendubins/dubins.h"

namespace opendubins {

    typedef std::vector<std::vector<std::vector<opendubins::myFloat>>> dst_type;
    typedef std::pair<int, opendubins::myFloat> dst_pair;
    typedef std::vector<std::vector<std::vector<dst_pair>>> matrix_pair;

    class DTP {
    public:
        DTP() { }

        DTP(std::vector<Point> points, myFloat radius);

        virtual ~DTP();

        opendubins::myFloat radius;
        int resolution;
        std::vector<std::vector<opendubins::AngleInterval> > intervals;
        std::vector<int> usedIntervals;

        bool first;

        void init();

        void findShortest();

        void updateDistances();

        void solve();

        bool split(int minInterval);

        std::vector<opendubins::Dubins> lowerBoundPath();

        opendubins::myFloat lowerBoundPathLen();

        std::vector<opendubins::Dubins> feasibleSolution();

        opendubins::myFloat feasibleSolutionLen();

        int size();

        Dubins shortestPath(opendubins::AngleInterval &from, opendubins::AngleInterval &to, opendubins::myFloat radius);

    protected:

        // matrix 1) from city 2) from sample 3) to sample (to city is known)
        dst_type distances;

        // find all shortest paths
        // matrix: 1) to City 2) to idx 3) from start idx
        matrix_pair shortest;

        inline std::vector<opendubins::AngleInterval> &getInt(int idx) {
            idx += intervals.size();
            idx %= intervals.size();

            return intervals[idx];
        }
    };

}

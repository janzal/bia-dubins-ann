/*
 * DTP.cpp
 *
 *  Created on: Feb 18, 2016
 *      Author: Petr Vana
 */

#include "opendubins/touring/dtp.h"

using namespace std;

namespace opendubins {

    DTP::DTP(std::vector<Point> points, myFloat radius) :
            radius(radius), first(true), resolution(1) {
        const int SIZE = points.size();

        intervals.resize(SIZE);
        usedIntervals.assign(SIZE, 0);

        for (int i = 0; i < SIZE; ++i) {
            intervals[i].push_back(AngleInterval(points[i]));
        }

        init();
    }

    DTP::~DTP() {
    }

    bool DTP::split(int resol) {
        bool ret = false;

        while (resol > resolution) {

            if (resolution * 2 > resolution) {
                resolution *= 2;
                //cout << "resolution " << resolution << endl;
            } else {
                break;
            }

            bool improving = true;
            while (improving) {
                improving = false;

                const int SIZE = intervals.size();

                // split used intervals in half
                for (int i = 0; i < SIZE; i++) {
                    auto &inters = intervals[i];
                    int idx = usedIntervals[i];

                    auto &actInt = inters[idx];
                    if (actInt.resolution < resolution) {
                        inters.push_back(actInt.splitInterval());
                        ret = true;
                        improving = true;
                    }
                }

                solve();
            }
        }

        return ret;
    }

    void DTP::init() {
        const int SIZE = intervals.size();

        distances.resize(SIZE);

        // fill distance matrix
        for (int i = 0; i < SIZE; i++) {
            const int S2 = getInt(i).size();
            const int S3 = getInt(i + 1).size();
            distances[i].resize(S2);

            for (int j = 0; j < S2; ++j) {
                distances[i][j].resize(S3);

                for (int k = 0; k < S3; ++k) {
                    auto &actInt = getInt(i)[j];
                    auto &nextInt = getInt(i + 1)[k];
                    distances[i][j][k] = shortestPath(actInt, nextInt, radius).length;
                }
            }
        }

        findShortest();
    }

    void DTP::findShortest() {
        const int SIZE = intervals.size();
        const auto BIG = numeric_limits<myFloat>::max();

        //log->info("init shortest");

        // clean matrix
        shortest.clear();
        shortest.resize(SIZE + 1);

        const int SIZE_FROM = getInt(0).size();

        // fill start in shortest matrix by diagonal matrix with zero and inf value
        shortest[0].resize(SIZE_FROM);
        for (int i = 0; i < SIZE_FROM; i++) {
            shortest[0][i].resize(SIZE_FROM);
            for (int j = 0; j < SIZE_FROM; j++) {
                if (i == j) {
                    shortest[0][i][j] = dst_pair(-1, 0);
                } else {
                    shortest[0][i][j] = dst_pair(-1, BIG);
                }
            }
        }

        //log->info("find");

        // find all shortest paths
        for (int act = 1; act <= SIZE; act++) {
            const int actS = getInt(act).size();
            const int prevS = getInt(act - 1).size();
            shortest[act].resize(actS);

            //log->info("stepf ") << act << "," << prevS << "," << actS;

            for (int actIdx = 0; actIdx < actS; ++actIdx) {
                shortest[act][actIdx].assign(SIZE_FROM, dst_pair(-1, BIG));
                for (int prevIdx = 0; prevIdx < prevS; ++prevIdx) {

                    //log->info("step1 ") << i << "," << j << "," << actIdx;

                    //log->info("step2 ") << i << "," << j << "," << actIdx;

                    auto dst2 = distances[act - 1][prevIdx][actIdx];
                    //log->info("dst2 ") << dst2;

                    for (int start = 0; start < SIZE_FROM; ++start) {
                        auto &fromPair = shortest[act - 1][prevIdx][start];
                        auto &toPair = shortest[act][actIdx][start];

                        auto dst = fromPair.second + dst2;

                        //log->info("shorter1 ") << dst;
                        if (toPair.second > dst) {
                            //log->info("shorter ") << dst << " << " << prevIdx;
                            toPair.first = prevIdx;
                            toPair.second = dst;
                        }
                    }
                }
            }

        }

        //log->info("found");
    }

    void DTP::updateDistances() {
        const int SIZE = intervals.size();

        distances.resize(SIZE);

        // fill distance matrix
        for (int i = 0; i < SIZE; i++) {
            const int S2 = getInt(i).size();
            const int S3 = getInt(i + 1).size();
            distances[i].resize(S2);

            for (int j = 0; j < S2; ++j) {
                distances[i][j].resize(S3);
            }
        }

        // update outgoing edges
        for (int i = 0; i < SIZE; i++) {
            const int S2 = getInt(i).size();
            const int S3 = getInt(i + 1).size();

            // the last (newly generated) interval
            int j = S2 - 1;

            for (int k = 0; k < S3; ++k) {
                auto &actInt = getInt(i)[j];
                auto &nextInt = getInt(i + 1)[k];
                distances[i][j][k] = shortestPath(actInt, nextInt, radius).length;
            }

            // currently used (splited) interval
            j = usedIntervals[i];

            for (int k = 0; k < S3; ++k) {
                auto &actInt = getInt(i)[j];
                auto &nextInt = getInt(i + 1)[k];
                distances[i][j][k] = shortestPath(actInt, nextInt, radius).length;
            }
        }

        // update incoming edges
        for (int i = 0; i < SIZE; i++) {
            const int S2 = getInt(i).size();
            const int S3 = getInt(i - 1).size();

            // the last (newly generated) interval
            int j = S2 - 1;

            for (int k = 0; k < S3; ++k) {
                auto &actInt = getInt(i)[j];
                auto &prevInt = getInt(i - 1)[k];
                distances[(i - 1 + SIZE) % SIZE][k][j] = shortestPath(prevInt, actInt, radius).length;
            }

            // currently used (splited) interval
            j = usedIntervals[i];

            for (int k = 0; k < S3; ++k) {
                auto &actInt = getInt(i)[j];
                auto &prevInt = getInt(i - 1)[k];
                distances[(i - 1 + SIZE) % SIZE][k][j] = shortestPath(prevInt, actInt, radius).length;
            }

        }
    }

    void DTP::solve() {
        const int SIZE = intervals.size();
        const auto BIG = numeric_limits<myFloat>::max();

        // init distance matrix and shortest paths
        if (first) {
            init();
            first = false;
        } else {
            updateDistances();
            findShortest();
        }

        // find the shortest circuit
        auto minDst = numeric_limits<myFloat>::max();
        auto fromIdx = -1;

        for (int i = 0; i < shortest[SIZE].size(); i++) {
            //log->info("step3 ") << i << "," << shortest[SIZE][i].size();
            auto &actPair = shortest[SIZE][i][i];
            if (actPair.second < minDst) {
                minDst = actPair.second;
                fromIdx = i;
                //log->info("previous ") << i << " prev " << actPair.first;
            }
        }

        myFloat length = 0;

        vector<int>
                used;

        int actIdx = fromIdx;
        for (int i = SIZE; i > 1; i--) {
            //log->info("prev1 ") << actIdx << " from " << fromIdx;
            auto &actInt = shortest[i][actIdx][fromIdx];
            auto &prevInt = shortest[i - 1][actInt.first][fromIdx];
            auto dubLen = shortestPath(getInt(i - 1)[actInt.first], getInt(i)[actIdx], radius).length;
            length += dubLen;
            //log->info("prev2 ") << (actInt.second - prevInt.second) << " = " << dubLen;
            actIdx = actInt.first;
            used.push_back(actIdx);
        }
        used.push_back(fromIdx);
        reverse(used.begin(), used.end());

        for (int i = 0; i < used.size(); i++) {
            usedIntervals[i] = used[i];
        }

    }

    std::vector<Dubins> DTP::lowerBoundPath() {
        vector<opendubins::Dubins> ret;

        const int SIZE = intervals.size();

        myFloat total = 0;

        // split used intervals in half
        for (int i = 0; i < SIZE; i++) {
            // actual
            int idCity1 = i;
            int idx1 = usedIntervals[idCity1];
            auto &actInt = intervals[idCity1][idx1];

            int idCity2 = (i + 1) % SIZE;
            int idx2 = usedIntervals[idCity2];
            auto &nextInt = intervals[idCity2][idx2];

            auto shortest = shortestPath(actInt, nextInt, radius);
            total += shortest.length;
            ret.push_back(shortest);
        }

        return ret;
    }

    opendubins::myFloat DTP::lowerBoundPathLen() {
        opendubins::myFloat ret = 0;
        for (auto m : lowerBoundPath()) {
            ret += m.length;
        }
        return ret;
    }

    opendubins::myFloat DTP::feasibleSolutionLen() {
        opendubins::myFloat ret = 0;
        for (auto m : feasibleSolution()) {
            ret += m.length;
        }
        return ret;
    }

    std::vector<Dubins> DTP::feasibleSolution() {
        const int SIZE = intervals.size();
        vector<opendubins::Dubins> ret;

        myFloat total = 0;

        dst_type distances;
        distances.resize(SIZE);

        // fill distance matrix
        for (int i = 0; i < SIZE; i++) {
            const int S2 = getInt(i).size();
            const int S3 = getInt(i + 1).size();
            distances[i].resize(S2);

            for (int j = 0; j < S2; ++j) {
                distances[i][j].resize(S3);

                for (int k = 0; k < S3; ++k) {
                    auto &actInt = getInt(i)[j];
                    auto &nextInt = getInt(i + 1)[k];
                    auto d = Dubins(
                            actInt.getLeftState(),
                            nextInt.getLeftState(),
                            radius);
                    distances[i][j][k] = d.length;
                }
            }
        }

        const auto BIG = numeric_limits<myFloat>::max();

        matrix_pair shortest;

        // clean matrix
        shortest.clear();
        shortest.resize(SIZE + 1);

        const int SIZE_FROM = getInt(0).size();

        // fill start in shortest matrix by diagonal matrix with zero and inf value
        shortest[0].resize(SIZE_FROM);
        for (int i = 0; i < SIZE_FROM; i++) {
            shortest[0][i].resize(SIZE_FROM);
            for (int j = 0; j < SIZE_FROM; j++) {
                if (i == j) {
                    shortest[0][i][j] = dst_pair(-1, 0);
                } else {
                    shortest[0][i][j] = dst_pair(-1, BIG);
                }
            }
        }

        // find all shortest paths
        for (int act = 1; act <= SIZE; act++) {
            const int actS = getInt(act).size();
            const int prevS = getInt(act - 1).size();
            shortest[act].resize(actS);

            for (int actIdx = 0; actIdx < actS; ++actIdx) {
                shortest[act][actIdx].assign(SIZE_FROM, dst_pair(-1, BIG));
                for (int prevIdx = 0; prevIdx < prevS; ++prevIdx) {

                    auto dst2 = distances[act - 1][prevIdx][actIdx];

                    for (int start = 0; start < SIZE_FROM; ++start) {
                        auto &fromPair = shortest[act - 1][prevIdx][start];
                        auto &toPair = shortest[act][actIdx][start];

                        auto dst = fromPair.second + dst2;

                        //log->info("shorter1 ") << dst;
                        if (toPair.second > dst) {
                            //log->info("shorter ") << dst << " << " << prevIdx;
                            toPair.first = prevIdx;
                            toPair.second = dst;
                        }
                    }
                }
            }

        }

        auto minDst = numeric_limits<myFloat>::max();
        auto fromIdx = -1;

        for (int i = 0; i < shortest[SIZE].size(); i++) {
            //log->info("step3 ") << i << "," << shortest[SIZE][i].size();
            auto &actPair = shortest[SIZE][i][i];
            if (actPair.second < minDst) {
                minDst = actPair.second;
                fromIdx = i;
                //log->info("previous ") << i << " prev " << actPair.first;
            }
        }

        myFloat sum = 0;
        myFloat sum3 = 0;

        vector<int> used;

        auto usedIntervals = this->usedIntervals;

        int actIdx = fromIdx;
        for (int i = SIZE; i > 1; i--) {
            auto &actInt = shortest[i][actIdx][fromIdx];
            actIdx = actInt.first;
            used.push_back(actIdx);
        }
        used.push_back(fromIdx);
        reverse(used.begin(), used.end());

        for (int i = 0; i < used.size(); i++) {
            usedIntervals[i] = used[i];
        }

        // split used intervals in half
        for (int i = 0; i < SIZE; i++) {
            // actual
            int idCity1 = i;
            int idx1 = usedIntervals[idCity1];
            auto &actInt = intervals[idCity1][idx1];

            int idCity2 = (i + 1) % SIZE;
            int idx2 = usedIntervals[idCity2];
            auto &nextInt = intervals[idCity2][idx2];

            auto shortest = Dubins(
                    actInt.getLeftState(),
                    nextInt.getLeftState(),
                    radius);
            //auto shortest = shortestPath(actInt, nextInt, radius);
            total += shortest.length;
            ret.push_back(shortest);
        }

        return ret;
    }

    int DTP::size() {
        int sum = 0;
        for (auto &a : intervals) {
            sum += a.size();
        }
        return sum;
    }

    opendubins::Dubins DTP::shortestPath(opendubins::AngleInterval &from, opendubins::AngleInterval &to,
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

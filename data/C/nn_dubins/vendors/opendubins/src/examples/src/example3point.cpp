//
// Created by petr on 3/8/16.
//

#include <iostream>

#include "opendubins/dubins.h"
#include "opendubins/touring/dubins3point.h"

using namespace std;
using namespace opendubins;

int main() {
    auto point1 = State(0, 0, 0);
    auto point2 = Point(1, 1);
    auto point3 = State(2, 2, 2);

    double radius = 1.0;
    // resolution - angular_resolution = 2*pi / resolution
    int initialResolution = 8;

    Dubins3Point d3p = Dubins3Point(point1, point2, point3, radius, initialResolution);

    // it is possible to increase resolution in any time
    d3p.split(initialResolution * 8);

    cout << "Actual solution (lower bound = " << d3p.lowerBoundPathLen() << "), (upper bound = "
    << d3p.feasibleSolutionLen() << ")" << endl;

    cout << endl << "Found feasible solution : " << endl;
    for(auto &d : d3p.feasibleSolution()){
        cout << d << endl;
    }
    cout << ">>> Center heading is " << d3p.centerHeading() << endl;

    cout << endl << "Found lower bound (unfeasible) solution : " << endl;
    for(auto &d : d3p.lowerBoundPath()){
        cout << d << endl;
    }

    return 0;
}
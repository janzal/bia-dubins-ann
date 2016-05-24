/*
 * File name: dubins_types.h
 * Date:      2016/02/05 12:11
 * Author:    Jan Faigl
 */

#ifndef __DUBINS_TYPES_H__
#define __DUBINS_TYPES_H__

#include <vector>

#include <opendubins/dubins.h>
#include <opendubins/touring/dubins3point.h>

#define DUBINS_ANGLE_TOLERANCE 1e-5

typedef opendubins::Dubins DubinsManeuver;
typedef opendubins::Point DubinsPoint;
typedef opendubins::Arc DubinsArc;
typedef opendubins::Line DubinsLine;
typedef opendubins::State DubinsState;
typedef opendubins::Dubins3Point Dubins3Point;

typedef std::vector<DubinsManeuver> DubinsManeuverVector;
typedef std::vector<DubinsState> DubinsStateVector;
typedef std::vector<DubinsPoint> DubinsPointVector;

typedef std::vector<double> DoubleVector;

#endif

/* end of dubins_types.h */

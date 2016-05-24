#include "dubins_types.h"

#include "opendubins/dubins.h"
#include "opendubins/touring/dubins3point.h"

using namespace opendubins;

extern "C" double getCenterHeading(double p1x, double p1y, double p1a, double p2x, double p2y, double p3x, double p3y, double p3a) {
   DubinsState point1 = DubinsState(p1x, p1y, p1a);
   DubinsPoint point2 = DubinsPoint(p2x, p2y);
   DubinsState point3 = DubinsState(p3x, p3y, p3a);
   double radius = 1.0;
   int initialResolution = 1024;   
   Dubins3Point d3p = Dubins3Point(point1, point2, point3, radius, initialResolution);
   return d3p.centerHeading();   
}

extern "C" double getCenterHeadingWithResolution(int resolution, double p1x, double p1y, double p1a, double p2x, double p2y, double p3x, double p3y, double p3a) {
   DubinsState point1 = DubinsState(p1x, p1y, p1a);
   DubinsPoint point2 = DubinsPoint(p2x, p2y);
   DubinsState point3 = DubinsState(p3x, p3y, p3a);
   double radius = 1.0;
   Dubins3Point d3p = Dubins3Point(point1, point2, point3, radius, resolution);
   return d3p.centerHeading();
}

extern "C" double getDubinsLength(double p1x, double p1y, double p1a, double p2x, double p2y, double p2a, double p3x, double p3y, double p3a) {
   auto point1 = DubinsState(p1x, p1y, p1a);
   auto point2 = DubinsState(p2x, p2y, p2a);
   auto point3 = DubinsState(p3x, p3y, p3a);

   double radius = 1.0;
   Dubins d1 = Dubins(point1, point2, radius);
   Dubins d2 = Dubins(point2, point3, radius);
   return d1.length + d2.length;
}
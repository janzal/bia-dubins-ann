/*
 * polygon.h
 *
 *  Created on: 18. 7. 2014
 *      Author: Petr
 */

#ifndef POLYGON_H_
#define POLYGON_H_

#include<vector>

#include "opendubins/dubins.h"

#include "shape.h"

namespace opendubins{

class Polygon: public Shape {

public:

	std::vector<Point> pnts;
	Point center;
	myFloat maxRadius;

	Polygon(){};
	Polygon(std::vector<Point>);
	Polygon(Point center, int n, myFloat radius, myFloat alpha);
	virtual ~Polygon();

	bool pointInPolygon(Point);

	bool intersect(const Line & line) const;
	bool intersectBool(const Arc & arc) const;

	State intersect(const Dubins& dub) const;
	bool intersectBool(const Dubins& dub) const;

	Point getCenter();

private:
	void updateCenter();

public:

	/**
	 *  get Point on edge of this polygon
	 *
	 *  alpha - in interval < 0, 1 >
	 */
	Point getEdgePoint(myFloat alpha);

	myFloat perimeterLength();

	int getType();
};

} // namespace geom

#endif /* POLYGON_H_ */

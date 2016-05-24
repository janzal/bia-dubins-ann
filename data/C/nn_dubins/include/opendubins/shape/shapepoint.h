/*
 * shapepoint.h
 *
 *  Created on: 18. 7. 2014
 *      Author: Petr
 */

#pragma once

#include<vector>

#include "opendubins/point.h"
#include "opendubins/line.h"

#include "shape.h"

namespace opendubins{

class ShapePoint: public Shape {

public:

	Point point;

	ShapePoint(std::vector<Point>);
	ShapePoint(Point);
	virtual ~ShapePoint();

	bool intersect(Line line);

	Point getCenter();

	Point getEdgePoint(myFloat alpha);

	myFloat perimeterLength();

	int getType();

	bool pointInPolygon(Point);
};

} // namespace geom


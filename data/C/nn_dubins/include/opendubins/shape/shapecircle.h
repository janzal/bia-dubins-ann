/*
 * shapecircle.h
 *
 *  Created on: 24. 2. 2015
 *      Author: Petr Vana
 */

#pragma once

#include <tuple>

#include "opendubins/circle.h"
#include "shape.h"

namespace opendubins {

class ShapeCircle: public Shape {
public:

	Circle circle;

	inline ShapeCircle(): circle() {};
	ShapeCircle(const Point & center, const myFloat & radius);
	virtual ~ShapeCircle();

	Point getCenter();
	inline myFloat getRadius(){return circle.radius;}

	Point getEdgePoint(myFloat alpha);
	myFloat perimeterLength();

	bool pointInPolygon(Point);

	int getType();
};

}

/*
 * shape.h
 *
 *  Created on: 20. 7. 2014
 *      Author: Petr
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "opendubins/line.h"
#include "opendubins/point.h"

namespace opendubins{

class Shape {
public:
	Shape();
	virtual ~Shape();

	virtual bool pointInPolygon(Point);

	virtual bool intersect(Line line);

	virtual Point getCenter();

	/**
	 *  get Point on edge of this polygon
	 *
	 *  alpha - in interval < 0, 1 >
	 */
	virtual Point getEdgePoint(myFloat alpha);

	virtual myFloat perimeterLength();

	inline myFloat distanceIfConvex(Shape & other){
		myFloat a = 0;
		myFloat b = 0;
		return distanceIfConvex(other, a, b);
	}

	myFloat distanceIfConvex(Shape & other, myFloat & alpha1, myFloat & alpha2);

	virtual int getType();
};

}

#endif /* SHAPE_H_ */

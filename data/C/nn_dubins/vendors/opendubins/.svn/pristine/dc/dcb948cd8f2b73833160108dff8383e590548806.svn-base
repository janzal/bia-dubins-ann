/*
 * path.cpp
 *
 *  Created on: Aug 1, 2015
 *      Author: Petr Vana
 */

#include "opendubins/path.h"

namespace opendubins {

    Path::Path() { }

    Path::~Path() { }

    State Path::getStart() const {
        return getState(0);
    }

    State Path::getEnd() const {
        return getState(getLength());
    }

    State Path::getClosestState(const Point &p) const{
        return getClosestIntersection(p).state;
    }

}

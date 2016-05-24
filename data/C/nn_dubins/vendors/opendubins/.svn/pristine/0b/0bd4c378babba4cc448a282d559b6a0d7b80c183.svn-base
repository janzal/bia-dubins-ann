/*
 * intersection.h
 *
 *  Created on: Sep 22, 2014
 *      Author: petr
 */

#pragma once

#include "state.h"

namespace opendubins {

    struct Intersection {

        State state;
        myFloat distance;

        Intersection() {
            state = State(Point(NAN, NAN), NAN);
            distance = NAN;
        }

        Intersection(State state, myFloat distance) {
            this->state = state;
            this->distance = distance;
        }

    };

}

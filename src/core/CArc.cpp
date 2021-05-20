//
// Created by eliott on 21/04/2021.
//

#include "CArc.h"

/**
 * CArc constructor
 *
 * @param iARCDestination Destination vertex identifier
 */
CArc::CArc(int iARCDestination) {
    this->iARCDestination = iARCDestination;
}

/**
 * CArc copy constructor
 */
CArc::CArc(CArc &arc) {
    this->iARCDestination = arc.ARCGetDestination();
}

/**
 * Retrieves the identifier of the destination vertex
 *
 * @return The identifier of the destination vertex
 */
int CArc::ARCGetDestination() const {
    return this->iARCDestination;
}
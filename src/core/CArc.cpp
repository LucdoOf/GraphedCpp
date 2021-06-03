//
// Created by eliott on 21/04/2021.
//

#include "CArc.h"

/**
 * CArc constructor
 *
 * @param iARCDestination Destination vertex identifier
 */
CArc::CArc(int iARCDestination, int iCost, int iMaximumFlow) {
    this->iARCDestination = iARCDestination;
    this->iCost = iCost;
    this->iMaximumFlow = iMaximumFlow;
}

/**
 * CArc copy constructor
 */
CArc::CArc(CArc &arc) {
    this->iARCDestination = arc.ARCGetDestination();
    this->iCost = arc.ARCGetCost();
    this->iMaximumFlow = arc.ARCGetMaximumFlow();
}

/**
 * Retrieves the identifier of the destination vertex
 *
 * @return The identifier of the destination vertex
 */
int CArc::ARCGetDestination() const {
    return this->iARCDestination;
}

/**
 * Retrieves the unitary cost of the arc
 *
 * @return The unitary cost of the arc
 */
int CArc::ARCGetCost() const {
    return this->iCost;
}

/**
 * Retrieves the maximum flow supported by the arc
 *
 * @return  The maximum flow supported by the arc
 */
int CArc::ARCGetMaximumFlow() const {
    return this->iMaximumFlow;
}

/**
 * Set the temporary flow value of the arc
 *
 * @param iTemporaryFlow New value of the temporary value
 */
void CArc::ARCSetTemporaryFlow(int iTemporaryFlow) {
    this->iTempFlow = iTemporaryFlow;
}

/**
 * Retrieves the temporary flow value of the arc
 *
 * @return The temporary flow value of the arc
 */
int CArc::ARCGetTemporaryFlow() const {
    return this->iTempFlow;
}

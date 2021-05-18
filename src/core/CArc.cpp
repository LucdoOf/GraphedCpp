//
// Created by eliott on 21/04/2021.
//

#include "CArc.h"

CArc::CArc(int iARCDestination) {
    this->iARCDestination = iARCDestination;
}

CArc::CArc(CArc &arc) {
    this->iARCDestination = arc.ARCGetDestination();
}

int CArc::ARCGetDestination() {
    return this->iARCDestination;
}

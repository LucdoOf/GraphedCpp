//
// Created by eliott on 21/04/2021.
//

#include <cstdlib>
#include "CArc.h"

CArc::CArc(int iDestination) {
    this->iARCDestination = iDestination;
}

CArc::~CArc() {
    this->iARCDestination = 0;
    free(this);
}

CSommet* CArc::getDestinationVertex() {
    for(int i)
}

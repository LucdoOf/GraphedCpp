//
// Created by eliott on 21/04/2021.
//

#include "CSommet.h"

inline int CSommet::SOMGetIncomingCount() {
    return this->iIncomingCount;
}

inline int CSommet::SOMGetLeavingCount() {
    return this->iLeavingCount;
}

inline CList<CArc*>* CSommet::SOMGetIncomingArcs() {
    return this->pSOMIncoming;
}

inline CList<CArc*>* CSommet::SOMGetLeavingArcs() {
    return this->pSOMLeaving;
}

int CSommet::SOMGetId() {
    return iId;
}

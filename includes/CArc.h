//
// Created by eliott on 21/04/2021.
//

#ifndef MATRIXEDCPP_CARC_H
#define MATRIXEDCPP_CARC_H

#include "CSommet.h"

class CArc{
private:
    int iARCDestination;
public:
    CArc(int iARCDestination);
    ~CArc();
    CSommet* ARCGetDestinationVertex();
};

#endif //MATRIXEDCPP_CARC_H

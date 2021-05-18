//
// Created by eliott on 21/04/2021.
//

#ifndef MATRIXEDCPP_CARC_H
#define MATRIXEDCPP_CARC_H

class CArc {

private:
    int iARCDestination;

public:
    CArc(int iARCDestination);
    CArc(CArc &);
    ~CArc();
    int ARCGetDestination();

};

#endif //MATRIXEDCPP_CARC_H

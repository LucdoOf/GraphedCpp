#ifndef GRAPHEDCPP_CSOMMET_H
#define GRAPHEDCPP_CSOMMET_H

#include "CArc.h"

class CSommet {
private:
    int iId;
    CArc** pSOMIncoming;
    CArc** pSOMLeaving;
public:
    CSommet(int iId);
    ~CSommet();
    void setIncoming(CArc* CArc);
    void setLeaving(CArc* CArc);
};

#endif //GRAPHEDCPP_CSOMMET_H
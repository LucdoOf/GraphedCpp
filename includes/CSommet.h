#ifndef GRAPHEDCPP_CSOMMET_H
#define GRAPHEDCPP_CSOMMET_H

#include "CArc.h"

class CSommet {
private:
    int iSOMId;
    CArc** pSOMIncoming;
    CArc** pSOMLeaving;
public:
    CSommet(int iId, CArc** pIncoming, CArc** pLeaving, int iCountIncoming, int iCountLeaving);
    CSommet(int iId);
    CSommet(CSommet* pSommet);
    ~CSommet();
    void setIncoming(CArc* arc);
    void setLeaving(CArc* arc);
    int iSOMCountIncoming;
    int iSOMCountLeaving;
};

#endif //GRAPHEDCPP_CSOMMET_H
#ifndef GRAPHEDCPP_CSOMMET_H
#define GRAPHEDCPP_CSOMMET_H

#include "CArc.h"
#include <cstdio>
#include "CList.h"

class CSommet {

private:
    int iId;
    CList<CArc>* pSOMIncoming;
    CList<CArc>* pSOMLeaving;

public:
    CSommet(int iId);
    CSommet(CSommet&);
    ~CSommet();
    void addIncomingArc(CArc* CArc);
    void addLeavingArc(CArc* CArc);
    void deleteLeavingArc(CArc* arc);
    void deleteIncomingArc(CArc* arc);
    CList<CArc>* SOMGetIncomingArcs();
    CList<CArc>* SOMGetLeavingArcs();
    int SOMGetId();

};

#endif //GRAPHEDCPP_CSOMMET_H
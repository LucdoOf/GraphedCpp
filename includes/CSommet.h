#ifndef GRAPHEDCPP_CSOMMET_H
#define GRAPHEDCPP_CSOMMET_H

#include "CArc.h"
#include <cstdio>
#include "CList.h"

class CSommet {

private:
    int iId;
    CList<CArc*>* pSOMIncoming;
    CList<CArc*>* pSOMLeaving;
    int iIncomingCount;
    int iLeavingCount;
public:
    CSommet(int iId);
    ~CSommet();
    void setIncoming(CArc* CArc);
    void setLeaving(CArc* CArc);
    int SOMGetLeavingCount();
    int SOMGetIncomingCount();
    CList<CArc*>* SOMGetIncomingArcs();
    CList<CArc*>* SOMGetLeavingArcs();
    CList<CSommet>* SOMGetIncomingVertices();
    int SOMGetId();
    void print();

};

#endif //GRAPHEDCPP_CSOMMET_H
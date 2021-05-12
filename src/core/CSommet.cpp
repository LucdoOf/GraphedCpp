//
// Created by eliott on 21/04/2021.
//

#include <cstdlib>
#include <search.h>
#include "CSommet.h"

CSommet::CSommet(int iId) {
    this->iSOMId = iId;
    this->pSOMLeaving = (CArc**) malloc(sizeof(CArc**));
    this->pSOMIncoming = (CArc**) malloc(sizeof(CArc**));
    iSOMCountIncoming = 0;
    iSOMCountLeaving = 0;
}

CSommet::CSommet(int iId, CArc **pIncoming, CArc **pLeaving, int iCountIncoming, int iCountLeaving) {
    this->iSOMId = iId;
    this->pSOMIncoming = pIncoming;
    this->pSOMLeaving = pLeaving;
    this->iSOMCountLeaving = iCountLeaving;
    this->iSOMCountIncoming = iCountIncoming;
}

CSommet::CSommet(CSommet *pSommet) {
    this->iSOMId = pSommet->iSOMId;
    this->pSOMIncoming = pSommet->pSOMIncoming;
    this->pSOMLeaving = pSommet->pSOMLeaving;
    this->iSOMCountIncoming = pSommet->iSOMCountIncoming;
    this->iSOMCountLeaving = pSommet->iSOMCountLeaving;
}

CSommet::~CSommet() {
    for(int i = 0; i < iSOMCountIncoming; i++){
        free(this->pSOMIncoming[i]);
    }

    for(int j = 0; j < iSOMCountLeaving; j++){
        free(this->pSOMLeaving[j]);
    }
    this->iSOMCountLeaving = 0;
    this->iSOMCountIncoming = 0;
    free(this->pSOMLeaving);
    free(this->pSOMIncoming);
}

void CSommet::setIncoming(CArc *arc) {
    this->iSOMCountIncoming ++;
    this->pSOMIncoming = (CArc **) realloc(pSOMIncoming, sizeof(pSOMIncoming) + sizeof(CArc));
    this->pSOMIncoming[iSOMCountIncoming] = arc;
}

void CSommet::setLeaving(CArc *arc) {
    this->iSOMCountLeaving ++;
    this->pSOMLeaving = (CArc **) realloc(pSOMLeaving, sizeof(pSOMLeaving) + sizeof(CArc));
    this->pSOMLeaving[iSOMCountLeaving] = arc;
}




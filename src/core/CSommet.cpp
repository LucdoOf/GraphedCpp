//
// Created by eliott on 21/04/2021.
//

#include "CSommet.h"

inline CList<CArc*>* CSommet::SOMGetIncomingArcs() {
    return this->pSOMIncoming;
}

inline CList<CArc*>* CSommet::SOMGetLeavingArcs() {
    return this->pSOMLeaving;
}

int CSommet::SOMGetId() {
    return iId;
}

void CSommet::addLeavingArc(CArc* arc) {
    for (int i = 0; i < this->SOMGetLeavingArcs()->getSize(); i++) {
        CArc* existingArc = this->SOMGetLeavingArcs()->get(i);
        if (existingArc->ARCGetDestination() == arc->ARCGetDestination()) {
            // On évite les doublons pour des problèmes de boucles infinies lors des traitements, de plus ils sont inutiles
            // Cependant on ne lève pas d'erreur, ce n'est pas un problème grave
            return;
        }
    }
    this->SOMGetLeavingArcs()->add(arc);
}

void CSommet::addIncomingArc(CArc* arc) {
    this->SOMGetIncomingArcs()->add(arc);
}

CSommet::CSommet(int iId) {
    this->iId = iId;
    this->pSOMIncoming = new CList<CArc*>();
    this->pSOMLeaving = new CList<CArc*>();
}

CSommet::~CSommet() {

}

//
// Created by eliott on 21/04/2021.
//

#include "CSommet.h"

/**
 * CSommet constructor
 *
 * @param iSOMId Vertex identifier
 */
CSommet::CSommet(int iSOMId) {
    this->iSOMId = iSOMId;
    this->pSOMIncoming = new CList<CArc>();
    this->pSOMLeaving = new CList<CArc>();
}

/**
 * CSommet copy constructor
 *
 * Copy the list of leaving and incoming arc
 */
CSommet::CSommet(CSommet &vertex) {
    this->iSOMId = vertex.iSOMId;
    this->pSOMIncoming = new CList<CArc>(*vertex.pSOMIncoming);
    this->pSOMLeaving = new CList<CArc>(*vertex.pSOMLeaving);
}

/**
 * CSommet destructor
 *
 * Delete the incoming and leaving arc
 */
CSommet::~CSommet() {
    delete this->pSOMIncoming;
    delete this->pSOMLeaving;
}

/**
 * Add an incoming arc to the vertex
 *
 * @param CArc New incoming arc (don't add duplicates)
 */
void CSommet::SOMAddIncomingArc(CArc* arc) {
    for (int i = 0; i < this->SOMGetIncomingArcs()->getSize(); i++) {
        CArc* existingArc = this->SOMGetIncomingArcs()->get(i);
        if (existingArc->ARCGetDestination() == arc->ARCGetDestination()) {
            // On évite les doublons pour des problèmes de boucles infinies lors des traitements, de plus ils sont inutiles
            // Cependant on ne lève pas d'erreur, ce n'est pas un problème grave
            return;
        }
    }
    this->SOMGetIncomingArcs()->add(arc);
}

/**
 * Add a leaving arc to the vertex
 *
 * @param CArc New leaving arc (don't add duplicates)
 */
void CSommet::SOMAddLeavingArc(CArc* arc) {
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

/**
 * Remove an incoming arc from the vertex
 *
 * @param arc Incoming arc to remove (delete the arc)
 */
void CSommet::SOMDeleteIncomingArc(CArc *arc) {
    this->SOMGetIncomingArcs()->remove(arc);
}

/**
 * Remove a leaving arc from the vertex
 *
 * @param arc Leaving arc to remove (delete the arc)
 */
void CSommet::SOMDeleteLeavingArc(CArc *arc) {
    this->SOMGetLeavingArcs()->remove(arc);
}

/**
 * Retrieves the list of the vertex incoming arcs
 *
 * @warning It is not recommended to change the list content, this list is given only for getting purposes,
 * any direct modifications will cause the vertex / graph to be corrupted, please use vertex methods instead
 * @return The list of the incoming vertex arcs
 */
CList<CArc>* CSommet::SOMGetIncomingArcs() { return this->pSOMIncoming; }

/**
 * Retrieves the list of the vertex leaving arcs
 *
 * @warning It is not recommended to change the list content, this list is given only for getting purposes,
 * any direct modifications will cause the vertex / graph to be corrupted, please use vertex methods instead
 * @return The list of the leaving vertex arcs
 */
CList<CArc>* CSommet::SOMGetLeavingArcs() { return this->pSOMLeaving; }

/**
 * Retrieves the vertex identifier
 *
 * @return The vertex identifier
 */
int CSommet::SOMGetId() const { return this->iSOMId; }

/**
 * Check the incoming and leaving arcs for the conversation law
 *
 * @return True if the conservation law is respected, false if it isn't
 */
bool CSommet::checkConservationLaw() {
    int incomingFlow = 0;
    int leavingFlow = 0;
    for (int i = 0; i < this->SOMGetIncomingArcs()->getSize(); i++) {
        incomingFlow += this->SOMGetIncomingArcs()->get(i)->ARCGetTemporaryFlow();
    }
    for (int i = 0; i < this->SOMGetLeavingArcs()->getSize(); i++) {
        leavingFlow += this->SOMGetLeavingArcs()->get(i)->ARCGetTemporaryFlow();
    }
    return incomingFlow == leavingFlow;
}

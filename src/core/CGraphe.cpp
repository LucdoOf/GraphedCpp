//
// Created by eliott on 21/04/2021.
//

#include "CGraphe.h"

void CGraph::print() {
    CGraph graph = CGraph(*this);

    CList<CSommet*>* vertexList = graph.GRAGetVertices();
    CList<CArc*>* arcActualList = vertexList->get(0)->SOMGetLeavingArcs();
    CArc* arc;

    while (true) {
        // Fin de la chaîne
        if (arcActualList->getSize() == 0) {
            if (vertexList->getSize() == 0) {
                break;
            } else {
                // Passage sur le root vertex
                arcActualList = vertexList->get(0)->SOMGetLeavingArcs();
                vertexList->shift();
            }
        } else {
            // Il reste des arcs a traiter on supprime l'arc actuel, on print, et on passe au prochain
            auto oldList = arcActualList;
            CSommet* vertex = oldList->get(0)->ARCGetDestinationVertex();
            printf("%d ", vertex->SOMGetId());
            // On met à jour la liste
            arcActualList = vertex->SOMGetLeavingArcs();
            arc = oldList->get(0);
            oldList->remove(arc);
        }
    }
}

inline CList<CSommet*>* CGraph::GRAGetVertices() {
    return this->pGRAVertices;
}
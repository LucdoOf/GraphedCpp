//
// Created by eliott on 21/04/2021.
//

#include "CGraph.h"

CGraph::CGraph() {
    this->pGRAVertices = new CList<CSommet*>();
}


void CGraph::print() {
    CGraph graph = CGraph(*this);

    int rootIndex = 0;
    CList<CSommet*>* vertexList = graph.GRAGetVertices();
    CList<CArc*>* arcActualList = nullptr;
    int actualChainSize;

    while (true) {
        // Fin de la chaîne
        if (arcActualList == nullptr || arcActualList->getSize() == 0) {
            // Si ce n'est pas la première itération, on affiche le nombre de sommets dans la chaîne
            if (arcActualList != nullptr) printf(" (%d vertices)", actualChainSize);
            // Si la liste globale des vertex est vide, alors on a traité tout les sommets
            if (rootIndex == vertexList->getSize()) {
                printf("\n"); // Il ne reste plus de sommets non traités
                break;
            } else {
                // Sinon, il reste des sommets non traités et on passe sur une autre chaine
                printf("\n");
                // Passage sur le root vertex, on print le root avant de print la suite
                actualChainSize = 1;
                printf("Root: %d", vertexList->get(rootIndex)->SOMGetId());
                arcActualList = vertexList->get(rootIndex)->SOMGetLeavingArcs();

                // On vérifie que la chaine est vide, c'est à dire si c'est la dernière itération
                // dans laquelle la chaine va être print, soit si toutes les listes sortantes sont de taille 1 ou 0 pour la dernière
                bool lastIteration = true;
                CList<CArc*>* tempList = arcActualList;
                while (tempList != nullptr) {
                    // Prevent infinite loop
                    if (tempList->getSize() >= 1 && tempList->get(0)->ARCGetDestination() != vertexList->get(rootIndex)->SOMGetId()) {
                        if (tempList->getSize() > 1) {
                            lastIteration = false;
                            break;
                        } else {
                            tempList = graph.getVertexById(tempList->get(0)->ARCGetDestination())->SOMGetLeavingArcs();
                        }
                    } else {
                        // Dernière liste de la chaîne
                        tempList = nullptr;
                    }
                }

                // Si la chaine est vide, on retire le root
                if (lastIteration) {
                    rootIndex++;
                }

            }
        } else {
            // Il reste des arcs a traiter on supprime l'arc actuel, on print, et on passe au prochain
            auto oldList = arcActualList;
            CSommet* vertex = graph.getVertexById(oldList->get(0)->ARCGetDestination());
            printf(" -> %d", vertex->SOMGetId());
            actualChainSize++;
            // On met à jour la liste
            arcActualList = vertex->SOMGetLeavingArcs();
            // Si il y a plus d'un arc sortant, alors il faudra retraiter la chaine après la fin de cette chaine
            if (arcActualList->getSize() <= 1) {
                oldList->shift();
            }
        }
    }
}

inline CList<CSommet*>* CGraph::GRAGetVertices() {
    return this->pGRAVertices;
}

void CGraph::addVertex(CSommet* vertex) {
    this->pGRAVertices->add(vertex);
}

CSommet *CGraph::getVertexById(int id) {
    for (int i = 0; i < this->pGRAVertices->getSize(); i++) {
        CSommet* vertex = this->pGRAVertices->get(i);
        if (vertex->SOMGetId() == id) return vertex;
    }
    return nullptr;
}
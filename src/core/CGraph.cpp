//
// Created by eliott on 21/04/2021.
//

#include "CGraph.h"

CGraph::CGraph() {
    this->pGRAVertices = new CList<CSommet*>();
}

CGraph::CGraph(CGraph &graph) {
    this->pGRAVertices = new CList<CSommet*>(*graph.pGRAVertices);
}

void CGraph::print() {

    /*
     * Cette fonction marche avec la notion de chaîne.
     * Une chaîne est définie comme la succession de sommets reliés par des arcs.
     * Pour construire une chaîne on prend un sommet "root", puis on regarde à chaque fois le premier arc sortant
     * et ce jusqu'au moment ou on retombe sur le sommet "root" où bien jusqu'au moment ou il n'y à plus d'arc sortant.
     * A chaque fois que l'on passe sur un arc, on le supprime de la liste des arcs afin d'assurer le fonctionnement de l'algorithme.
     */
    auto graph = new CGraph(*this);

    int rootIndex = 0;                                       // Index du root actuel dans la liste des sommets
    CList<CSommet*>* vertexList = graph->GRAGetVertices();   // Liste de tout les sommets du graphe
    CList<CArc*>* arcActualList = nullptr;                   // Liste d'arc a traiter au cours de la prochaine itération
    int actualChainSize;                                     // Utilisé pour print le nombre de vertex de la chaîne

    while (true) {
        // Fin de la chaîne courante ou début du parcours (arcActualList est nulle au tout début)
        if (arcActualList == nullptr || arcActualList->getSize() == 0) {
            // Si ce n'est pas la première itération, on affiche le nombre de sommets dans la chaîne
            if (arcActualList != nullptr) printf(" (%d vertices)", actualChainSize);
            // Si l'index courant est supérieur à celui du dernier sommet, alors on sort de la boucle, on a tout traité
            if (rootIndex == vertexList->getSize()) {
                printf("\n"); // Esthetique
                break;
            } else {
                // Sinon, il reste des sommets non traités et on passe sur une autre chaine
                printf("\n");
                // Passage sur le root vertex, on print le root avant de print la suite
                actualChainSize = 1;
                printf("Root: %d", vertexList->get(rootIndex)->SOMGetId());
                arcActualList = vertexList->get(rootIndex)->SOMGetLeavingArcs();

                // On vérifie que la chaine est vide à 1 sommet prêt pour chaque maillon
                // Si il reste des "croisements" dans la chaîne, alors il ne faut pas changer de root, il faut repasser
                // à la prochaine itération dessus. Si par exemple on à comme root 2 et un graphe 2 -> 3, 4
                // On ne peux pas encore changer de root à la prochaine itération, il faudra 2 itérations pour print toutes
                // les chaînes partant de ce root.
                bool lastIteration = true;
                CList<CArc*>* tempList = arcActualList;
                while (tempList != nullptr) {
                    // Prevent infinite loop
                    if (tempList->getSize() >= 1 && tempList->get(0)->ARCGetDestination() != vertexList->get(rootIndex)->SOMGetId()) {
                        if (tempList->getSize() > 1) {
                            lastIteration = false;
                            break;
                        } else {
                            tempList = graph->getVertexById(tempList->get(0)->ARCGetDestination())->SOMGetLeavingArcs();
                        }
                    } else {
                        // Dernière liste de la chaîne
                        tempList = nullptr;
                    }
                }

                // Si la chaine est vide, on passe au root suivant
                if (lastIteration) rootIndex++;
            }
        } else {
            // Il reste des arcs a traiter on supprime l'arc actuel, on print, et on passe au prochain
            auto oldList = arcActualList;
            CSommet* vertex = graph->getVertexById(oldList->get(0)->ARCGetDestination());
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

void CGraph::deleteVertex(CSommet *vertex) {
    if (this->GRAGetVertices()->contains(vertex)) {
        this->GRAGetVertices()->remove(vertex);
        for (int i = 0; i < this->GRAGetVertices()->getSize(); i++) {
            CSommet* existingVertex = this->GRAGetVertices()->get(i);
            for (int j = 0; j < existingVertex->SOMGetLeavingArcs()->getSize(); j++) {
                CArc* existingArc = existingVertex->SOMGetLeavingArcs()->get(j);
                if (existingArc->ARCGetDestination() == vertex->SOMGetId()) {
                    existingVertex->deleteLeavingArc(existingArc);
                }
            }
        }
    }
}

CGraph *CGraph::GRAInvert() {
    auto graph = new CGraph();

    // Loop through existing vertices
    for (int i = 0; i < this->GRAGetVertices()->getSize(); i++) {
        CSommet* existingVertex = this->GRAGetVertices()->get(i);
        auto newVertex = new CSommet(existingVertex->SOMGetId());

        // Copying incoming arcs to leaving arcs
        for (int j = 0; j < existingVertex->SOMGetIncomingArcs()->getSize(); j++) {
            CArc* existingArc = existingVertex->SOMGetIncomingArcs()->get(j);
            newVertex->addLeavingArc(new CArc(existingArc->ARCGetDestination()));
        }

        // Copying leaving arcs to incoming arcs
        for (int j = 0; j < existingVertex->SOMGetLeavingArcs()->getSize(); j++) {
            CArc* existingArc = existingVertex->SOMGetLeavingArcs()->get(j);
            newVertex->addIncomingArc(new CArc(existingArc->ARCGetDestination()));
        }

        // Adding the new vertex to the graph
        graph->addVertex(newVertex);
    }

    return graph;
}

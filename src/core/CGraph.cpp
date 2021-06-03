//
// Created by eliott on 21/04/2021.
//

#include "CGraph.h"

/**
 * CGraph constructor
 */
CGraph::CGraph() {
    this->pGRAVertices = new CList<CSommet>();
}

/**
 * CGraph copy constructor
 *
 * Duplicate every vertices in the graph using CSommet copy constructor
 */
CGraph::CGraph(CGraph &graph) {
    this->pGRAVertices = new CList<CSommet>(*graph.pGRAVertices);
}

/**
 * CGraph destructor
 *
 * Delete every vertices and every arcs objects
 */
CGraph::~CGraph() {
    delete this->pGRAVertices;
}

/**
 * Retrieves the origin vertex of the given arc
 *
 * @return The origin vertex of the given arc
 * or nullptr if no origin have been found (graph is corrupted or arc is not in the graph)
 */
CSommet *CGraph::GRAGetArcOrigin(CArc* arc) {
    for (int i = 0; i < this->GRAGetVertices()->getSize(); i++) {
        CSommet* vertex = this->GRAGetVertices()->get(i);
        for (int j = 0; j < vertex->SOMGetLeavingArcs()->getSize(); j++) {
            CArc* existingArc = vertex->SOMGetLeavingArcs()->get(j);
            if (arc->ARCGetDestination() == existingArc->ARCGetDestination()) return vertex;
        }
    }
    return nullptr;
}

/**
 * Print the graph into standard output.
 * The printing algorithm will try to collapse as much as possible vertex to display longest chain possible
 * instead of listing vertices with their leaving arcs.
 */
void CGraph::GRAPrint() {
    /*
     * Nous n'avons pas voulu faire une fonction de print triviale qui allait prendre chaque sommet et afficher la liste des
     * arcs partants et sortants. Nous avons decider de pousser le challenge:
     *
     * Cette fonction fonctionne avec la notion de chaîne.
     * Une chaîne est définie comme la succession de sommets reliés par des arcs.
     * Pour construire une chaîne on prend un sommet "root", puis on regarde à chaque fois le premier arc sortant
     * et ce jusqu'au moment ou on retombe sur le sommet "root" où bien jusqu'au moment ou il n'y à plus d'arc sortant.
     * A chaque fois que l'on passe sur un arc, on le supprime de la liste des arcs afin d'assurer le fonctionnement de l'algorithme.
     */
    auto graph = new CGraph(*this);

    int rootIndex = 0;                                            // Index du root actuel dans la liste des sommets
    CList<CSommet>* vertexList = graph->GRAGetVertices();         // Liste de tout les sommets du graphe
    CList<CArc>* arcActualList = nullptr;                         // Liste d'arc a traiter au cours de la prochaine itération
    int actualChainSize;                                          // Utilisé pour print le nombre de vertex de la chaîne

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
                CList<CArc>* tempList = arcActualList;
                while (tempList != nullptr) {
                    // Prevent infinite loop
                    if (tempList->getSize() >= 1 && tempList->get(0)->ARCGetDestination() != vertexList->get(rootIndex)->SOMGetId()) {
                        if (tempList->getSize() > 1) {
                            lastIteration = false;
                            break;
                        } else {
                            tempList = graph->GRAGetVertexById(tempList->get(0)->ARCGetDestination())->SOMGetLeavingArcs();
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
            CSommet* vertex = graph->GRAGetVertexById(oldList->get(0)->ARCGetDestination());
            printf(" -> %d", vertex->SOMGetId());
            actualChainSize++;
            // On met à jour la liste
            arcActualList = vertex->SOMGetLeavingArcs();
            // Si il y a plus d'un arc sortant, alors il faudra retraiter la chaine après la fin de cette chaine
            if (arcActualList->getSize() == 1) {
                oldList->shift();
            }
        }
    }

    delete graph;
}

/**
 * Retrieves all of the graph vertices in their creation order.
 *
 * @warning It is not recommended to change the list content, this list is given only for getting purposes,
 * any direct modifications will cause the graph to be corrupted, please use graph methods instead
 * @return All of the graph vertices in their creation order.
 */
inline CList<CSommet>* CGraph::GRAGetVertices() {
    return this->pGRAVertices;
}

/**
 * Add a vertex to the vertex list
 *
 * @param vertex Vertex to add to the graph
 */
void CGraph::GRAAddVertex(CSommet* vertex) {
    this->pGRAVertices->add(vertex);
}

/**
 * Delete a vertex from the graph
 *
 * @param vertex Vertex to delete from the graph (delete the vertex)
 */
void CGraph::GRADeleteVertex(CSommet *vertex) {
    if (this->GRAGetVertices()->contains(vertex)) {
        this->GRAGetVertices()->remove(vertex);
        for (int i = 0; i < this->GRAGetVertices()->getSize(); i++) {
            CSommet* existingVertex = this->GRAGetVertices()->get(i);
            for (int j = 0; j < existingVertex->SOMGetLeavingArcs()->getSize(); j++) {
                CArc* existingArc = existingVertex->SOMGetLeavingArcs()->get(j);
                if (existingArc->ARCGetDestination() == vertex->SOMGetId()) {
                    existingVertex->SOMDeleteLeavingArc(existingArc);
                }
            }
        }
        delete vertex;
    }
}

/**
 * Retrieves a vertex by its identifier
 *
 * @param id Vertex identifier
 * @return The graph vertex with the given identifier or nullptr if not found
 */
CSommet *CGraph::GRAGetVertexById(int id) {
    for (int i = 0; i < this->pGRAVertices->getSize(); i++) {
        CSommet* vertex = this->pGRAVertices->get(i);
        if (vertex->SOMGetId() == id) return vertex;
    }
    return nullptr;
}

/**
 * Return a new graph which is a copy of the current graph except that every arcs have been inverted
 *
 * @return A new graph which is a copy of the current graph except that every arcs have been inverted
 */
CGraph *CGraph::GRAInvert() {
    auto graph = new CGraph();

    // Loop through existing vertices
    for (int i = 0; i < this->GRAGetVertices()->getSize(); i++) {
        // Getting current loop vertex
        CSommet* currentVertex = this->GRAGetVertices()->get(i);

        auto *newVertex = graph->GRAGetVertexById(currentVertex->SOMGetId());
        // Add the vertex if not already added below
        if (newVertex == nullptr) {
            newVertex = new CSommet(currentVertex->SOMGetId());
            graph->GRAAddVertex(newVertex);
        }

        // Copying incoming arcs to leaving arcs
        for (int j = 0; j < currentVertex->SOMGetIncomingArcs()->getSize(); j++) {
            CArc* oldArc = currentVertex->SOMGetIncomingArcs()->get(j);
            CSommet* arcOriginVertex = this->GRAGetArcOrigin(oldArc);
            CSommet* newOriginVertex = graph->GRAGetVertexById(arcOriginVertex->SOMGetId());
            // Add the vertex if not already added
            if (newOriginVertex == nullptr) {
                newOriginVertex = new CSommet(arcOriginVertex->SOMGetId());
                graph->GRAAddVertex(newOriginVertex);
            }
            newVertex->SOMAddLeavingArc(new CArc(newOriginVertex->SOMGetId(), oldArc->ARCGetCost(), oldArc->ARCGetMaximumFlow()));
        }

        // Copying leaving arcs to incoming arcs
        for (int j = 0; j < currentVertex->SOMGetLeavingArcs()->getSize(); j++) {
            CArc* oldArc = currentVertex->SOMGetLeavingArcs()->get(j);
            int destinationId = oldArc->ARCGetDestination();
            CSommet* newArcDestinationVertex = graph->GRAGetVertexById(destinationId);
            // Add the vertex if not already added
            if (newArcDestinationVertex == nullptr) {
                newArcDestinationVertex = new CSommet(destinationId);
                graph->GRAAddVertex(newArcDestinationVertex);
            }
            newVertex->SOMAddIncomingArc(new CArc(newVertex->SOMGetId(), oldArc->ARCGetCost(), oldArc->ARCGetMaximumFlow()));
        }

    }

    return graph;
}

/**
 * Ask the user for the flow amount of every arc in the graph
 */
void CGraph::GRAAskFlowAmounts() {
    for (int i = 0; i < this->GRAGetVertices()->getSize(); i++) {
        CSommet* vertex = this->GRAGetVertices()->get(i);
        // Loop through incoming
        for (int j = 0; j < vertex->SOMGetLeavingArcs()->getSize(); j++) {
            CArc* arc = vertex->SOMGetLeavingArcs()->get(j);
            int flow = 0;
            printf("%s", strMultiCat(5, "Flow amount for the arc ", itoa(vertex->SOMGetId()), " -> ", itoa(arc->ARCGetDestination()), ": "));
            scanf("%d", &flow);
            arc->ARCSetTemporaryFlow(flow);
        }
    }
}

/**
 * Check the incoming and leaving arcs of each vertices for the conversation law
 *
 * @return True if the conservation law is respected, false if it isn't
 */
bool CGraph::GRATestConservationLaw() {
    for (int i = 0; i < this->GRAGetVertices()->getSize(); i++) {
        if (!this->GRAGetVertices()->get(i)->SOMTestConservationLaw()) return false;
    }
    return true;
}

/**
 * Print every step of the conservation law test process
 */
void CGraph::GRAPrintConservationLaw() {
    for (int i = 0; i < this->GRAGetVertices()->getSize(); i++) {
        this->GRAGetVertices()->get(i)->SOMPrintConservationLaw();
    }
}

/**
 * Retrieves the amount of the total cost for the actual flow
 *
 * @return the amount of the total cost for the actual flow
 */
int CGraph::GRAGetTotalCost() {
    int totalCost = 0;
    for (int i = 0; i < this->GRAGetVertices()->getSize(); i++) {
        CSommet* vertex = this->GRAGetVertices()->get(i);
        for (int j = 0; j < vertex->SOMGetLeavingArcs()->getSize(); j++) {
            CArc* arc = vertex->SOMGetLeavingArcs()->get(j);
            totalCost+= arc->ARCGetTemporaryFlow() * arc->ARCGetCost();
        }
    }
    return totalCost;
}






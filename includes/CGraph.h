//
// Created by eliott on 21/04/2021.
//

#ifndef MATRIXEDCPP_CGRAPHE_H
#define MATRIXEDCPP_CGRAPHE_H

#include "CSommet.h"
#include <malloc.h>

/**
 * CGraph constructor
 *
 * Representation of an oriented graph containing vertices linked with arcs.
 */
class CGraph {

private:
    /**
     * List of the graph vertices
     */
    CList<CSommet>* pGRAVertices;

public:
    /**
     * CGraph constructor
     */
    CGraph();
    /**
     * CGraph copy constructor
     *
     * Duplicate every vertices in the graph using CSommet copy constructor
     */
    CGraph(CGraph&);
    /**
     * CGraph destructor
     *
     * Delete every vertices and every arcs objects
     */
    ~CGraph();
    /**
     * Retrieves the origin vertex of the given arc
     *
     * @return The origin vertex of the given arc
     * or nullptr if no origin have been found (graph is corrupted or arc is not in the graph)
     */
    CSommet* GRAGetArcOrigin(CArc*);
    /**
     * Print the graph into standard output.
     * The printing algorithm will try to collapse as much as possible vertex to display longest chain possible
     * instead of listing vertices with their leaving arcs.
     */
    void GRAPrint();
    /**
     * Retrieves all of the graph vertices in their creation order.
     *
     * @warning It is not recommended to change the list content, this list is given only for getting purposes,
     * any direct modifications will cause the graph to be corrupted, please use graph methods instead
     * @return All of the graph vertices in their creation order.
     */
    inline CList<CSommet>* GRAGetVertices();
    /**
     * Add a vertex to the vertex list
     *
     * @param vertex Vertex to add to the graph
     */
    void GRAAddVertex(CSommet* vertex);
    /**
     * Delete a vertex from the graph
     *
     * @param vertex Vertex to delete from the graph (delete the vertex)
     */
    void GRADeleteVertex(CSommet* vertex);
    /**
     * Retrieves a vertex by its identifier
     *
     * @param id Vertex identifier
     * @return The graph vertex with the given identifier or nullptr if not found
     */
    CSommet* GRAGetVertexById(int id);
    /**
     * Return a new graph which is a copy of the current graph except that every arcs have been inverted
     *
     * @return A new graph which is a copy of the current graph except that every arcs have been inverted
     */
    CGraph* GRAInvert();

};
#endif //MATRIXEDCPP_CGRAPHE_H
